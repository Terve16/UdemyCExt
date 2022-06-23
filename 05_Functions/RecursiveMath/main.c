#include <stdint.h>
#include <stdio.h>

uint32_t recursive_sum(uint32_t lower_value, uint32_t upper_value)
{
    if (lower_value >= upper_value)
    {
        return 0u;
    }
    else
    {
        return (lower_value + recursive_sum((lower_value + 1u), upper_value));
    }

    /*
    uint32_t result = 0u;

    for (uint32_t i = lower_value; i < upper_value; i++)
    {
        result += i;
    }

    return result;
    */
}

uint32_t recursive_product(uint32_t lower_value, uint32_t upper_value)
{
    if (lower_value >= upper_value)
    {
        return 1u;
    }
    else
    {
        return (lower_value * recursive_product((lower_value + 1u), upper_value));
    }
}

int main()
{
    uint32_t lower_value = 1;
    uint32_t upper_value = 10;

    printf("recursive_sum: %u\n", recursive_sum(lower_value, upper_value));
    printf("recursive_product: %u\n", recursive_product(lower_value, upper_value));

    return 0;
}
