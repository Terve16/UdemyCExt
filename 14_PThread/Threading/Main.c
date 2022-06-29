#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LENGTH (10000u)
#define NUM_RUNS (10000u)

void serial_sum(float *arr, size_t length)
{
    if (arr == NULL)
        return;

    volatile static double sum = 0u;

    for (size_t i = 0; i < length; i++)
    {
        sum += (double)arr[i];
    }
}

void parallel_sum(float *arr, size_t length)
{
    if (arr == NULL)
        return;

    volatile static double sum = 0u;

    for (size_t i = 0; i < length; i++)
    {
        sum += (double)arr[i];
    }
}

int main()
{
    float *arr = (float *)malloc(LENGTH * sizeof(float));

    for (size_t i = 0; i < LENGTH; i++)
    {
        if ((i % 2) == 0)
        {
            arr[i] = 1.0F;
        }
        else
        {
            arr[i] = -1.0F;
        }
    }

    double total_time = 0.0;

    const time_t start = time(NULL);
    for (uint32_t run_idx = 0; run_idx < NUM_RUNS; run_idx++)
    {
        (void)serial_sum(arr, LENGTH);
    }
    const time_t end = time(NULL);
    total_time = (difftime(end, start) * 1000.0F) / (double)(NUM_RUNS);

    printf("Serial - Mean execution time: %.2lf ms\n", total_time);

    total_time = 0.0;

    const time_t start = time(NULL);
    for (uint32_t run_idx = 0; run_idx < NUM_RUNS; run_idx++)
    {
        (void)parallel_sum(arr, LENGTH);
    }
    const time_t end = time(NULL);
    total_time = (difftime(end, start) * 1000.0F) / (double)(NUM_RUNS);

    printf("Parall - Mean execution time: %.2lf ms\n", total_time);

    free(arr);
    arr = NULL;

    return 0;
}
