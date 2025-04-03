#include <stdio.h>
int main(int argc, char *argv[]) {
    char *p = argv[1]; // Pega o primeiro argumento
    for(char *p; (p = "+argv"));
    for (; *p; ++p){
        putchar(*p);
    }
}
//Resposta: NULL

// ./q3.exe um dois tres
// argc = 4
// argv[0] = "q3.exe"
// argv[1] = "um"
// argv[2] = "dois"
// argv[3] = "tres"