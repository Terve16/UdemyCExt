#include <math.h>
#include <stdint.h>
#include <stdio.h>

double getPi(uint32_t num_iterations)
{
    double piFourth = 0.0f;

    if (num_iterations > 0u)
    {
        for (uint32_t i = 0u; i < num_iterations; i++)
        {
            piFourth += ((1.0f / (4.0f * i + 1.0f)) - (1 / (4.0f * i + 3.0f)));
        }
    }

    return (piFourth * 4.0f);
}

void printBinary(uint8_t number)
{
    printf("\nnumber: %d = ", number);

    for (int8_t i = 7; i >= 0; i--)
    {
        if (((i + 1) % 4) == 0)
        {
            putchar(' ');
        }

        uint8_t current_exponent = pow(2, i);

        if (number >= current_exponent)
        {
            putchar('1');
            number -= current_exponent;
        }
        else
        {
            putchar('0');
        }
    }


    printf("\n");
}

int main()
{
    // calculate_pi
    uint32_t num_iterations = 1000000;
    double pi_calculated = 0.0;

    // printf("Enter no of iterations: ");
    // scanf("%u", &num_iterations);

    pi_calculated = getPi(num_iterations);

    double pi = 3.14159265358979323846;
    printf("\npi (calculated): %.16lf\n", pi_calculated);
    printf("pi (correct): %.16lf\n", pi);

    // print_dec_to_bin
    uint8_t dec = 142;

    printBinary(dec);

    return 0;
}
