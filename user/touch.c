#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fcntl.h"

int
main(int argc, char *argv[])
{
  if(argc == 2 && strcmp(argv[1], "?") == 0) {
    printf("Usage: touch filename\n");
    exit(0);
  }

  if(argc != 2) {
    printf("touch: requires a filename\n");
    exit(0);
  }

  // Open with create flag, close immediately to produce an empty file.
  int fd = open(argv[1], O_WRONLY | O_CREATE);
  if(fd < 0) {
    printf("touch: cannot create file %s\n", argv[1]);
    exit(0);
  }

  close(fd);
  exit(0);
}
