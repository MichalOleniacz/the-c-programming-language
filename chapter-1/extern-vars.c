#include <stdio.h>

#define MAXLINE 10

int max;
char line[MAXLINE];
char longest[MAXLINE];

int _getline(void);
void copy(void);

int main()
{
    int len;
    extern int max;
    extern char line[];
    extern char longest[];

    max = 0;

    while((len = _getline()) > 0)
    {
        if(len > max)
        {
            max = len;
            copy();
        }
    }
    if (max > 0)
        printf("\n%d characters in %s", max, longest);
    return 0;
}

int _getline(void)
{
    extern char line[];
    int c, i;
    i = 0;
    while ((c = getchar()) != EOF)
    {
        ++i;
        if(i < MAXLINE - 2)
        {
            line[i - 1] = c;
            line[i] = '\0';
        }
    }
    return i;
}

void copy(void)
{
    extern char line[], longest[];
    int i;
    i = 0;

    while((longest[i] = line[i]) != '\0')
        ++i;
}
