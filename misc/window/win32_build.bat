@ECHO OFF

gcc -Wall -c common.c -o common.o
gcc -Wall -c window_win32.cpp -o window_win32.o
gcc -Wall common.o window_win32.o -o window.exe -mwindows