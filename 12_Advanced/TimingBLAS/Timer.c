
#include "Timer.h"

double get_timing_milliseconds(const clock_t *time_start, const clock_t *time_end)
{
    if (time_start == NULL || time_end == NULL)
        return 0.0;

    return (((double)(*time_end - *time_start) / (double)CLOCKS_PER_SEC) * 1000.0);
}

double get_timing_microseconds(const clock_t *time_start, const clock_t *time_end)
{
    return (get_timing_milliseconds(time_start, time_end) * 1000.0);
}

double get_timing_nanoseconds(const clock_t *time_start, const clock_t *time_end)
{
    return (get_timing_microseconds(time_start, time_end) * 1000.0);
}
