#!/bin/sh

LINKER_FLAGS="-L./lib-mac -lglfw3"
# Required frameworks
FRAMEWORKS="-framework OpenGL -framework Cocoa -framework IOkit -framework CoreVideo"
# Performing static linking
clang glad.c main.c -o main.out -Wall -g -I./include $LINKER_FLAGS $FRAMEWORKS