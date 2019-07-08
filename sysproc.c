#include "types.h"
#include "x86.h"
#include "defs.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"
#include "guestSysCalls.h"

int
sys_fork(void)
{
  return fork();
}

int
sys_exit(void)
{
  exit();
  return 0;  // not reached
}

int
sys_wait(void)
{
  return wait();
}

int
sys_kill(void)
{
  int pid;

  if(argint(0, &pid) < 0)
    return -1;
  return kill(pid);
}

int
sys_getpid(void)
{
  return proc->pid;
}

int
sys_sbrk(void)
{
  int addr;
  int n;

  if(argint(0, &n) < 0)
    return -1;
  addr = proc->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

int
sys_sleep(void)
{
  int n;
  uint ticks0;
  
  if(argint(0, &n) < 0)
    return -1;
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(proc->killed){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

// return how many clock tick interrupts have occurred
// since start.
int
sys_uptime(void)
{
  uint xticks;
  
  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}

// return the year of which Unix version 6 was released
int
sys_getyear(void)
{
  return 1975;
}

// return the size of the address space of the current program
int
sys_getmysize(void)
{
    int size;
    size = proc->sz;

    return size;
}

// starting of the virtual addresses in the kernal area
int
sys_getkernelstartaddr(void)
{
    return KERNBASE;
}

// ending of the virtual addresses in the kernal area
int
sys_getkernelendaddr(void)
{
    return KERNBASE + PHYSTOP;
}

// create int variable and return its address
int
sys_getkernelvariaddr(void)
{
    int i = 1;
    int addr = (int)&i;
    return addr;
}

// address of the sys_fork() system call
int
sys_getsystemcalladdr(void)
{
    int addr = (int)&sys_fork;
    return addr;
}

// set priority
int
sys_setpriority(void) {
    int priority;
    if(argint(0, &priority) < 0)
        return -1;

    proc->priority = priority;
    return priority;
}

// get ps
int
sys_mycall(void) {
    return 1;
}
// hotd9
int sys_vmtrap(void) {
    int funcId;
    argint(0, &funcId);
    if (strncmp(proc->parent->name, "guestVM", 7) == 0) {
        return gtrap(funcId);
    } else {
        return kill(proc->pid);
    }
}