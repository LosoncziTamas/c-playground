@echo off

rem https://www.transmissionzero.co.uk/computing/building-dlls-with-mingw/
rem use -Wl,-verbose flags for debugging linker locations
rem https://stackoverflow.com/a/5686083
rem https://stackoverflow.com/a/18362391

pushd build-mingw
gcc ..\src\*.c -o main.exe -g -I..\include -L. -lglfw3 -lopengl32
popd