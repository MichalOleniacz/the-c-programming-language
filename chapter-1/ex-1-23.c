#include "stdio.h"

#define SLASH '/'
#define STAR '*'
#define QUOTE '\''
#define DOUBLE_QUOTE '"'
#define MAX_LINE_LEN 1024

int readline(char *buff);
void writeline(char *buff);
int find_nullbyte_idx(char *buff);

int main(void)
{
    char buff[MAX_LINE_LEN];
    int status = 0;

    while(status != -1) // -1 => EOF
    {
        buff[0] = '\0';
        status = readline(buff);
        // printf("INPUT:\n%s", buff);
        if ( status == 1) {
            // printf("OUTPUT:\n");
            writeline(buff);
        }
        else if ( status == -1 ) {
            printf("%s",buff);
            putchar('\n');
            break;
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
        buff[i-1] = c;
        buff[i] = '\0';
        ++i;
        if (c == '\n')
            return 1;
    }
    return 1;
}

int find_nullbyte_index(char *buff)
{
    int i = 0;
    while(buff[i] != '\0') i++;
    return i;
}

void writeline(char *buff)
{
    int nullbyteidx = find_nullbyte_index(buff);
    int i;
    int in_string = 0;
    int single_quote = 0;
    int double_quote = 0;
    int has_code = 0;
    for (i = 0; i < nullbyteidx; ++i)
    {
        if(in_string == 0 && buff[i] == buff[i+1] && buff[i] == SLASH) {
            if(has_code == 1) putchar('\n');
            break;
        }
        else if(buff[i] == QUOTE && in_string == 0 && double_quote == 0) {
            in_string = 1;
            single_quote = 1;
            putchar(buff[i]);
        }
        else if(buff[i] == QUOTE && in_string == 1 && double_quote == 0) {
            in_string = 0;
            single_quote = 0;
            putchar(buff[i]);
        }
        else if(buff[i] == DOUBLE_QUOTE && in_string == 0 && single_quote == 0) {
            in_string = 1;
            double_quote = 1;
            putchar(buff[i]);
        }
        else if(buff[i] == DOUBLE_QUOTE && in_string == 1 && single_quote == 0) {
            in_string = 0;
            double_quote = 0;
            putchar(buff[i]);
        }
        else {
            has_code = 1;
            putchar(buff[i]);
        }
    }
}