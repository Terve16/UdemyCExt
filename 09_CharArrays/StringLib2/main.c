#include <stdbool.h>
#include <stdio.h>
#include <string.h>

bool string_starts_with(char *string, char *substr);

bool string_ends_with(char *string, char *substr);

char *string_find_first_not_of(char *string, char *substr);

char *string_n_copy(char *dest, char *src, size_t count);

int main()
{
    char text[50] = "jan schaffranek";
    char copy[50] = {'\0'};

    printf("string_starts_with: %d\n", string_starts_with(text, "jan"));
    printf("string_ends_with: %d\n", string_ends_with(text, "anek"));

    printf("string_starts_with: %d\n", string_starts_with(text, "an"));
    printf("string_ends_with: %d\n", string_ends_with(text, "ane"));

    printf("string_find_first_not_of: %s\n", string_find_first_not_of(text, "jan "));
    printf("string_find_first_not_of: %s\n", string_find_first_not_of(text, "an "));

    printf("string_n_copy: %s\n", string_n_copy(copy, text, 9u));

    return 0;
}

bool string_starts_with(char *string, char *substr)
{
    if (string == NULL || substr == NULL)
        return false;

    size_t i = 0u;
    while (substr[i] != '\0')
    {
        if (string[i] == '\0')
        {
            return false;
        }
        else if (string[i] != substr[i])
        {
            return false;
        }
        i++;
    }

    return true;
}

bool string_ends_with(char *string, char *substr)
{
    if (string == NULL || substr == NULL)
        return false;

    size_t string_len = strlen(string);
    size_t substr_len = strlen(substr);

    if (string_len < substr_len)
    {
        return false;
    }

    for (size_t i = 0u; i < substr_len; i++)
    {
        if (string[string_len - i] != substr[substr_len - i])
        {
            return false;
        }
    }

    return true;
}

char *string_find_first_not_of(char *string, char *substr)
{
    if (string == NULL || substr == NULL)
        return NULL;

    size_t i = 0u;
    while (string[i] != '\0')
    {
        if (substr[i] == '\0')
        {
            return &(string[i]);
        }
        else if (string[i] != substr[i])
        {
            return NULL;
        }
        i++;
    }

    return NULL;
}

char *string_n_copy(char *dest, char *src, size_t count)
{
    if (dest == NULL || src == NULL)
        return NULL;

    for (size_t i = 0u; i < count; i++)
    {
        if (src[i] == '\0')
        {
            return dest;
        }
        else
        {
            dest[i] = src[i];
        }
    }

    return dest;
}
