#include <stdio.h>


int main ()
{
    // How to actually get string input
    int c;
    while((c = getchar()) != EOF || getchar() != 'q')
    {
        putchar(c);
    }

    // Custom string length function
    long len;
    for (len = 0; getchar() != EOF; len++);
    printf("Length of string = %ld\n", len);

    return 0;
}