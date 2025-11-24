#include <stdio.h>
#include <stdbool.h>
#include "CreateIsEven.h"

int main() {
    char *function = CreateIsEven(true, 1000);
    FILE *fp;
    fp = fopen("IsEven.c", "w");
    if (fp == NULL) {
        printf("Error opening file!\n");
        return 1;
    }
    fprintf(fp, function);
    return 0;
}