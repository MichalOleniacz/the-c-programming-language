#include <stdio.h>

int main()
{
    int fahr, cels;
    int lower, upper, step;

    lower = 0;
    upper = 300;
    step = 20;

    cels = lower;

    printf("Celc -> fahr table:\n");

    while (cels <= upper) 
    {
        fahr = (cels * 9/5) + 32;
        printf("%d\t%d\n",cels, fahr);
        cels = cels + step;
    }
}