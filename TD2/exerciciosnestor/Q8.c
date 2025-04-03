#include<stdio.h>
void initArray() {
    int array[3];
    int i = 3, x = 3;
    while (--i && (array[i] = --x)) // Undefined behavior (array[3] out of bounds)
        printf("%d ", array[i]);
}

int main(void) { 
    initArray(); 
    return 0; 
}
// Resposta: 2 1