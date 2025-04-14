#include <stdio.h>
void swap(int* x, int* y) {
    int tmp = *x;
    *x = *y;
    *y = tmp;
}
int main(void) {
    int a = 33;
    int b = 55;
    swap(&a,&b);
    printf("%d %d\n",a,b);
}

// Resposta: 55 33