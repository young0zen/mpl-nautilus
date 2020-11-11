#ifndef _PTHREAD_SIMPLE_SEM_H_
#define _PTHREAD_SIMPLE_SEM_H_

#include<nautilus/spinlock.h>

struct simple_sem{
  NK_LOCK_T* lock;
  int count;
};


typedef struct simple_sem simple_sem_t;

int ssem_timedwait( simple_sem_t *s, uint64_t timeout_ns);
void ssem_init(simple_sem_t *s, int initial_count);

void ssem_post(simple_sem_t *s, int count);

void ssem_wait( simple_sem_t *s);

#endif
