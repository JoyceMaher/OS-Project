#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char *argv[])
{
  int i;

  printf("Testing sysrand() system call:\n");
  for(i = 0; i < 10; i++) {
    printf("Random number %d: %d\n", i, sysrand());
  }

  exit(0);
}
