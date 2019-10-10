#!/bin/sh

clang -c common.c -o common.o
clang -c window_mac.mm -o window_mac.o
clang common.o window_mac.o -o window.out -framework Cocoa