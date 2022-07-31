#include "stdio.h"

#define MAX_LINE_LEN 100

/**
 * @brief Reverses a string buffer
 * 
 * @param buff
 */
void reverse(char *buff);

/**
 * @brief Reads from stdin
 * 
 * @param buff 
 * @return int 
 */
int readline(char *buff);

/**
 * @brief Writes from buffer to stdout
 * 
 * @param buff 
 */
void writeline(char *buff);

/**
 * @brief Returns the index of \0 in char array
 * 
 * @param buff 
 * @return int 
 */
int find_nullbyte_index(char *buff);

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
            reverse(buff);
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

void writeline(char *from)
{
    printf("%s\n",from);
}

int find_nullbyte_index(char *buff)
{
    int i = 0;
    while(buff[i] != '\0') i++;
    return i;
}

void reverse(char *buff)
{
    int nullbyteidx = find_nullbyte_index(buff);
    int j = nullbyteidx - 1;
    int i;
    char temp;

    for (i = 0; i < nullbyteidx; i++)
    {
        if(i == j || j < i) break;
        temp = buff[i];
        buff[i] = buff[j];
        buff[j] = temp;
        j--;
    }
}