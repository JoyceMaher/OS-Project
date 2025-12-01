#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
    int count = kbdint();
    printf("Keyboard: %d\n", count);
    exit(0);
}
