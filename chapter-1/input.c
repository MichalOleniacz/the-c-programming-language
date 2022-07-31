#include <stdio.h>

int main()
{
    int c;

    int test = getchar() != EOF;
    printf("%d\n",test);
    while ((c = getchar()) != EOF)
        putchar(c);
}