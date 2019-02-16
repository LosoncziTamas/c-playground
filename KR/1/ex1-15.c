#include <stdio.h>

#define LOWER 0
#define UPPER 300
#define STEP 20

float fahrToCelsius(float fahr);
float celsiusToFahr(float celsius);

/*  Rewrite the temperature conversion
    program of Section 1.2 to use a 
    function for conversion. */

int main(void)
{
    for (float fahr = LOWER; fahr < UPPER; fahr += STEP)
    {
        printf("%6.1f %6.2f\n", fahr, fahrToCelsius(fahr));
    }
    putchar('\n');
    for (float celsius = LOWER; celsius < UPPER; celsius += STEP)
    {
        printf("%6.1f %6.1f\n", celsius, celsiusToFahr(celsius));
    }
    return 0;
}

float fahrToCelsius(float fahr)
{
    return (5.0f / 9.0f) * (fahr - 32);
}

float celsiusToFahr(float celsius)
{
    return (9.0f / 5.0f) * celsius + 32;
}