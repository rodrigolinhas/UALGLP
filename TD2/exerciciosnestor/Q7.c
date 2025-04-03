#include<stdio.h>
int main() {
    int x, y, z;
    x = y = z = 1;     
    (x += y) += z; // Erro aqui
    printf("%d %d %d\n", x, y, z);
    return 0;
}
// Resposta: Compile-time error