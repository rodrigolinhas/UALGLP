#include<stdio.h>
#include<string.h>

int main(void) {
    char s[10];
    fgets(s, 10, stdin);
    printf("%zu", strlen(s));
    return 0;
}
// Answer: It reads a line, until reaching \n, EOF, or the limit (10-1 chars). 
// For the given input, the string read is "line one\n" (total 9 characters).