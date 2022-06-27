#include <stdint.h>
#include <stdio.h>

void clamp_value(float *value, float min, float max)
{
    if (*value < min)
    {
        *value = min;
    }
    else if (*value > max)
    {
        *value = max;
    }
}

void round_value(float *value, uint8_t num_digits)
{
    if (num_digits == 0u)
    {
        *value = ((float)((int)*value));
    }
    else
    {
        float multiplier = 1.0f;

        for (uint8_t i = 0u; i < num_digits; i++)
        {
            multiplier *= 10.0f;
        }

        uint32_t temp = (uint32_t)((*value) * multiplier);

        *value = (((float)temp) / multiplier);
    }
}

int main()
{
    float value = 3.0f;

    clamp_value(&value, -2.0f, 2.0f);
    printf("%f\n", value);

    value = 1.23456f;

    round_value(&value, 3u);
    printf("%f\n", value);

    return 0;
}
