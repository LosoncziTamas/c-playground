#!/bin/sh

# Statically linking against glfw requires adding Cocoa, OpenGL, IOKit and CoreVideo
FRAMEWORKS="-framework OpenGL -framework Cocoa -framework IOkit -framework CoreVideo"
clang main.c -o main.out -g -I./include -L./lib-mac -lglfw3 $FRAMEWORKS