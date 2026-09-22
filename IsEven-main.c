#include <stdio.h>
#include <stdlib.h>
#include "IsEven.c"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <number>", argv[0]);
        return 1;
    }
    unsigned long int num = strtoul(argv[1], NULL, 10);
    int Even = IsEven(num);
    if (Even) printf("Number is Even\n");
    else printf("Number is Odd\n");
    return 0;
}
