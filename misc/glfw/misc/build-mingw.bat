echo off
rem TODO: link properly, https://access.redhat.com/documentation/en-US/Red_Hat_Enterprise_Linux/4/html/Using_ld_the_GNU_Linker/win32.html
gcc main.c -o main.exe -Iinclude -Llib-mingw -lglfw3 -lopengl32