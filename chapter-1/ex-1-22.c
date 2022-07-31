#include "stdio.h"

#define MAX_LINE_LEN 1024
#define MAX_PER_LINE 10
#define SPACE ' '
#define NEWLINE '\n'

int readline(char *buff);
void writeline(char *buff);
int find_nullbyte_index(char *buff);
void splitlines(char *buff);
int find_next_newline(char *buff, int startingpos, int nullbyteidx);

int main(void)
{
    char buff[MAX_LINE_LEN];
    int status = 0;

    while(status != -1) // -1 => EOF
    {
        buff[0] = '\0';
        status = readline(buff);
        if(status == 1) {
            int nullbyteidx = find_nullbyte_index(buff);
            printf("%d\n", nullbyteidx > MAX_PER_LINE);
            if(nullbyteidx > (int)MAX_PER_LINE) splitlines(buff);
            writeline(buff);
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

void writeline(char *from)
{
    printf("%s\n",from);
}

int find_next_newline(char *buff, int startingpos, int nullbyteidx)
{
    int i;
    int res;
    for (i = startingpos; i < nullbyteidx; ++i)
    {
        if(buff[i] == NEWLINE)
            res = i;
    }
    return res;
}

void splitlines(char *buff)
{
    int i = MAX_PER_LINE;
    int j = 0;
    int len = find_nullbyte_index(buff);
    while (i < len)
    {
        printf("call %d\n", i);
        if(buff[i] == SPACE) {
            buff[i] = NEWLINE;
            i += MAX_PER_LINE;    
        }
        else {
            for(j = i; j < len; ++j)
                if(buff[j] == SPACE) {
                    printf("else for: %d %c\n", j, buff[j]);
                    buff[j] = NEWLINE;
                    int next_newline = find_next_newline(buff, j, len);
                    i = next_newline + MAX_PER_LINE;
                    break;
                } else continue;
        }
        i++;

    }
    printf("%d %d\n",i,len);
}