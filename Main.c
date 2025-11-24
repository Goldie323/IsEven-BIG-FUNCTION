#include <stdio.h>
#include <stdbool.h>
#include "CreateIsEven.h"

int main(int argc, char *argv[]) {
    if (argc != 4) {
        printf("Usage: %s <0|1> <number> <cfile>\n", argv[0]);
        return 1;
    }
    bool flag = atoi(argv[1]) != 0;
    unsigned long int num = strtoul(argv[2], NULL, 10);
    CreateIsEvenFile(flag, num, argv[3]);
    return 0;
}