#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

#include "func.h"


void menu_mode_1();
void menu_mode_2();
double get_value(double x, int choice);
double calc_est(double x, int choice, int count);

double (*taylor_func[4])(double, int, int, int*) =
{
    taylor_exp,
    taylor_sin,
    taylor_cos,
    taylor_arcsin,
};

double (*сur_func[4])(double) =
{
    exp,
    sin,
    cos,
    asin,
};

int main()
{
    setlocale(LC_ALL, "Rus");
    int choice, flag = 1;

    while (flag == 1)
    {
        printf("Привет!\nЭта программа позволяет выполнять расчет значений для некоторого набора функций \nв заданной точке с заданной погрешностью за счет разложения этих функций в ряд Тейлора.\nВыбери режим работы программы:\n");
        printf("1) Однократный расчет функции в заданной точке\n2) Серийный эксперимент\n3) Выключить программу\n>>> ");
        if (scanf("%d", &choice) != 1)
        {
            while (getwchar() != "\n");
            continue;
        }

        switch (choice)
        {
        case 1:
            menu_mode_1();
            flag = 0;
            break;
        case 2:
            menu_mode_2();
            flag = 0;
            break;
        case 3:
            return;
        default:
            system("cls");
            break;
        }
    }
    return 0;
}

void menu_mode_1()
{
    int mode, accuracy, N, count, flag = 1;;
    double x, result, result_cur, diff;

    system("cls");
    printf("Выберите функцию:\n1) Синус - sin(x)\n2) Косинус - cos(x)\n3) Экспонента - exp(x)\n4) Арксинус - arcsin(x)\n5) Выйти в меню\n>>> ");
    if (scanf("%d", &mode) != 1 || mode < 1 || mode > 5)
    {
        printf("Ошибка ввода. Попробуйте ещё раз.\n");
        return;
    }
    system("cls");
    printf("Задайте точку x, в которой необходимо вычислить значение: \n");
    if (scanf("%lf", &x) != 1)
    {
        printf("Ошибка ввода. Попробуйте ещё раз.\n");
        return;
    }
    printf(L"Введите нужную точность (кол-во знаков после запятой)\n");
    if (scanf("%d", &accuracy) != 1 || accuracy < 0)
    {
        printf("Ошибка ввода. Попробуйте ещё раз.\n");
        return;
    }
    printf("Введите максимальное количество членов ряда\n");
    if (scanf("%d", &N) != 1 || N <= 0)
    {
        printf("Ошибка ввода. Попробуйте ещё раз.\n");
        return;
    }
    if (mode == 2 || mode == 3)
    {
        result = taylor_func[mode - 1](x + 1, accuracy, N, &count);
        result_cur = сur_func[mode - 1](x + 1);
    }
    else
    {
        result = taylor_func[mode - 1](x, accuracy, N, &count);
        result_cur = сur_func[mode - 1](x);
    }
    diff = fabs(result - result_cur);
    system("cls");
    printf("Эталонное значение: %lf\nОценка значения функции: %lf\nРазница между оценкой и эталонным значением: %lf\nКоличество вычесленных слагаемых: %d\n", result_cur, result, diff, count);
    system("pause");
}

void menu_mode_2()
{
    int mode, count, terms;
    double x, est, refer_value;

    system("cls");
    printf("Выберите функцию:\n1) Синус - sin(x)\n2) Косинус - cos(x)\n3) Экспонента - exp(x)\n4) Арксинус - arcsin(x)\n5) Выйти в меню\n>>> ");
    if (scanf("%d", &mode) != 1 || mode < 1 || mode > 5)
    {
        printf("Ошибка ввода. Попробуйте ещё раз.\n");
        return;
    }
    system("cls");
    printf("Задайте точку x, в которой необходимо вычислить значение: \n");
    scanf("%lf", &x);
    printf("Введите число экспериментов (от 1 до 25):\n");
    if (scanf("%d", &count) != 1 || count < 1 || count > 25)
    {
        printf("Ошибка ввода. Попробуйте ещё раз.\n");
        return;
    }
    system("cls");
    if (mode == 2 || mode == 3)
    {
        refer_value = get_value(x + 1, mode);
    }
    else
    {
        refer_value = get_value(x, mode);
    }
    printf("Эталонное значение: %lf\nОценка значения   Разница \n", refer_value);
    for (int i = 1; i <= count; ++i)
    {
        if (mode == 2 || mode == 3)
        {
            est = taylor_func[mode - 1](x + 1, 10000, i, &terms);
        }
        else
        {
            est = taylor_func[mode - 1](x, 10000, i, &terms);
        }
        double difference = fabs(est - refer_value);
        printf("%-16lf  %-8lf \n", est, difference);
    }
    system("pause");
}

double get_value(double x, int choice)
{
    return сur_func[choice - 1](x);
}
