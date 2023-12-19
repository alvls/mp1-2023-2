#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "dmath.h"

void mode1();
void mode2();
double get_reference_value(double x, int choice);
double calculate_estimate(double x, int choice, int terms_count);

double (*taylor_functions[9])(double, int, int, int*) =
{
    exp_taylor,

    sin_taylor,
    cos_taylor,
    tan_taylor,
    cot_taylor,

    arcsin_taylor,
    arccos_taylor,
    arctan_taylor,
    arccot_taylor
};

double (*с_functions[9])(double) =
{
     exp,
    sin,
    cos,
    tan,
    cot,
    asin,
    acos,
    atan,
    acot
};

wchar_t* function_names[9] =
{
    L"exp(x)",

    L"sin(x)",
    L"cos(x)",
    L"tan(x)",
    L"cot(x)",

    L"arcsin(x)",
    L"arccos(x)",
    L"arctan(x)",
    L"arccot(x)"
};

int main()
{
    _wsetlocale(LC_ALL, L"rus");
    int choice;
    int fl = 1;

    while (fl == 1)
    {
        wprintf(L"Выберите режим (1|2)\n");
        if (wscanf(L"%d", &choice) != 1) 
        {
            wprintf(L"Ошибка ввода. Попробуйте ещё раз.\n");
            while (getwchar() != L'\n');  // Очистка буфера ввода
            continue;
        }

        switch (choice)
        {
        case 1:
            mode1();
            fl = 0;
            break;
        case 2:
            mode2();
            fl = 0;
            break;
        default:
            wprintf(L"Такого режима нет. Попробуйте ещё раз.\n");
            break;
        }
    }
    return 0;
}

void mode1()
{
    int choice;
    double x_value;
    int precision;
    int max_iterations;
    double result;
    double result_c;
    double rz;
    int terms_count;

    system("cls");
    wprintf(L"Выберите функцию\n");

    for (int i = 0; i < 9; ++i) 
    {
        wprintf(L"%d) %s\n", i + 1, function_names[i]);
    }

    if (wscanf(L"%d", &choice) != 1 || choice < 1 || choice > 9) 
    {
        wprintf(L"Ошибка ввода. Попробуйте ещё раз.\n");
        return;
    }

    wprintf(L"Введите X\n");
    if (wscanf(L"%lf", &x_value) != 1) 
    {
        wprintf(L"Ошибка ввода. Попробуйте ещё раз.\n");
        return;
    }

    wprintf(L"Введите нужную точность (кол-во знаков после запятой)\n");
    if (wscanf(L"%d", &precision) != 1 || precision < 0) 
    {
        wprintf(L"Ошибка ввода. Попробуйте ещё раз.\n");
        return;
    }

    wprintf(L"Введите максимальное количество членов ряда\n");
    if (wscanf(L"%d", &max_iterations) != 1 || max_iterations <= 0) 
    {
        wprintf(L"Ошибка ввода. Попробуйте ещё раз.\n");
        return;
    }

    result = taylor_functions[choice - 1](x_value, precision, max_iterations, &terms_count);
    result_c = с_functions[choice - 1](x_value);
    rz = fabs(result - result_c);

    wprintf(L"Эталонное значение %s: %lf\n", function_names[choice - 1], result_c);
    wprintf(L"Оценка значения функции: %s = %lf\n", function_names[choice - 1], result);
    wprintf(L"Разница между оценкой и эталонным значением: %lf", rz);
    wprintf(L"Количество вычесленных слагаемых: %d\n", terms_count);
    system("pause");
}

void mode2()
{
    int choice;
    double x_value;
    int experiments_count;
    int terms_count;

    system("cls");
    printf("Выберите функцию:\n");
    for (int i = 0; i < 9; ++i) 
    {
        wprintf(L"%d) %s\n", i + 1, function_names[i]);
    }

    scanf("%d", &choice);

    printf("Введите X:\n");
    scanf("%lf", &x_value);

    printf("Введите число экспериментов (от 1 до 25):\n");
    scanf("%d", &experiments_count);

    double reference_value = get_reference_value(x_value, choice);

    printf("Эталонное значение: %lf\n", reference_value);
    printf("Таблица результатов:\n");
    printf("| Кол-во слагаемых | Оценка значения | Разница |\n");

    for (int i = 1; i <= experiments_count; ++i) 
    {
        double estimate = taylor_functions[choice - 1](x_value, 10000, i, &terms_count);
        double difference = fabs(estimate - reference_value);
        printf("| %-16d | %-16lf | %-8lf |\n", i, estimate, difference);
    }

    system("pause");
}

double get_reference_value(double x, int choice) 
{
    return с_functions[choice - 1](x);
}
