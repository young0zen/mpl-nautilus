#include <nautilus/nautilus.h>
#include <nautilus/libccompat.h>

struct itimerval {
	struct timeval it_interval;
	struct timeval it_value;
};

int putchar(int c) {
	nk_vc_printf("%s", c);
	return c;
}

int setitimer(int which, const struct itimerval *new_value,
                     struct itimerval *old_value) {

	return 0;
}

typedef struct {
	void  *ss_sp;     /* Base address of stack */
	int    ss_flags;  /* Flags */
	size_t ss_size;   /* Number of bytes in stack */
} stack_t;

int sigaltstack(const stack_t *restrict ss, stack_t *restrict old_ss) {
	return 0;
}

//int ___lxstat64 (int vers, const char *name, struct stat64 *buf)
int __lxstat64 ()
{
	nk_vc_printf("lxstat64\n");
	return 0;
}

int __xstat64 ()
{
	nk_vc_printf("lxstat64\n");
	return 0;
}

//int fstat() {
//	nk_vc_printf("fstat\n");
//	return 0;
//}
//int lstat() {
//	nk_vc_printf("lstat\n");
//	return 0;
//}
//
//int stat() {
//	return 0;
//}
