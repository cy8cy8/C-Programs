#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <stdbool.h>
#include "randpassgen.h"

int main()
{

    // Ask user for the length of the password to be generated.
    printf("\n");
    int length = getLength();
    if (length == 0 || length > 64)
    {
        return 0;
    }

    // Generate seed using random pid and password
    if (length % 2 == 0)
    {
        srand(getpid());
        printf("pid = %d\n", getpid());
    }
    else
    {
        srand((getpid() / 2));
        printf("pid = %d\n", (getpid() / 2));
    }
    getPassword(length);
    printf("\n");
    return EXIT_SUCCESS;
}

// Function to get length from user.
int getLength()
{
    int length;
    printf("Enter the desired length for your new password (must be be more than 10 characters long): ");
    scanf("%d", &length);
    if (length < 10)
    {
        printf("The length of your password needs to be more than 10 characters long!\n");
        return EXIT_SUCCESS;
    }
    else if (length > 64)
    {
        printf("Max length is 64, enter a length between 10 and 64!");
        return 0;
    }
    else
    {
        printf("length of password = %d\n", length);
        return length;
    }
}

// Function to generate password.
void getPassword(int length)
{
    printf("Your password = ");
    for (int i = 0; i < length; i++)
    {
        // Create a random printable ASCII char: english alphabet (upper/lower case), numbers and symbols.
        // Note: rand() is repeatable, DO NOT use it if unique chars need to be generated every time the program is run!
        // For this use case, forcing users to implement a strong length and seed are sufficient to a strong password that is difficult to be brute-forced.
        char c = (char)((rand() % 94) + 34);
        printf("%c", c);
    }
    printf("\n");
}
