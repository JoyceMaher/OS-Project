#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
    int count = getptable();
    printf("Number of processes in table: %d\n", count);

    if(count >= 2) {
        printf("getptable() working correctly!\n");
    } else {
        printf("Warning: Expected at least 2 processes\n");
    }

    exit(0);
}
