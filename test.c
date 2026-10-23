#include <stdio.h>
#include <stdlib.h>

int main ()
{
    char *p = malloc (sizeof(char));

    p[9] = 'a';
    printf("%c\n", p[9]);

    free(p);

}