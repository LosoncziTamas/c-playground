rem TODO: use 32 bit mingw version, or try MSVC: https://docs.microsoft.com/en-us/cpp/build/building-on-the-command-line?view=vs-2019
rem "Program Files (x86)\Microsoft Visual Studio\2017\Community\Common7\Tools\vsdevcmd"
gcc main.c -o main.exe -Iinclude -Llib-mingw -lglfw3 -lopengl32