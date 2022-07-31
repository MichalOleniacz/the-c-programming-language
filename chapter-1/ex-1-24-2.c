#include "stdio.h"
#include <stddef.h>

#define MAX_LINE_LEN 10024
#define S_SLASH '/'
#define S_QUOTE '\''
#define S_ESCAPE_SLASH '\\'
#define S_DOUBLE_QUOTE '\"'
#define S_SQ_BRACKET_LEFT '['
#define S_SQ_BRACKET_RIGHT ']'
#define S_CURLY_BRACKET_LEFT '{'
#define S_CURLY_BRACKET_RIGHT '}'
#define S_PARENTHESES_LEFT '('
#define S_PARENTHESES_RIGHT ')'
#define S_HASH '#'

enum States {
    CODE,
    COMMENT,
    QUOTE,
    DOUBLE_QUOTE,
    DEF_OR_INCLUDE
};

int sq_bracket_left = 0;
int sq_bracket_right = 0;
int curly_bracket_left = 0;
int curly_bracket_right = 0;
int parentheses_left = 0;
int parentheses_right = 0;
int in_single_quote_f = 0;
int in_double_quote_f = 0;
int state = CODE;


int readline(char *buff);
void report_and_exit();
int scanline(char *buff, int line);
int find_nullbyte_index(char *buff);

int main(void)
{
    char buff[MAX_LINE_LEN];
    int line = 0;
    int status = 0;
    int scan_status = 0;
    char c;

    while(status != -1)
    {
        status = readline(buff);
        scan_status = scanline(buff, line);
        if ( scan_status == -1 ) 
        {
            printf("Critical error while parsing line %d!\n", line);
            break;
        }
        ++line;
    }

    report_and_exit(&state);
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

int scanline(char *buff, int line)
{
    int nullbyteidx = find_nullbyte_index(buff);
    int i;

    for (i = 0; i < nullbyteidx; ++i)
    {
        if (state == CODE) {
                if(buff[i] == S_CURLY_BRACKET_LEFT) curly_bracket_left++;
                if(buff[i] == S_CURLY_BRACKET_RIGHT) curly_bracket_right++;
                if(buff[i] == S_SQ_BRACKET_LEFT) sq_bracket_left++;
                if(buff[i] == S_SQ_BRACKET_RIGHT) sq_bracket_right++;
                if(buff[i] == S_PARENTHESES_LEFT) parentheses_left++;
                if(buff[i] == S_PARENTHESES_RIGHT) parentheses_right++;
                if(buff[i] == S_QUOTE) {
                    state = QUOTE;
                    in_single_quote_f = 1;
                }
                if(buff[i] == S_DOUBLE_QUOTE) {
                    state = DOUBLE_QUOTE;
                    in_double_quote_f = 1;
                }
                if(buff[i] == S_SLASH && buff[i-1] == S_SLASH) state = COMMENT;
                if(buff[i] == S_HASH) state = DEF_OR_INCLUDE;
        }
        else if (state == QUOTE ) 
        {
            if(in_single_quote_f == 1 && buff[i] == S_QUOTE && buff[i-1] != S_ESCAPE_SLASH) {
                    state = CODE;
                    in_single_quote_f = 0;
            }
            else continue;
        }
        else if ( state == DOUBLE_QUOTE )
        {
            if(in_double_quote_f == 1 && buff[i] == S_DOUBLE_QUOTE && buff[i-1] != S_ESCAPE_SLASH) {
                state = CODE;
                in_double_quote_f = 0;
            }
            else continue;
        }
        else if ( state == COMMENT || state == DEF_OR_INCLUDE)
        {
            state = CODE;
            break;
        }
        else return -1;
    }

    printf("l %d - curly: left %d right %d, sq: left %d right %d, parentheses: left %d right %d\n", 
            line, curly_bracket_left, curly_bracket_right, sq_bracket_left,
             sq_bracket_right, parentheses_left, parentheses_right);
    
    return 1;
}

void report_and_exit()
{
    if(curly_bracket_left != curly_bracket_right) 
    {
        if(curly_bracket_left > curly_bracket_right) printf("Missing '}'...\n");
        else printf("Missing '{'...\n");    
    }
    else if(sq_bracket_left != sq_bracket_right)
    {
        if(sq_bracket_left > sq_bracket_right) printf("Missing ']'...\n");
        else printf("Missing '['...\n");
    }
    else if(parentheses_left != parentheses_right)
    {
        if(parentheses_left > parentheses_right) printf("Missing ')'...\n");
        else printf("Missing '('...\n");
    }
    else printf("Everything looks fine...\n");
}