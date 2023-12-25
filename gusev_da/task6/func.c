#include "func.h"

unsigned long long factorial(unsigned long long n)
{
    if (n == 0)  return 1;
    return n * factorial(n - 1);
}

double calc_acc(int accuracy)
{
    return pow(10, -accuracy);
}

double taylor_sin(double x, int accuracy, int N, int* count)
{
    double result = 0, term, accuracy_value = calc_acc(accuracy), period = 2 * PI;
    *count = 0;
    x = fmod(x, period);
    for (int i = 0; i < N; ++i)
    {
        term = pow(-1, i) * pow(x, 2 * i + 1) / factorial(2 * i + 1);
        result += term;
        (*count)++;
        if(fabs(term) < accuracy_value)  break;
    }
    return result;
}

double taylor_cos(double x, int accuracy, int N, int* count)
{
    double result = 0, term, accuracy_value = calc_acc(accuracy), period = 2 * PI;
    *count = 0;
    x = fmod(x, period);
    for (int i = 0; i < N; ++i)
    {
        term = pow(-1, i) * pow(x, 2 * i) / factorial(2 * i);
        result += term;
        (*count)++;
        if (fabs(term) < accuracy_value)  break;
    }
    return result;
}

double taylor_exp(double x, int accuracy, int N, int* count)
{
    double result = 0, term, accuracy_value = calc_acc(accuracy);
    *count = 0;
    for (int i = 0; i < N; ++i)
    {
        term = pow(x, i) / factorial(i);
        result += term;
        (*count)++;
        if(fabs(term) < accuracy_value)  break;
    }
    return result;
}

double taylor_arcsin(double x, int accuracy, int N, int* count)
{
    double result = 0, term, accuracy_value = calc_acc(accuracy);
    *count = 0;
    for (int i = 0; i < N; ++i)
    {
        term = factorial(2 * i) * pow(x, 2 * i + 1) / pow(4, i) / pow(factorial(i), 2) / (2 * i + 1);
        result += (i % 2 == 0) ? term : -term;
        (*count)++;
        if (fabs(term) < accuracy_value)  break;
    }
    return result;
}
