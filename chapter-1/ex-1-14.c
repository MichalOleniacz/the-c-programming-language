#include <stdio.h>

#define NUMBER_OF_CHARS 26

int main()
{
    char c;
    int counter[NUMBER_OF_CHARS];
    char chars[] = {'a', 'b','c','d','e','f','g','h','i','j','k',
        'l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};

    for(int i = 0; i < NUMBER_OF_CHARS; ++i)
        counter[i] = 0;

    while((c=getchar())!=EOF)
    {
        if(c >= 'a' && c <= 'z')
        {
            ++counter[c-'a'];
        }
    }

    printf("\n");
    for(int i = 0; i < NUMBER_OF_CHARS; ++i)
    {
        printf("%c: ", chars[i]);
        for(int j = 0; j < counter[i]; ++j)
            printf("||");
        printf("\n");
    }

}
