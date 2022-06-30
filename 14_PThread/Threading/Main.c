#include <assert.h>
#include <pthread.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define LENGTH (size_t)(10000000000u)
#define NUM_RUNS (size_t)(10u)

typedef struct
{
    float *array;
    size_t length;
} varg_thread_t;


void serial_sum(float *arr, size_t length)
{
    if (arr == NULL)
        return;

    static volatile double sum = 0u;

    for (size_t i = 0; i < length; i++)
    {
        sum += (double)arr[i];
    }
}

void *parallel_sum(void *varg)
{
    if (varg == NULL)
        return NULL;

    varg_thread_t *varg_thread = (varg_thread_t *)varg;

    static volatile double sum = 0u;

    for (size_t i = 0; i < varg_thread->length; i++)
    {
        sum += (double)varg_thread->array[i];
    }

    return NULL;
}

int main()
{

    // init start

    float *arr = (float *)malloc(LENGTH * sizeof(float));

    if (arr == NULL)
        return 1;

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

    // serial execution start

    double total_time = 0.0;

    time_t start = time(NULL);
    for (uint32_t run_idx = 0; run_idx < NUM_RUNS; run_idx++)
    {
        (void)serial_sum(arr, LENGTH);
    }
    time_t end = time(NULL);
    total_time = (difftime(end, start) * 1000.0F);

    printf("Serial - Total time: %.16lf ms\n", total_time);
    printf("Serial - Mean execution time: %.16lf ms\n", (total_time / (double)(NUM_RUNS)));

    total_time = 0.0;

    // parallel execution start

    start = time(NULL);

    /*
    varg_thread_t *varg_thread = (varg_thread_t *)malloc(sizeof(varg_thread_t));

    if (varg_thread == NULL)
        return 1;
    */

    varg_thread_t varg_thread;

    varg_thread.length = LENGTH;
    varg_thread.array = arr;

    pthread_t thread_id[NUM_RUNS] = {NULL};

    for (uint32_t run_idx = 0; run_idx < NUM_RUNS; run_idx++)
    {
        pthread_create(&(thread_id[run_idx]), NULL, parallel_sum, (void *)(&varg_thread));
    }
    for (uint32_t run_idx = 0; run_idx < NUM_RUNS; run_idx++)
    {
        pthread_join(thread_id[run_idx], NULL);
    }
    end = time(NULL);
    total_time = (difftime(end, start) * 1000.0F);

    printf("Parallel - Total time: %.16lf ms\n", total_time);
    printf("Parallel - Mean execution time: %.16lf ms\n", (total_time / (double)(NUM_RUNS)));

    free(arr);
    arr = NULL;

    return 0;
}
