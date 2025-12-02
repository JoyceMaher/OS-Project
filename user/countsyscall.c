#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
    int count1 = countsyscall();
    printf("System calls before test: %d\n", count1);

    int pid = getpid();
    printf("My PID: %d\n", pid);

    int count2 = countsyscall();
    printf("System calls after getpid and printf: %d\n", count2);
    printf("Syscalls made by this test: %d\n", count2 - count1);

    for(int i = 0; i < 5; i++) {
        sleep(1);
    }

    int count3 = countsyscall();
    printf("Total system calls: %d\n", count3);

    exit(0);
}
