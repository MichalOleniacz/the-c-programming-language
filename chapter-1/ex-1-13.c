#include <stdio.h>

#define MAX_WORDS 1000
#define DISPLAY_LIMIT 10
#define IN 1
#define OUT 0
int main()
{
    char c;
    int i, wc = 0;
    int char_count[MAX_WORDS];
    int state = OUT;

    for(i = 0;i < MAX_WORDS; ++i)
        char_count[i] = 0;

    while((c=getchar())!=EOF)
    {
        if(c == ' ' || c == '\n' || c == '\t')
        {
            state = OUT;
            ++wc;
        } else if (state == OUT)
        {
            state = IN;
            ++char_count[wc];
        } else
            ++char_count[wc];
    }

    for(int i = 0; i < DISPLAY_LIMIT; ++i)
    {
        printf("%d:", i);
        for(int j = 0; j < char_count[i]; ++j)
            printf("||||");
        printf("\n");
    }

}
