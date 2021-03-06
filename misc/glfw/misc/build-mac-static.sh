#!/bin/sh

LINKER_FLAGS="-L./lib-mac -lglfw3"
# Required frameworks
FRAMEWORKS="-framework OpenGL -framework Cocoa -framework IOkit -framework CoreVideo"
# Performing static linking
clang main.c -o main.out -g -I./include $LINKER_FLAGS $FRAMEWORKS