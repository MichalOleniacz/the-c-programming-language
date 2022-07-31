#include <stdio.h>

#define MAXLINE 10

int _getline(char line[], int maxline);
void copy(char to[], char from[]);

int main()
{
    int len;
    int max = 0;
    char line[MAXLINE];
    char longest[MAXLINE];

    while((len = _getline(line, MAXLINE)) > 0)
    {
        if(len > max)
        {
            max = len;
            copy(longest,line);
        }
    }
    if (max > 0)
        printf("\n%d characters in %s", max, longest);
    return 0;
}

int _getline(char s[], int lim)
{
    int c, i;
    i = 0;
    while ((c = getchar()) != EOF)
    {
        ++i;
        if(i < lim - 2)
        {
            s[i - 1] = c;
            s[i] = '\0';
        }    
    }
    return i;
}

void copy(char to[], char from[])
{
    int i;
    i = 0;

    while((to[i] = from[i]) != '\0')
        ++i;
}
