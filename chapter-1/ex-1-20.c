#include "stdio.h"

#define SPACES_PER_TAB 8
#define MAX_LINE_LEN 100

int readline(char *buff);
void detab(char *buff);
int find_nullbyte_index(char *buff);
void print_spaces(void);

int main(void)
{
    char buff[MAX_LINE_LEN];
    int status = 0;
    int print = 0;

    while(status != -1) // -1 => EOF
    {
        buff[0] = '\0';
        status = readline(buff);
        if(status == 1) {
            detab(buff);
        }
    }

    return 0;
}

int readline(char *buff)
{
    size_t i = 1;
    while( i < MAX_LINE_LEN )
    {
        char c = getchar();
        if (c == EOF ) return -1;
        if (c == '\n') return 1;
        buff[i-1] = c;
        buff[i] = '\0';
        i++;
    }
    return 1;
}

int find_nullbyte_index(char *buff)
{
    int i = 0;
    while(buff[i] != '\0') i++;
    return i;
}

void print_spaces()
{
    for(int i = 0; i < SPACES_PER_TAB; ++i) putchar(' ');
}


void detab(char *buff)
{
    int i;
    int nullbyteidx = find_nullbyte_index(buff);
    for (i = 0; i < nullbyteidx; ++i)
    {
        if(buff[i] == '\t')
            print_spaces();
        else putchar(buff[i]);
    }
}