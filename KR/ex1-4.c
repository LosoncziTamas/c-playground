#include <stdio.h>

#define LOWER 0
#define UPPER 300
#define STEP 20

/* Celsius to Fahrenheit 0 - 300 */

int main(void)
{
    float celsius = 0;
    while(celsius <= UPPER)
    {
        float fahr = (9.0f / 5.0f) * celsius + 32;
        printf("%5.1f %5.1f\n", celsius, fahr);
        celsius += STEP;
    }
    return 0;
}