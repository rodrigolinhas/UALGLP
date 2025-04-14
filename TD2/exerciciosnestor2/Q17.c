#include<stdio.h>
#include<string.h>

int main(void) {
    char s[10];
    scanf("%10c", s);
    printf("%zu", strlen(s));
    return 0;
}
// Answer: It reads exactly 10 characters of any kind (including spaces or terminators). 
// s[] contains "line one\nl" (ending with the first 'l' character of line two), 
// no \0 terminator.