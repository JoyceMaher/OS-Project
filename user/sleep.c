#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char *argv[])
{
    if (argc != 2) {
        printf("Usage: sleep ticks\n");
        exit(1);
    }

    int sleeptime = atoi(argv[1]);
    if (sleeptime <= 0) {
        printf("Error: sleep time must be positive\n");
        exit(1);
    }

    if (sleep(sleeptime) < 0) {
        printf("Error: sleep failed\n");
        exit(1);
    }

    exit(0);
}
