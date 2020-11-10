#include "ssem.h"

struct simple_sem{
  NK_LOCK_T* lock;
  int count;
};

void ssem_init(simple_sem_t *s, int initial_count){
  NK_LOCK_INT(s->lock);
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
   }

    NK_UNLOCK(s->lock);
}
