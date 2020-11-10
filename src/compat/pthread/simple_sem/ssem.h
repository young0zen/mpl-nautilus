#ifndef _PTHREAD_SIMPLE_SEM_H_
#define _PTHREAD_SIMPLE_SEM_H_

#include<nautilus/spinlock.h>

struct simple_sem{
  spin_lock_t* lock;
  int count;
};


typedef simple_sem simple_sem_t;

void ssem_init(simple_sem_t *s, int initial_count);

void ssem_post(simple_sem_t *s, int count);

void ssem_wait( simple_sem_t *s);

#endif
