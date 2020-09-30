#include <nautilus/nautilus.h>
#include <nautilus/shell.h>

static int size = 5;
static int a[5][5];
static int b[5][5];
#pragma omp threadprivate(b,a)


static int toy(char *buf, void* priv);

static struct shell_cmd_impl nas_toy_impl = {
    .cmd      = "toy",
    .help_str = "NAS parallel benchmark BT",
    .handler  = toy,
};
nk_register_shell_cmd(nas_toy_impl);

static int toy(char *buf, void* priv) {

#pragma omp parallel
  {
    int i =0,j=0;
    #pragma omp for
    for(i =0;i<size;i++){
      for(j=0; j< size;j++){
	a[i][j] = i+j;
	b[i][j] = i-j;
	//printf("%d\n",a[i][j]);
      }
    }
    for(i =0;i<size;i++){
      for(j=0; j< size;j++){
	printf("i %d, j %d, %d %d\n", i,j, a[i][j], b[i][j]);
      }
    }

    

  }


}
