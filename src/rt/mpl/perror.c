#include <nautilus/nautilus.h>
void perror(const char *s) {
	nk_vc_printf("%s\n", s);
}
