#include <nautilus/nautilus.h>
#include "pthread.h"

int pthread_yield(void) {
	return sched_yield();
}

int pthread_setaffinity_np() {
	nk_vc_printf("setaffinity\n");
	return 0;
}
