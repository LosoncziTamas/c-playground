#!/bin/sh

LINKER_FLAGS="-L./build-mac build-mac/libglfw.3.dylib -Wl,-rpath,./build-mac"
# Performing compilation & dynamic linking
clang src/*.c -o build-mac/main.out -Wall -g -I./include $LINKER_FLAGS