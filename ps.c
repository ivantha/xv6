#include "types.h"
#include "stat.h"
#include "user.h"

#define NUM_STRUCTS 10

typedef struct {
    int occupied;

    int value1;
    int value2;
} info;

int main(void) {
    info info_array[NUM_STRUCTS];
    info *p;

    int return_val = mycall(NUM_STRUCTS * sizeof(info), &info_array);
    p = &info_array[0];

    while (p != &info_array[NUM_STRUCTS - 1] && p->occupied == 1) {
        printf(1, "%d %d \n", p->value1, p->value2);
        p++;
    }

    printf(1, "Program %d \n", return_val);
    exit();
}