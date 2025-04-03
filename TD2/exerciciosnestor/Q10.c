#include<stdio.h>
int main() {
    char arr[] = "abcc";
    *(arr + 3) = 'd'; // Changes 'c' to 'd'
    puts(arr);
    return 0;
}
// Resposta: abcd