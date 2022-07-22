#include <nautilus/nautilus.h>
#include <nautilus/thread.h>

#include <nautilus/shell.h>

void
test_mpl_hello_world(void *input, void **output) {
	nk_vc_printf("testing mpl hello world\n");
	char *argv[] = {"testmpl", 0};
	mpl_main(1, argv);
	nk_vc_printf("test done\n");
}

static int
test_mpl() {
	//THREAD_T t;
	nk_thread_start(test_mpl_hello_world, NULL, NULL, 1, PAGE_SIZE_4KB, NULL, -1);
	//test_mpl_hello_world(NULL, NULL);
	return 0;
}

static int
handle_mpl(char *buf, void *priv)
{
	test_mpl();
	return 0;
}

static struct shell_cmd_impl mpl_impl = {
    .cmd      = "testmpl",
    .help_str = "testmpl",
    .handler  = handle_mpl,
};
nk_register_shell_cmd(mpl_impl);
