#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include "PSC.h"

/**
 * Password strength checker, based on rules at each level.
 * The rules focus on strength scores: adequate length, digit, upper and lowercase letters, special characters.
 * Does not check against a dictionary, yet.
*/
int main(void) 
{
    while(true){
        char* password = getPassword();
        // Some input validation
        if (strlen(password) >= 32 )
        {
            puts("Password needs to be less than 32 characters long!");
            continue;
        }
        if (containsWhitespace(password))
        {
            puts("Password cannot contain whitespaces!");
            continue;
        }

        // Check password strength
        char* msg = checkStrength(password);
        printf("%s\n", msg);

        // Free allocated memory
        free(password);
        free(msg);
    }
    return EXIT_SUCCESS;
}


/**
 * Return the user's password.
 * Using dynamic memory allocation (malloc()) to return the char array.
 * Don't forget to free the allocated memory to avoid memory leaks!
*/
char* getPassword(void)
{
    char* password;
    while (true)
    {
        password = malloc(64 * sizeof(char));
        printf("Enter your password (needs to be less than 64 characters): ");
        // fgets() over scanf() for safer input handling and prevention of buffer overflow.
        fgets(password, 64, stdin);
        if (password[0] == '\n') 
        {
            printf("Password cannot be carriage return/new line, try again!\n");
            continue;
        }
        else
        {
            // remove \n, replace with null.
            password[strcspn(password, "\n")] = '\0';
            break;
        }
    }
    return password;
}


/**
 * Custom function to check for white space in user's input.
 * Loop through the allocated char array to determine if there is a whitespace char in there.
*/
int containsWhitespace(const char* password)
{
    for (int i=0; i<strlen(password); i++)
    {
        if(isspace((unsigned char) password[i]))
        {
            // If i is a whitespace char, returns true.
            return true;
        }
    }
    return false;
}


char* checkStrength(const char* str)
{
    // Allocate memory for message
    char* msg = malloc(24 * sizeof(char));

    int strengthScore = 0;
    const bool hasLength = strlen(str) >= 10;
    bool hasDigit = false, hasLower = false, hasUpper = false, hasSpecialChar = false;
    int length = strlen(str);
    
    // ChatGpt added this validation. 
    if (msg == NULL)
    {
        fprintf(stderr, "Memory allocation failed for 'msg'\n");
        return NULL;
    }

    // Loop through password, tracking special symbols
    for (int i=0; i<length; i++)
    {
        if (isdigit(str[i])) hasDigit = true;
        if (islower(str[i])) hasLower = true;
        if (isupper(str[i])) hasUpper = true;
        // Evaluating whether i is a printable special symbol on a qwerty keyboard
        if ((str[i]>=33 && str[i]<=47) || 
            (str[i]>=58 && str[i]<=64) || 
            (str[i]>=91 && str[i]<=96) || 
            (str[i]>=123 &&str[i]<=126))
        {
            hasSpecialChar = true;
        }
    }

    // Calculate and Rate strength base on strengthScore
    if (hasLength) strengthScore += 30;
    if (hasDigit) strengthScore += 10;
    if (hasLower) strengthScore += 10;
    if (hasUpper) strengthScore += 25;
    if (hasSpecialChar) strengthScore += 25;

    if (strengthScore == 100)
    {
        sprintf(msg, "VERY STRONG");
    }
    else if (strengthScore >= 75)
    {
        sprintf(msg, "STRONG");
    }
    else if (strengthScore >= 50)
    {
        sprintf(msg, "MODERATE");
    }
    else if (strengthScore >= 40)
    {
        sprintf(msg, "WEAK");
    }
    else 
    {
        sprintf(msg, "VERY WEAK");
    }
    
    return msg;
}