#include <stdio.h>

#define LOWER 0
#define UPPER 300
#define STEP 20

int main()
{
    int fahr, cels;
    cels = LOWER;

    printf("Celc -> fahr table:\n");
    while (cels <= UPPER) 
    {
        fahr = (cels * 9/5) + 32;
        printf("%d\t%d\n",cels, fahr);
        cels = cels + STEP;
    }
}