#include <stdbool.h>
#include <stdio.h>

int main()
{
    char character;

    printf("Please enter any ASCII character: ");
    scanf("%c", &character);

    printf("\nThe ASCII character '");
    putchar(character);
    printf("' is:\n");

    // is numeric
    bool numeric = ((character >= '0') && (character <= '9'));
    if (numeric)
    {
        printf("numeric,\n");
    }
    else
    {
        printf("not numeric,\n");
    }

    // is upper case
    bool upper_case = ((character >= 'A') && (character <= 'Z'));
    if (upper_case)
    {
        printf("upper case,\n");
    }
    else
    {
        printf("not upper case,\n");
    }

    // is lower case
    bool lower_case = ((character >= 'a') && (character <= 'z'));
    if (lower_case)
    {
        printf("lower case,\n");
    }
    else
    {
        printf("not lower case,\n");
    }

    // is alpha
    bool alpha = (upper_case || lower_case);
    if (alpha)
    {
        printf("alpha,\n");
    }
    else
    {
        printf("not alpha,\n");
    }

    // is alpha numeric
    if (numeric || alpha)
    {
        printf("alpha numeric,\n");
    }
    else
    {
        printf("not alpha numeric,\n");
    }

    // to upper case
    if (lower_case)
    {
        char upper_c = (character - 32);
        printf("To upper case: ");
        putchar(upper_c);
        printf("\n");
    }

    // to lower case
    if (upper_case)
    {
        char lower_c = (character + 32);
        printf("To lower case: ");
        putchar(lower_c);
        printf("\n");
    }

    return 0;
}
