#include "MyFunc.h"
#include <math.h>
#define PI 3.1415926535

double my_cos(double x, double precision, int N, int* pcount)
{
    while (x > 2 * PI)
        x -= 2 * PI;
    double result = 1;
    double temp = 1;
    double present;
    int i = 1;
    while (i < N && (fabs(cos(x) - result) >= precision))
    {
        present = -temp * x * x / ((2 * i) * (2 * i - 1));
        result += present;
        temp = present;
        i++;
    }
    *pcount = i;
    return result;
}