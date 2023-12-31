#include "MyFunc.h"
#include <math.h>


double my_exp(double x, double precision, int N, int* pcount)
{
    double result = 1;
    double temp = 1;
    double present;
    int i = 1;
    while (i < N && (fabs(exp(x) - result) >= precision))
    {
        present = temp * x / i;
        result += present;
        temp = present;
        i++;
    }
    *pcount = i;
    return result;
}