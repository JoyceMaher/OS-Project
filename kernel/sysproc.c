#include "types.h"
#include "riscv.h"
#include "defs.h"
#include "param.h"
#include "memlayout.h"
#include "spinlock.h"
#include "proc.h"


//int argint(int, int*);
//int argaddr(int, uint64*);
//int argstr(int, char*, int);

extern int sched_mode;
uint64
sys_exit(void)
{
  int n;
  argint(0, &n);
  exit(n);
  return 0;  // not reached
}

uint64
sys_getpid(void)
{
  return myproc()->pid;
}

uint64
sys_getptable(void)
{
    int count = 0;

    struct proc *p = proc;

    for(int i = 0; i < NPROC; i++){
        if(p[i].state != UNUSED){
            count++;
        }
    }

    return count;
}

extern uint64 syscall_count;

uint64
sys_countsyscall(void)
{
    return syscall_count;
}

uint64
sys_fork(void)
{
  return fork();
}

uint64
sys_wait(void)
{
  uint64 p;
  argaddr(0, &p);
  return wait(p);
}

uint64
sys_sbrk(void)
{
  uint64 addr;
  int n;

  argint(0, &n);
  addr = myproc()->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

uint64
sys_sleep(void)
{
  int n;
  uint ticks0;

  argint(0, &n);
  if(n < 0)
    n = 0;
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(killed(myproc())){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

uint64
sys_kill(void)
{
  int pid;

  argint(0, &pid);
  return kill(pid);
}

// return how many clock tick interrupts have occurred
// since start.
uint64
sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}

uint64
sys_sysrand(void)
{
  static uint32 seed = 1;
  const uint32 a = 1664525;
  const uint32 c = 1013904223;

  seed = a * seed + c;

  return (uint64)seed;
}

uint64
sys_datetime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);

  #ifdef BUILD_TIME
  return BUILD_TIME + (xticks / 100);
  #else
  return xticks / 100;
  #endif
}

uint64
sys_set_scheduler(void)
{
  struct proc *p = myproc();
  int mode = p->trapframe->a0;  // Direct access - no argint needed

  // Validate mode (0-3)
  if(mode < 0 || mode > 3)
    return -1;

  sched_mode = mode;
  return 0;
}

uint64
sys_get_scheduler(void)
{
  return sched_mode;
}
