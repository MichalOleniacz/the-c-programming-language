#include <stdio.h>

#define IN 1
#define OUT 0

int main()
{

    char c;
    int state;


    while((c=getchar()) != EOF)
    {
        if(c == ' ' || c == '\n' || c == '\t')
        {
            printf("\n");
            state = OUT;
        }
        else if(state == OUT)
        {
            state = IN;
            printf("%c", c);
        }
        else if(state == IN)
            printf("%c", c);
    }
}
