#!/bin/sh

# -Wl tells the compiler front-end to pass an option to the linker
# -rpath adds a path to the runtime-linker search path
LINKER_FLAGS="-L./lib-mac -lglfw3 -Wl,-rpath,./lib-mac"
# Required frameworks
FRAMEWORKS="-framework OpenGL -framework Cocoa -framework IOkit -framework CoreVideo"
# Performing compilation & dynamic linking
clang main.c -o main.out -g -I./include $LINKER_FLAGS $FRAMEWORKS