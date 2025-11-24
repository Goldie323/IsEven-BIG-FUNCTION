#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

#define FUNCTIONDEF "int IsEven(unsigned long int a) {\n"
#define STIFSTATEMENT "if (a=="
#define EDIFSTATEMENT ") {\n"
#define RETURNSTAT0 "return 0;\n"
#define RETURNSTAT1 "return 1;\n"
#define RETURNSTAT2 "return -1;\n}"
#define OUTSIDEIF "}\n"
#define TABS "\t"
#define SPACES "    "
#define ASCIIZERO 48
#define EXTRASPACE 500
#define MULTIPLICATEMEM 2

#define ASCIIZERO 48

unsigned long int addNumber(char *variable, unsigned long int num, unsigned long int currentSize) {
    if (num == 0) {
        variable[currentSize++] = '0';
        return currentSize;
    }
    unsigned long int temp = num;
    unsigned long int digits[20]; // enough for 64-bit unsigned long
    unsigned int count = 0;
    while (temp != 0) {
        digits[count++] = temp % 10;
        temp /= 10;
    }
    for (int i = count - 1; i >= 0; i--) {
        variable[currentSize++] = digits[i] + ASCIIZERO;
    }
    return currentSize;
}

int CreateIsEvenFile(bool tabs, unsigned long int howFar, const char *outPath) {
    char indent[8];
    unsigned long int indentSize = 0;
    if (tabs) {
        indentSize = sizeof(TABS)-1;
        memcpy(indent, TABS, indentSize);
    }
    else {
        indentSize = sizeof(SPACES)-1;
        memcpy(indent, SPACES, indentSize);
    }

    size_t s_FUNCTIONDEF = sizeof(FUNCTIONDEF)-1;
    size_t s_STIF = sizeof(STIFSTATEMENT)-1;
    size_t s_EDIF = sizeof(EDIFSTATEMENT)-1;
    size_t s_RETURN0 = sizeof(RETURNSTAT0)-1;
    size_t s_RETURN1 = sizeof(RETURNSTAT1)-1;
    size_t s_RETURN2 = sizeof(RETURNSTAT2)-1;
    size_t s_OUTSIDEIF = sizeof(OUTSIDEIF)-1;

    unsigned long int digits_max = 1;
    if (howFar > 1) {
        unsigned long int tmp = howFar - 1;
        digits_max = 0;
        while (tmp != 0) {
            digits_max++;
            tmp /= 10;
        }
    }

    size_t per_iter = 0;
    per_iter += indentSize;
    per_iter += s_STIF + digits_max + s_EDIF;
    per_iter += indentSize * 2;
    per_iter += (s_RETURN0 > s_RETURN1 ? s_RETURN0 : s_RETURN1);
    per_iter += indentSize;
    per_iter += s_OUTSIDEIF;
    size_t total_est = s_FUNCTIONDEF + howFar * per_iter + indentSize + s_RETURN2 + 1 + EXTRASPACE;

    int fd = open(outPath, O_RDWR | O_CREAT | O_TRUNC, 0666);
    if (fd < 0) {
        perror("open");
        return -1;
    }
    if (ftruncate(fd, (off_t)total_est) != 0) {
        perror("ftruncate");
        close(fd);
        return -1;
    }

    char *map = mmap(NULL, total_est, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (map == MAP_FAILED) {
        perror("mmap");
        close(fd);
        return -1;
    }

    unsigned long int functionLen = 0;
    bool isEven = 1;

    memcpy(map + functionLen, FUNCTIONDEF, s_FUNCTIONDEF);
    functionLen += s_FUNCTIONDEF;

    for (unsigned long int i = 0; i < howFar; i++) {
        printf("%lu\n", i);
        memcpy(map + functionLen, indent, indentSize);
        functionLen += indentSize;

        memcpy(map + functionLen, STIFSTATEMENT, s_STIF);
        functionLen += s_STIF;

        functionLen = addNumber(map, i, functionLen);

        memcpy(map + functionLen, EDIFSTATEMENT, s_EDIF);
        functionLen += s_EDIF;

        memcpy(map + functionLen, indent, indentSize);
        functionLen += indentSize;
        memcpy(map + functionLen, indent, indentSize);
        functionLen += indentSize;

        if (isEven) {
            memcpy(map + functionLen, RETURNSTAT1, s_RETURN1);
            functionLen += s_RETURN1;
            isEven = false;
        } else {
            memcpy(map + functionLen, RETURNSTAT0, s_RETURN0);
            functionLen += s_RETURN0;
            isEven = true;
        }

        memcpy(map + functionLen, indent, indentSize);
        functionLen += indentSize;

        memcpy(map + functionLen, OUTSIDEIF, s_OUTSIDEIF);
        functionLen += s_OUTSIDEIF;
    }

    memcpy(map + functionLen, indent, indentSize);
    functionLen += indentSize;
    memcpy(map + functionLen, RETURNSTAT2, s_RETURN2);
    functionLen += s_RETURN2;

    if (functionLen < total_est) {
        map[functionLen] = '\0';
    }

    if (msync(map, functionLen + 1, MS_SYNC) != 0) {
        perror("msync");
    }
    if (munmap(map, total_est) != 0) {
        perror("munmap");
    }
    close(fd);
    return 0;
}