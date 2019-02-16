#include <stdio.h>

#define LOWER 0
#define UPPER 300
#define STEP 20

/* Celsius to Fahrenheit 0 - 300 */

int main(void)
{
    float celsius = LOWER;
    while(celsius <= UPPER)
    {
        float fahr = (9.0f / 5.0f) * celsius + 32;
        printf("%3.0f %3.0f\n", celsius, fahr);
        celsius += STEP;
    }
    return 0;
}