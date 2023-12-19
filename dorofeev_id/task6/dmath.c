#include "dmath.h"

unsigned long long factorial(unsigned long long n) 
{
    if (n == 0) 
    {
        return 1;
    }
    return n * factorial(n - 1);
}

double calculate_precision(int precision) 
{
    return pow(10, -precision);
}

double sin_taylor(double x, int precision, int max_iterations, int* terms_count)
{
    double result = 0;
    double term;
    double precision_value = calculate_precision(precision);
    double period = 2 * PI;
    *terms_count = 0;

    x = fmod(x, period);

    for (int i = 0; i < max_iterations; ++i) 
    {
        term = pow(-1, i) * pow(x, 2 * i + 1) / factorial(2 * i + 1);
        result += term;
        *terms_count++;

        if (fabs(term) < precision_value) 
        {
            break;
        }
    }

    return result;
}

double cos_taylor(double x, int precision, int max_iterations, int* terms_count)
{
    double result = 0;
    double term;
    double precision_value = calculate_precision(precision);
    double period = 2 * PI;
    *terms_count = 0;

    x = fmod(x, period);

    for (int i = 0; i < max_iterations; ++i) 
    {
        term = pow(-1, i) * pow(x, 2 * i) / factorial(2 * i);
        result += term;
        *terms_count++;

        if (fabs(term) < precision_value) 
        {
            break;
        }
    }

    return result;
}

double exp_taylor(double x, int precision, int max_iterations, int* terms_count)
{
    double result = 0;
    double term;
    double precision_value = calculate_precision(precision);
    *terms_count = 0;

    for (int i = 0; i < max_iterations; ++i) 
    {
        term = pow(x, i) / factorial(i);
        result += term;
        *terms_count++;

        if (fabs(term) < precision_value) 
        {
            break;
        }
    }

    return result;
}


double arccot_taylor(double x, int precision, int max_iterations, int* terms_count)
{
    double result = 0;
    double term;
    double precision_value = calculate_precision(precision);
    double period = 2;
    *terms_count = 0;

    x = fmod(x, period);

    for (int i = 0; i < max_iterations; ++i) 
    {
        term = pow(-1, i) * pow(x, 2 * i + 1) / (2 * i + 1);
        result += term;
        *terms_count++;

        if (fabs(term) < precision_value) 
        {
            break;
        }
    }

    return result;
}

double tan_taylor(double x, int precision, int max_iterations, int* terms_count)
{
    double result = 0;
    double term;
    double precision_value = calculate_precision(precision);
    double period = PI;
    *terms_count = 0;

    x = fmod(x, period);

    for (int i = 1; i <= max_iterations; i += 2) 
    {
        term = pow(x, i) / factorial(i);
        result += (i % 4 == 1) ? term : -term;
        *terms_count++;

        if (fabs(term) < precision_value) 
        {
            break;
        }
    }

    return result;
}

double cot_taylor(double x, int precision, int max_iterations, int* terms_count)
{
    double result = 0;
    double term;
    double precision_value = calculate_precision(precision);
    double period = PI;

    x = fmod(x, period);
    *terms_count = 0;

    for (int i = 0; i < max_iterations; ++i) {
        term = pow(x, 2 * i + 1) / factorial(2 * i + 1);
        result += (i % 2 == 0) ? term : -term;
        *terms_count++;

        if (fabs(term) < precision_value) 
        {
            break;
        }
    }

    return 1 / result;
}


double arcsin_taylor(double x, int precision, int max_iterations, int* terms_count)
{
    double result = 0;
    double term;
    double precision_value = calculate_precision(precision);
    *terms_count = 0;

    for (int i = 0; i < max_iterations; ++i) 
    {
        term = factorial(2 * i) * pow(x, 2 * i + 1) / pow(4, i) / pow(factorial(i), 2) / (2 * i + 1);
        result += (i % 2 == 0) ? term : -term;
        *terms_count++;

        if (fabs(term) < precision_value) 
        {
            break;
        }
    }

    return result;
}

double arccos_taylor(double x, int precision, int max_iterations, int* terms_count)
{
    double result = 0;
    double term;
    double precision_value = calculate_precision(precision);
    *terms_count = 0;

    // Ensure x is within the valid range [-1, 1]
    x = fmin(fmax(x, -1.0), 1.0);

    for (int i = 0; i < max_iterations; ++i) 
    {
        term = factorial(2 * i) * pow(x, 2 * i) / pow(4, i) / pow(factorial(i), 2) / (2 * i + 1);
        result += (i % 2 == 0) ? term : -term;
        *terms_count++;

        if (fabs(term) < precision_value) 
        {
            break;
        }
    }

    return result;
}



double arctan_taylor(double x, int precision, int max_iterations, int* terms_count)
{
    double result = 0;
    double term;
    double precision_value = calculate_precision(precision);
    *terms_count = 0;

    for (int i = 0; i < max_iterations; ++i) 
    {
        term = pow(-1, i) * pow(x, 2 * i + 1) / (2 * i + 1);
        result += term;
        *terms_count++;

        if (fabs(term) < precision_value) 
        {
            break;
        }
    }

    return result;
}

double cot(double x)
{
    return 1 / tan(x);
}

double acot(double x)
{
    return atan(1 / x);
}


