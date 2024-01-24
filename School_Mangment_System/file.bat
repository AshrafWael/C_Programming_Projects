gcc main.c School.c -o project.exe
gcc -E main.c -o main.i
gcc -E School.c -o School.i
gcc -S main.c -o main.asm
gcc -S main.c -o School.asm
project.exe