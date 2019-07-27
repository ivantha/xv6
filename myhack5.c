//mkdir home
//mkdir home/ucsc

#include "types.h"
#include "stat.h"
#include "user.h"

int main(void) {
    printf(1, "Size of a given inode: %d \n", getinodesize("home/ucsc"));
    exit();
}