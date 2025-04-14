#include<stdio.h>
#include<string.h>

int main(void) {
    char s[10];
    scanf("%9s", s);
    printf("%zu", strlen(s));
    return 0;
}
// Answer: It reads a word, until reaching whitespace or 9 characters. 
// For the given input, the string read s is: "line".