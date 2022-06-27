#include <stdbool.h>
#include <stdio.h>

/* CHARS */

bool is_numeric(char character);

bool is_alpha(char character);

bool is_alpha_numeric(char character);

bool is_upper_case(char character);

bool is_lower_case(char character);

char to_upper_case(char character);

char to_lower_case(char character);

/* CHAR ARRAYS */

char *to_upper_case_str(char *text);

char *to_lower_case_str(char *text);

char *char_search(char *text, char character);

int main()
{
    char input_text[50] = {'\0'};

    printf("Please enter any text: ");
    scanf("%s", input_text);

    printf("to_upper_case: %s\n", to_upper_case_str(input_text));
    printf("to_lower_case: %s\n", to_lower_case_str(input_text));
    printf("char_search: %s\n", char_search(input_text, 'a'));

    return 0;
}

/* CHARS */

bool is_numeric(char character)
{
    if ((character >= '0') && (character <= '9'))
    {
        return true;
    }

    return false;
}

bool is_alpha(char character)
{
    if (is_upper_case(character) || is_lower_case(character))
    {
        return true;
    }

    return false;
}

bool is_alpha_numeric(char character)
{
    return is_numeric(character) || is_alpha(character);
}

bool is_upper_case(char character)
{
    if ((character >= 'A') && (character <= 'Z'))
    {
        return true;
    }

    return false;
}

bool is_lower_case(char character)
{
    if ((character >= 'a') && (character <= 'z'))
    {
        return true;
    }

    return false;
}

char to_upper_case(char character)
{
    if (is_lower_case(character))
    {
        return character - 32;
    }

    return character;
}

char to_lower_case(char character)
{
    if (is_upper_case(character))
    {
        return character + 32;
    }

    return character;
}

/* CHAR ARRAYS */

char *to_upper_case_str(char *text)
{
    if (text == NULL)
        return NULL;

    size_t i = 0u;
    while (text[i] != '\0')
    {
        text[i] = to_upper_case(text[i]);
        i++;
    }

    return text;
}

char *to_lower_case_str(char *text)
{
    if (text == NULL)
        return NULL;

    size_t i = 0u;
    while (text[i] != '\0')
    {
        text[i] = to_lower_case(text[i]);
        i++;
    }

    return text;
}

char *char_search(char *text, char character)
{
    if (text == NULL)
        return NULL;

    size_t i = 0u;
    while (text[i] != '\0')
    {
        if (text[i] == character)
        {
            return &(text[i]);
        }
        i++;
    }

    return NULL;
}
