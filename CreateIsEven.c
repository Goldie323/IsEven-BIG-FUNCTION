#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define FUNCTIONDEF "int IsEven(int a) {\n"
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

unsigned long int addNumber(char *variable, unsigned long int num, unsigned long int currentSize) {
    unsigned long int modulo = num % 10;
    unsigned long int divided = num / 10;
    variable[currentSize++] = modulo+ASCIIZERO;
    while (divided != 0) {
        modulo = divided % 10;
        divided = divided / 10;
        variable[currentSize++] = modulo+ASCIIZERO;
    }
    return currentSize;
}

char *CreateIsEven(bool tabs, unsigned long int howFar) {
    char indent[5];
    unsigned long int indentSize = 0;
    char *functionString = NULL;
    unsigned long int functionLen = 0;
    unsigned long int functionCap = 0;
    if (tabs) {
        indentSize = sizeof(TABS)-1;
        memcpy(indent, TABS, indentSize);
    }
    else {
        indentSize = sizeof(SPACES)-1;
        memcpy(indent, SPACES, indentSize);
    }
    functionString = realloc(functionString, 4096);
    if (!functionString) exit(-1);
    functionCap = 4096;
    functionLen = sizeof(FUNCTIONDEF)-1;
    memcpy(functionString, FUNCTIONDEF, functionLen); // pretty sure it's 20 chars, I hope it is at least.
    

    bool isEven = 1;
    for (unsigned long int i = 0; i < howFar; i++) {
        if (functionCap-functionLen<EXTRASPACE) {
            functionCap *= MULTIPLICATEMEM;
            functionString = realloc(functionString, functionCap);
            if (!functionString) exit(-1);
        }

        memcpy(functionString+functionLen, indent, indentSize);
        functionLen += indentSize;

        memcpy(functionString+functionLen, STIFSTATEMENT, sizeof(STIFSTATEMENT)-1);
        functionLen += sizeof(STIFSTATEMENT)-1;
        functionLen = addNumber(functionString, i, functionLen);
        memcpy(functionString+functionLen, EDIFSTATEMENT, sizeof(EDIFSTATEMENT)-1);
        functionLen += sizeof(EDIFSTATEMENT)-1;

        memcpy(functionString+functionLen, indent, indentSize);
        functionLen += indentSize;
        memcpy(functionString+functionLen, indent, indentSize);
        functionLen += indentSize;

        if (isEven) {
            memcpy(functionString+functionLen, RETURNSTAT1, sizeof(RETURNSTAT1)-1);
            functionLen += sizeof(RETURNSTAT1)-1;
            isEven = false;
        }
        else {
            memcpy(functionString+functionLen, RETURNSTAT0, sizeof(RETURNSTAT0)-1);
            functionLen += sizeof(RETURNSTAT0)-1;
            isEven = true;
        }

        memcpy(functionString+functionLen, indent, indentSize);
        functionLen += indentSize;
        
        memcpy(functionString+functionLen, OUTSIDEIF, sizeof(OUTSIDEIF)-1);
        functionLen += sizeof(OUTSIDEIF)-1;
    }
    memcpy(functionString+functionLen, indent, indentSize);
    functionLen += indentSize;


    memcpy(functionString+functionLen, RETURNSTAT2, sizeof(RETURNSTAT2)-1);
    functionLen += sizeof(RETURNSTAT2)-1;

    functionString[functionLen] = '\0';
    return functionString;
}