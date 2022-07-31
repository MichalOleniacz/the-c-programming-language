#include "stdio.h"

#define SPACES_PER_TAB    2
#define MAX_LINE_LEN      1024
#define TAB               '\t'
#define SPACE             ' '

int readline(char *buff);
void writeline(char *buff);
void entab(char *buff);
int find_nullbyte_index(char *buff);
void print_spaces(void);

int main(void)
{
    char buff[MAX_LINE_LEN];
    int status = 0;

    while(status != -1) // -1 => EOF
    {
        buff[0] = '\0';
        status = readline(buff);
        if(status == 1) {
            entab(buff);
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

void entab(char *buff)
{
    int i, j;
    int nullbyteidx = find_nullbyte_index(buff);
    int spacecounter = 0;
    for (i = 0; i < nullbyteidx; ++i)
    {
        if(spacecounter == 0 && buff[i] == SPACE)
            for (j = i; j < i + SPACES_PER_TAB; ++j)
            {
                if(buff[j] == SPACE)
                    spacecounter++;
                else spacecounter = 0;
            }
        if(spacecounter == SPACES_PER_TAB)
        {
            buff[i] = TAB;
            int offset = i + 1;
            for (j = offset; j < nullbyteidx; j++)
            {
                buff[j] = buff[j + SPACES_PER_TAB - 1];
            }
            spacecounter = 0;
        }
    }
}

void writeline(char *from)
{
    printf("%s\n",from);
}