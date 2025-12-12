#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
  int p = getpid();
  int pp = getppid();
  printf("pid=%d ppid=%d\n", p, pp);
  exit(0);
}
