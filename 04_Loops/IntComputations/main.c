#include <stdint.h>
#include <stdio.h>

#include <math.h>

int main()
{
    uint32_t number = 0;

    printf("Please enter a unsinged integer: ");
    scanf("%u", &number);

    uint32_t temp = number;

    // sum_of_digits
    uint32_t num_digits = 0u;

    while (temp > 0u)
    {
        num_digits++;
        temp /= 10u;
    }

    /*
    while (number >= (uint32_t)pow(10.0, (double)num_digits))
    {
        num_digits++;
    }
    */

    printf("sum_of_digits: %u\n", num_digits);

    temp = number;

    // cross_sum
    uint32_t cross_sum = 0u;

    while (temp > 0u)
    {
        cross_sum += (temp % 10);
        temp /= 10u;
    }

    /*
    uint32_t remainder = number;
    for (uint32_t i = (num_digits - 1u); i > 0u; i--)
    {
        cross_sum += (remainder / (uint32_t)pow(10.0, (double)i));
        remainder = (remainder % (uint32_t)pow(10.0, (double)i));
    }
    cross_sum += remainder;
    */

    printf("cross_sum: %d\n", cross_sum);
}
