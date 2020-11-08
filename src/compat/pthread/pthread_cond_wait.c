/*
 * pthread_cond_wait.c
 *
 */

#include "pthread.h"
#include "implement.h"
#include "pthread_cond_common.h"

static int no_check(void *s){
  return 0;
}

struct op {
     nk_timer_t *timer;
};

static int check_timer(void *s)
{
    struct op *o = (struct op *)s;
    return __sync_fetch_and_or(&o->timer->state,0)==NK_TIMER_SIGNALLED;
}

int
pthread_cond_timedwait (pthread_cond_t * c,
                    pthread_mutex_t * l, const struct timespec *abstime)
{
   
    NK_PROFILE_ENTRY();
    int result = 0;
    if (c == NULL || abstime == NULL){
      return EINVAL;
		      
    }

    uint64_t start = nk_sched_get_realtime();
    uint64_t now = start;
    uint64_t timeout_ns = abstime->tv_sec*1000000000ULL+abstime->tv_nsec;
    DEBUG("Condvar wait on (%p) mutex=%p\n", (void*)c, (void*)l);

    NK_LOCK(&c->lock);

    /* now we can unlock the mutex and go to sleep */
    pthread_mutex_unlock(l);

    ++c->nwaiters;
    ++c->main_seq;

    unsigned long long val;
    unsigned long long seq;
    unsigned bc = *(volatile unsigned*)&(c->bcast_seq);
    val = seq = c->wakeup_seq;

    do {
      if((now-start) > timeout_ns){
	result = 1; //timeout
	//waited long enough
	goto bcout;
	
       }
        nk_timer_t *t = nk_timer_get_thread_default();

        if (!t) {
            ERROR("Failed to acquire timer for thread...\n");
            return errno;
        }

        struct op o = {  .timer = t };

        // the queues we will simultaneously be on
        nk_wait_queue_t *queues[2] = { c->wait_queue, t->waitq} ;
        // their condition checks no_check means sleep until explicit wakeup
        int (*condchecks[2])() = { no_check, check_timer };
        // and state
        void *states[2] = { &o, &o };

        //DEBUG("down sleep / timeout %s\n",s->name);

        if (nk_timer_set(t, timeout_ns - (now-start), NK_TIMER_WAIT_ONE, 0, 0, 0)) {
            ERROR("Cannot set timer\n");
            return errno;
        }

        if (nk_timer_start(t)) {
            ERROR("Cannot start timer\n");
            return errno;
        }

        
        NK_UNLOCK(&c->lock); 

	DEBUG("starting multiple sleep\n");

        nk_wait_queue_sleep_extended_multiple(2,queues,condchecks,states);

        DEBUG("returned from multiple sleep and checking\n");

	nk_timer_cancel(t);
 
        //nk_wait_queue_sleep(c->wait_queue);
        NK_LOCK(&c->lock);

        if (bc != *(volatile unsigned*)&(c->bcast_seq)) {
            goto bcout;
        }

        val = *(volatile unsigned long long*)&(c->wakeup_seq);
        now = nk_sched_get_realtime();
	
    } while (val == seq || val == *(volatile unsigned long long*)&(c->woken_seq));

    ++c->woken_seq;

bcout:

    --c->nwaiters;

    NK_UNLOCK(&c->lock);

    /* reacquire lock */
    pthread_mutex_lock(l);

    NK_PROFILE_EXIT();

    return result;

}
int
pthread_cond_wait (pthread_cond_t * c, pthread_mutex_t * l)
{
    NK_PROFILE_ENTRY();
    if (c == NULL){
      return EINVAL;
		      
    }
    DEBUG("Condvar wait on (%p) mutex=%p\n", (void*)c, (void*)l);

    NK_LOCK(&c->lock);

    /* now we can unlock the mutex and go to sleep */
    pthread_mutex_unlock(l);

    ++c->nwaiters;
    ++c->main_seq;

    unsigned long long val;
    unsigned long long seq;
    unsigned bc = *(volatile unsigned*)&(c->bcast_seq);
    val = seq = c->wakeup_seq;

    do {

        NK_UNLOCK(&c->lock);
        nk_wait_queue_sleep(c->wait_queue);
        NK_LOCK(&c->lock);

        if (bc != *(volatile unsigned*)&(c->bcast_seq)) {
            goto bcout;
        }

        val = *(volatile unsigned long long*)&(c->wakeup_seq);
   } while (val == seq || val == *(volatile unsigned long long*)&(c->woken_seq));

    ++c->woken_seq;

bcout:

    --c->nwaiters;

    NK_UNLOCK(&c->lock);

    /* reacquire lock */
    pthread_mutex_lock(l);

    NK_PROFILE_EXIT();

    return 0;

}				/* pthread_cond_wait */

