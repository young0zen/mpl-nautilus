#include "ssem.h"


void ssem_init(simple_sem_t *s, int initial_count){
  NK_LOCK_INIT(s->lock);
  s->count = initial_count;
}

void ssem_post(simple_sem_t *s, int count){
    
    NK_LOCK(s->lock);
    s->count+=count;
    NK_UNLOCK(s->lock);
}

void ssem_wait( simple_sem_t *s){
    
   //int ori =  __sync_fetch_and_sub(&(s->count), 1);
   
   while(1){
      NK_LOCK(s->lock);
      if(s->count > 0){
	s->count--;
        break;
      }
      NK_UNLOCK(s->lock);
      nk_yield();
   }

    NK_UNLOCK(s->lock);
}
int ssem_timedwait( simple_sem_t *s, uint64_t timeout_ns){

   //int ori =  __sync_fetch_and_sub(&(s->count), 1);
   uint64_t start = nk_sched_get_realtime(), now;

   do{
      NK_LOCK(s->lock);
      if(s->count > 0){
        s->count--;
        break;
      }

      NK_UNLOCK(s->lock);
      //nk_yield();
      __asm__("pause");

      now = nk_sched_get_realtime();

      if( now-start > timeout_ns){
         NK_UNLOCK(s->lock);
        return 1;
      }
   }while(1);

    NK_UNLOCK(s->lock);
    return 0;
 }

