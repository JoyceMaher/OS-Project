#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main()
{
    printf("Testing FCFS scheduler...\n");
    
    // Get current scheduler
    int mode = get_scheduler();
    printf("Current scheduler mode: %d (0=RR, 1=FCFS, 2=SJF, 3=Priority)\n", mode);
    
    // Test switching
    printf("\nSwitching to FCFS (mode 1)...\n");
    set_scheduler(1);
    printf("New mode: %d\n", get_scheduler());
    
    // Create test processes
    int pid1 = fork();
    if(pid1 == 0) {
        printf("Child 1 started (PID: %d)\n", getpid());
        sleep(100);
        printf("Child 1 finished\n");
        exit(0);
    }
    
    sleep(5); // Wait a bit
    
    int pid2 = fork();
    if(pid2 == 0) {
        printf("Child 2 started (PID: %d)\n", getpid());
        sleep(50);
        printf("Child 2 finished\n");
        exit(0);
    }
    
    sleep(5); // Wait a bit
    
    int pid3 = fork();
    if(pid3 == 0) {
        printf("Child 3 started (PID: %d)\n", getpid());
        sleep(10);
        printf("Child 3 finished\n");
        exit(0);
    }
    
    // Wait for all children
    wait(0);
    wait(0);
    wait(0);
    
    printf("\nTest complete. With FCFS:\n");
    printf("1. Child 1 (created first) should run to completion first\n");
    printf("2. Child 2 (created second) should run second\n");
    printf("3. Child 3 (created third) should run last\n");
    
    exit(0);
}
