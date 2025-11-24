#!/bin/bash

gcc -Ofast -march=native -flto -o ./Main ./Main.c ./CreateIsEven.c
./Main