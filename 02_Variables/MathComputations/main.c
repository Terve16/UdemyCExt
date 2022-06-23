#include <stdio.h>

int main()
{
    float x = -2.0f;
    float y = -3.0f;

    float z1 = 0.0f;
    float z2 = 0.0f;
    float z3 = 0.0f;

    z1 = ((x * x) + (y * y) - (x * y) + 2.0f);

    float temp = (x - y);
    z2 = ((temp * temp * temp) - 3.0f);

    z3 = (((2.0f * x * x * x) - (x * x / 2.0f) - x + 4.0f) / y);

    printf("z1 = %f\n", z1);
    printf("z2 = %f\n", z2);
    printf("z3 = %f\n", z3);

    return 0;
}
