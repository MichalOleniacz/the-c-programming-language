#include <stdio.h>

void count()
{
    int c;
    int blanks, tabs, newlines = 0;
    
    while((c=getchar()) != EOF)
        switch (c) {
            case ' ':
                ++blanks;
            case '\t':
                ++tabs;
            case '\n':
                ++newlines;
        }
    
    printf("%d %d %d\n", blanks, tabs, newlines);
}

void reduce_blanks()
{
    int prev, curr;

    while((curr=getchar()) != EOF)
        if (prev == ' ' && curr == ' ')
            continue;
        else {
            putchar(curr);
            prev = curr;
        }
}


int main()
{
    // int c, n1;

    // n1 = 0;

    // while((c=getchar()) != EOF)
    //     if (c == '\n')
    //         ++n1;
    
    // printf("%d\n", n1);

    reduce_blanks();
}