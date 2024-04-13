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
            return EXIT_FAILURE;
        }
        if (containsWhitespace(password))
        {
            puts("Password cannot contain whitespaces!");
            return EXIT_FAILURE;
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
    char* password = malloc(64 * sizeof(char));
    printf("Enter your password (needs to be less than 64 characters): ");
    // fgets() over scanf() for safer input handling and prevention of buffer overflow.
    fgets(password, 64, stdin);
    // remove \n, replace with null.
    password[strcspn(password, "\n")] = '\0';
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

    int strengthCounter = 0;
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
            break;
        }
    }

    // Calculate and Rate strength base on strengthCounter
    if (hasLength) strengthCounter += 20;
    if (hasDigit) strengthCounter += 20;
    if (hasLower) strengthCounter += 20;
    if (hasUpper) strengthCounter += 20;
    if (hasSpecialChar) strengthCounter += 20;

    if (strengthCounter == 100)
    {
        sprintf(msg, "VERY STRONG");
    }
    else if (strengthCounter >= 80)
    {
        sprintf(msg, "STRONG");
    }
    else if (strengthCounter >= 60)
    {
        sprintf(msg, "MODERATE");
    }
    else if (strengthCounter >= 40)
    {
        sprintf(msg, "WEAK");
    }
    else 
    {
        sprintf(msg, "VERY WEAK");
    }
    
    return msg;
}