#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(void) {
    char *t;
    const char *str = "item1 item2 item3 item4 item5";
    char *tmp = (char *)malloc(strlen(str) + 1);
    if (tmp == NULL) {
        exit(1);
    }
    strcpy(tmp, str);
    t = strtok(tmp, " ");
    printf("%s,", t);
    while (t = strtok(0, " "))
        printf("%s,", t);
    free(tmp);
    tmp = NULL;
    return 0;
}
// Resposta: item1,item2,item3,item4,item5,