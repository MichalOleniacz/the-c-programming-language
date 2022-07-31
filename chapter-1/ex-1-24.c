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

typedef struct {
    int sq_bracket_left;
    int sq_bracket_right;
    int curly_bracket_left;
    int curly_bracket_right;
    int parentheses_left;
    int parentheses_right;
    int in_single_quote_f;
    int in_double_quote_f;
    int state;
} State;

int readline(char *buff);
void report_and_exit(State *state);
int scanline(char *buff, State *state, int line);
int find_nullbyte_index(char *buff);
void init_state(State *state);

int main(void)
{
    char buff[MAX_LINE_LEN];
    int line = 0;
    int status = 0;
    int scan_status = 0;
    char c;
    State state;
    init_state(&state);

    while(status != -1)
    {
        status = readline(buff);
        scan_status = scanline(buff, &state, line);
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

void init_state(State *state)
{
    state->state = CODE;
    state->curly_bracket_left = 0;
    state->curly_bracket_right = 0;
    state->sq_bracket_left = 0;
    state->sq_bracket_right = 0;
    state->parentheses_left = 0;
    state->parentheses_right = 0;
    state->in_double_quote_f = 0;
    state->in_single_quote_f = 0;
}

int scanline(char *buff, State *state, int line)
{
    int nullbyteidx = find_nullbyte_index(buff);
    int i;

    for (i = 0; i < nullbyteidx; ++i)
    {
        if (state->state == CODE) {
                if(buff[i] == S_CURLY_BRACKET_LEFT) state->curly_bracket_left++;
                if(buff[i] == S_CURLY_BRACKET_RIGHT) state->curly_bracket_right++;
                if(buff[i] == S_SQ_BRACKET_LEFT) state->sq_bracket_left++;
                if(buff[i] == S_SQ_BRACKET_RIGHT) state->sq_bracket_right++;
                if(buff[i] == S_PARENTHESES_LEFT) state->parentheses_left++;
                if(buff[i] == S_PARENTHESES_RIGHT) state->parentheses_right++;
                if(buff[i] == S_QUOTE) {
                    state->state = QUOTE;
                    state->in_single_quote_f = 1;
                }
                if(buff[i] == S_DOUBLE_QUOTE) {
                    state->state = DOUBLE_QUOTE;
                    state->in_double_quote_f = 1;
                }
                if(buff[i] == S_SLASH && buff[i-1] == S_SLASH) state->state = COMMENT;
                if(buff[i] == S_HASH) state->state = DEF_OR_INCLUDE;
        }
        else if (state->state == QUOTE ) 
        {
            if(state->in_single_quote_f == 1 && buff[i] == S_QUOTE && buff[i-1] != S_ESCAPE_SLASH) {
                    state->state = CODE;
                    state->in_single_quote_f = 0;
            }
            else continue;
        }
        else if ( state->state == DOUBLE_QUOTE )
        {
            if(state->in_double_quote_f == 1 && buff[i] == S_DOUBLE_QUOTE && buff[i-1] != S_ESCAPE_SLASH) {
                state->state = CODE;
                state->in_double_quote_f = 0;
            }
            else continue;
        }
        else if ( state->state == COMMENT || state->state == DEF_OR_INCLUDE)
        {
            state->state = CODE;
            break;
        }
        else return -1;
    }

    printf("l %d - curly: left %d right %d, sq: left %d right %d, parentheses: left %d right %d\n", 
            line, state->curly_bracket_left, state->curly_bracket_right, state->sq_bracket_left,
             state->sq_bracket_right, state->parentheses_left, state->parentheses_right);
    
    return 1;
}

void report_and_exit(State *state)
{
    if(state->curly_bracket_left != state->curly_bracket_right) 
    {
        if(state->curly_bracket_left > state->curly_bracket_right) printf("Missing '}'...\n");
        else printf("Missing '{'...\n");    
    }
    else if(state->sq_bracket_left != state->sq_bracket_right)
    {
        if(state->sq_bracket_left > state->sq_bracket_right) printf("Missing ']'...\n");
        else printf("Missing '['...\n");
    }
    else if(state->parentheses_left != state->parentheses_right)
    {
        if(state->parentheses_left > state->parentheses_right) printf("Missing ')'...\n");
        else printf("Missing '('...\n");
    }
    else printf("Everything looks fine...\n");
}