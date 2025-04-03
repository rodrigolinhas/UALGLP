#include<stdio.h>

int main(void) {
    char arr[] = "abcc";

    *(arr + 3) = 'd';
    puts(arr);

    return 0;
}
// Answer: abcd