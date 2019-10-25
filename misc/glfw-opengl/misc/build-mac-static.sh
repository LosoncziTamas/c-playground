#!/bin/sh

LINKER_FLAGS="-L./build-mac -lglfw3"
# Required frameworks
FRAMEWORKS="-framework OpenGL -framework Cocoa -framework IOkit -framework CoreVideo"
# Performing static linking
clang src/*.c -o build-mac/main.out -Wall -g -I./include $LINKER_FLAGS $FRAMEWORKS