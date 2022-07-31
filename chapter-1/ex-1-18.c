#include "stdio.h"
#include <stddef.h>

#define MAX_LINE_LEN 100

/**
 * @brief Reads from stdin, saves input to buffer
 * 
 * @param buff pointer to char array
 * @return int 
 */
int readline(char *buff);

/**
 * @brief Writes contents of char array to stdout
 * 
 * @param from 
 * @returns int
 */
int writeline(char *from);

/**
 * @brief Sanitizes the str buffer removing trailing commas, tabs, blanks etc.
 * 
 * @param buff 
 * @returns int 
 */
int sanitize(char *buff);

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
            print = sanitize(buff);
            if (print == 1) writeline(buff);
        }
    }
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

int sanitize(char *buff)
{
    int i = find_nullbyte_index(buff);

    printf("sanitize in: %s\n", buff);
    
    for (;i >= 0; --i)
    {
        if(buff[0] == '\0')
        {
            printf("sanitize: empty buffer, skipping\n");
            return 0;
        } 
        if(buff[i] == '\0') continue;
        if(buff[i] == ',' || buff[i] == '\n' || buff[i] == '\t' || buff[i] == ' ')
        {
            printf("hit > %i: %c\n", i, buff[i]);
            buff[i] = '\0';          
        }
        else break; 
    }
    printf("sanitize out: %s\n", buff);
    return 1;
}

int writeline(char *from)
{
    printf("%s\n",from);
    return 0;
}

int find_nullbyte_index(char *buff)
{
    int i = 0;
    while(buff[i] != '\0') i++;
    return i;
}