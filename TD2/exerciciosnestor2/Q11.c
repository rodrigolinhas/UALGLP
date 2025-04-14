#include<stdio.h>

int main(void) {
    char *str = "abcc";

    *(str + 3) = 'd';
    puts(str);
    
    return 0;
}
// Answer: Run-time error