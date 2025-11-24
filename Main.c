#include <stdio.h>
#include <stdbool.h>
#include "CreateIsEven.h"

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s <0|1> <number>\n", argv[0]);
        return 1;
    }
    bool flag = atoi(argv[1]) != 0;
    unsigned long int num = strtoul(argv[2], NULL, 10);
    char *function = CreateIsEven(flag, num);
    FILE *fp = fopen("IsEven.c", "w");
    if (!fp) {
        printf("Error opening file!\n");
        return 1;
    }
    fprintf(fp, "%s", function);
    fclose(fp);
    return 0;
}