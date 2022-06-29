#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "Matrix.h"
#include "Timer.h"
#include "Vector.h"

int main()
{
    Matrix *m1 = createMatrix(249, 249, +1.0f);
    Matrix *m2 = createMatrix(249, 249, -1.0f);

    const clock_t time_start = clock();

    Matrix *m3 = multiplyMatrix(m1, m2);

    const clock_t time_end = clock();

    printf("ms: %.16lf\n", get_timing_milliseconds(&time_start, &time_end));
    printf("us: %.16lf\n", get_timing_microseconds(&time_start, &time_end));
    printf("ns: %.16lf\n", get_timing_nanoseconds(&time_start, &time_end));

    freeMatrix(m1);
    freeMatrix(m2);
    freeMatrix(m3);

    return 0;
}
