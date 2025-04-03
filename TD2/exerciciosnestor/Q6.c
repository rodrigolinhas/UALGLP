#include<stdio.h>
int main() {
    int x, y, z;
    x = y = z = 1;    
    x += (y += z);
    printf("%d %d %d\n", x, y, z);
}
// Resposta: 3 2 1 1