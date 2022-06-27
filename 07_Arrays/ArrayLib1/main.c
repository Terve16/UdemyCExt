#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utils.h"

void unique_elements(int32_t *array, size_t length);

void remove_duplicates(int32_t *array, size_t *length);

void rotate_left(int32_t *array, size_t length);

void rotate_right(int32_t *array, size_t length);

int main()
{
    int32_t array[] = {1, 1, 2, 3, 3, 4};
    size_t length = 6;

    printf("unique_elements: \n");
    unique_elements(array, length);

    printf("\n");
    remove_duplicates(array, &length);
    print_int32_array(array, length);

    printf("\n");
    rotate_left(array, length);
    print_int32_array(array, length);

    printf("\n");
    rotate_right(array, length);
    print_int32_array(array, length);

    return 0;
}

void unique_elements(int32_t *array, size_t length)
{
    if (array == NULL)
        return;

    for (size_t i = 0u; i < length; i++)
    {
        bool duplicate = false;
        for (size_t j = 0u; j < length; j++)
        {
            if (i != j && array[i] == array[j])
            {
                duplicate = true;
                break;
            }
        }
        if (!duplicate)
        {
            printf("%d, ", array[i]);
        }
    }

    printf("\n");
    /*
    int32_t *temp = (int32_t *)malloc(length * sizeof(int32_t));
    if (temp == NULL)
        return;

    for (size_t i = 0; i < length; i++)
    {
        temp[i] = array[i];
    }

    remove_duplicates(temp, &length);

    print_int32_array(temp, length);

    free(temp);
    */
}

void remove_duplicates(int32_t *array, size_t *length)
{
    if (array == NULL || length == NULL)
        return;

    for (size_t i = 0u; i < *length; i++)
    {
        for (size_t j = (i + 1u); j < *length; j++)
        {
            if (array[i] == array[j])
            {
                int32_t temp = array[j];

                for (size_t k = j; k < ((*length) - 1u); k++)
                {
                    array[k] = array[k + 1u];
                }

                array[(*length) - 1u] = temp;
                (*length)--;
            }
        }
    }
}

void rotate_left(int32_t *array, size_t length)
{
    if (array == NULL)
        return;

    int32_t temp = array[0];

    for (size_t i = 0u; i < (length - 1u); i++)
    {
        array[i] = array[i + 1u];
    }

    array[length - 1u] = temp;
}

void rotate_right(int32_t *array, size_t length)
{
    if (array == NULL)
        return;

    int32_t temp = array[length - 1u];

    for (size_t i = (length - 1u); i > 0u; i--)
    {
        array[i] = array[i - 1u];
    }

    array[0] = temp;
}
