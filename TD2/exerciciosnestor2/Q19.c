#include <stdlib.h>
#include <stdio.h>

int* retorna_ponteiro() {
    int* p = malloc(sizeof(int));
    (*p) = 33;
    return p;
}

int main(void) {
    int* p = retorna_ponteiro();
    printf("%i",(*p));
    return 0;
}
// Answer: Yes