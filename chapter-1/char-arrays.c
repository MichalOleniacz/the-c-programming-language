#include <stdio.h>

#define MAXLINE 1000

int _getline(char line[], int maxline);
void copy(char to[], char from[]);

int main()
{
    int len; // current line length
    int max = 0; // maximum length seen so far
    char line[MAXLINE]; // curent input line
    char longest[MAXLINE]; // longest line saved

    while((len = _getline(line, MAXLINE)) > 0)
    {
        if(len > max)
        {
            max = len;
            copy(longest, line);
        }
    }
    if (max > 0)
        printf("%s", longest);
    return 0;
}

int _getline(char s[], int lim)
{
    int c, i;
    for(i=0; i<lim-1 && (c=getchar())!=EOF && c!='\n'; ++i)
        s[i] = c;
    if(c == '\n')
    {
        s[i] = c;
        ++i;
    }
    s[i] = '\0';
    return i;
}

void copy(char to[], char from[])
{
    int i;

    i = 0;
    while((to[i] = from[i]) != '\0')
        ++i;
}
