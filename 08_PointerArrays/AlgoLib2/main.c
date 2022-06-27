#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "utils.h"

void iota(int32_t *array, size_t length, int32_t start_value);

int32_t *inclusive_scan(int32_t *array, size_t length);

int main()
{
    int32_t array[8] = {0};
    size_t length = 8;

    iota(array, length, -2);
    print_int32_array(array, length);

    int32_t *inc_scan_values = inclusive_scan(array, length);
    printf("inclusive_scan: \n");
    print_int32_array(inc_scan_values, length);

    free(inc_scan_values);
    inc_scan_values = NULL;

    return 0;
}

void iota(int32_t *array, size_t length, int32_t start_value)
{
    if (array == NULL)
        return;

    for (size_t i = 0u; i < length; i++)
    {
        array[i] = (start_value + i);
    }
}

int32_t *inclusive_scan(int32_t *array, size_t length)
{
    if (array == NULL)
        return 0;

    int32_t *array_sum = (int32_t *)malloc(length * sizeof(int32_t));

    if (array_sum == NULL)
        return NULL;

    int32_t sum = 0;

    for (size_t i = 0u; i < length; i++)
    {
        sum += array[i];
        array_sum[i] = sum;
    }
    return array_sum;
}
