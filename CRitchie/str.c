#include <stdio.h>


int main ()
{
    // How to actually get string input
    int c;
    while((c = getchar()) != EOF || getchar() != 'q')
    {
        putchar(c);
    }

    return 0;
}