@ECHO OFF

gcc -c common.c -o common.o
gcc -c window_win32.cpp -o window_win32.o
gcc common.o window_win32.o -o window.exe