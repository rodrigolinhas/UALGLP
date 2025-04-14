#include <stdio.h>
int main(int argc, char *argv[]) {
    for(char *p; (p = *++argv);){
        for (; *p; ++p){
            putchar(*p);
        }    
    }
}
//Resposta: onetwothree

// ./q3.exe one two three
// argc = 4
// argv[0] = "q3.exe"
// argv[1] = "one"
// argv[2] = "two"
// argv[3] = "three"