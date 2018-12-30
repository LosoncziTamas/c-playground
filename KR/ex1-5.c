#include <stdio.h>

#define LOWER 0
#define UPPER 300
#define STEP 20

/* Fahrenheit-Celsius table 0 - 300 */

int main()
{
    float fahr = UPPER;

    while(fahr >= LOWER)
    {
        float celsius = (5.0f / 9.0f) * (fahr - 32);
        printf("%3.0f %6.1f\n", fahr, celsius);
        fahr -= STEP;
    }

    return 0;
}