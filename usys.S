#include "syscall.h"
#include "traps.h"

#define SYSCALL(name) \
  .globl name; \
  name: \
    movl $SYS_ ## name, %eax; \
    int $T_SYSCALL; \
    ret

SYSCALL(fork)
SYSCALL(exit)
SYSCALL(wait)
SYSCALL(pipe)
SYSCALL(read)
SYSCALL(write)
SYSCALL(close)
SYSCALL(kill)
SYSCALL(exec)
SYSCALL(open)
SYSCALL(mknod)
SYSCALL(unlink)
SYSCALL(fstat)
SYSCALL(link)
SYSCALL(mkdir)
SYSCALL(chdir)
SYSCALL(dup)
SYSCALL(getpid)
SYSCALL(sbrk)
SYSCALL(sleep)
SYSCALL(uptime)

// Lecture 2
SYSCALL(getyear)

// HOTD 2
SYSCALL(getmysize)

// HOTD 3
SYSCALL(getkernelstartaddr)
SYSCALL(getkernelendaddr)
SYSCALL(getkernelvariaddr)
SYSCALL(getkernelcalladdr)

// HOTD 4
SYSCALL(setpriority)

// HOTD 5
SYSCALL(getinodesize)

// HOTD 9
SYSCALL(vmtrap)