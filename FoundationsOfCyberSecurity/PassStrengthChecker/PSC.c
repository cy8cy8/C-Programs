#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include "PSC.h"

// Symbolic Constants to avoid magic numbers.
#define MSGLEN 24
#define PASSLEN 64

/**
 * Password strength checker, based on rules at each level.
 * The rules focus on strength scores: adequate length, digit, upper and lowercase letters, special characters.
 * Does not check against a dictionary, yet.
*/
int main(void) 
{
    while(true){
        // printf("Press enter to continue, q to quit: ");
        // int enterOrQuit = getchar();
        // if (enterOrQuit == '\n') 
        // {
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
        // else if (enterOrQuit == 'q')
        // {
        //     break;
        // }
        // else 
        // {
            // puts("Please press enter to continue or q to quit!");
        //     continue;
        // }
    // }
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
        password = malloc(PASSLEN * sizeof(char));
        printf("Enter your password (needs to be less than 64 characters): ");
        // fgets() over scanf() for safer input handling and prevention of buffer overflow.
        fgets(password, PASSLEN, stdin);
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
    char* msg = malloc(MSGLEN * sizeof(char));

    int strengthScore = 0;
    const bool hasLength = strlen(str) >= 12;
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
    if (hasLength) strengthScore += 20;
    if (hasDigit) strengthScore += 20;
    if (hasLower) strengthScore += 20;
    if (hasUpper) strengthScore += 20;
    if (hasSpecialChar) strengthScore += 20;

    if (strengthScore == 100)
    {
        sprintf(msg, "VERY STRONG");
    }
    else if (strengthScore >= 80)
    {
        sprintf(msg, "STRONG");
    }
    else if (strengthScore >= 60)
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