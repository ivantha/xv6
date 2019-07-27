#include "types.h"
#include "x86.h"
#include "defs.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"

#include "guestSysCalls.h"

int
sys_fork(void) {
    return fork();
}

int
sys_exit(void) {
    exit();
    return 0;  // not reached
}

int
sys_wait(void) {
    return wait();
}

int
sys_kill(void) {
    int pid;

    if (argint(0, &pid) < 0)
        return -1;
    return kill(pid);
}

int
sys_getpid(void) {
    return proc->pid;
}

int
sys_sbrk(void) {
    int addr;
    int n;

    if (argint(0, &n) < 0)
        return -1;
    addr = proc->sz;
    if (growproc(n) < 0)
        return -1;
    return addr;
}

int
sys_sleep(void) {
    int n;
    uint ticks0;

    if (argint(0, &n) < 0)
        return -1;
    acquire(&tickslock);
    ticks0 = ticks;
    while (ticks - ticks0 < n) {
        if (proc->killed) {
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
sys_uptime(void) {
    uint xticks;

    acquire(&tickslock);
    xticks = ticks;
    release(&tickslock);
    return xticks;
}


// Lecture 2
int
sys_getyear(void) {
    return 1975;
}

// HOTD 2
int
sys_getmysize(void) {
    int sz;
    sz = proc->sz;
    return sz;
}

// HOTD 3
int
sys_getkernelstartaddr(void) {
    int addr = (int) P2V(0);
    return addr;
}

int
sys_getkernelendaddr(void) {
    int addr = (int) p2v(PHYSTOP);
    return addr;
}

int
sys_getkernelvariaddr(void) {
    int i = 1;
    int addr = (int) &i;
    return addr;
}

int
sys_getkernelcalladdr(void) {
    int addr = (int) &sys_fork;
    return addr;
}

// HOTD 4
int
sys_setpriority(void) {
    int priority;

    if (argint(0, &priority) < 0)
        return -1;

    proc->priority = priority;
    return priority;
}

int
sys_vmtrap(void) {
    int sys_call_num;

    if(argint(0, &sys_call_num) < 0){
        return -1;
    }

    if(strncmp(proc->parent->name, "guestVM", 7) == 0){
        return gtrap(sys_call_num);
    }else{
        return kill(proc->pid);
    }
}