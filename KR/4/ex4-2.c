#include <ctype.h>
#include <stdio.h>
#include <math.h>

double atof(char s[]) 
{
    double val, power;
    int i, sign;

    for (int i = 0; isspace(s[i]); i++)
        ;
    sign = (s[i] == '-') ? -1 : 1;
    if (s[i] == '+' || s[i] == '-') 
    {
        i++;
    }
    for (val = 0.0; isdigit(s[i]); i++)
    {
        val = 10.0 * val + (s[i] - '0');
    }
    if (s[i] == '.')
    {
        i++;
    }
    for (power = 1.0; isdigit(s[i]); i++) 
    {
        val = 10.0 * val + (s[i] - '0');
        power *= 10.0;
    }

    double result = sign * val / power;
    
    if (s[i] == 'e' || s[i] == 'E')
    {
        i++;
        int expSign = s[i] == '-' ? -1 : 1;
        if (s[i] == '+' || s[i] == '-')
        {
            i++;
        }
        int exp;
        for (exp = 0; isdigit(s[i]); i++)
        {
            exp = 10.0 * exp + (s[i] - '0');
        }
        result *= pow(10, expSign * exp);
    }

    return result;
}

int main() {
    double n = atof("123.456");
    printf("%f", n);
}