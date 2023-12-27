#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

#include "func.h"

// Объявление функций в правильном порядке
void menu_mode_1();
void menu_mode_2();
double get_value(double x, int choice);

// Считывание вариантов ответа пользователя в меню
int scan_methods(int* result, int min_v, int max_v)
{
    int methods;
    methods = scanf_s("%d", result);
    while (getchar() != '\n');
    if (methods == 1 && *result >= min_v && *result <= max_v)
        return 1;
    return 0;
}

// "Тейлоровские" функции, которые мы создали сами 
double (*taylor_func[4])(double, int, int, int*) =
{
    taylor_sin,
    taylor_cos,
    taylor_exp,
    taylor_arcsin,
};

// Функции из библиотеки math.h
double (*сur_func[4])(double) =
{
    sin,
    cos,
    exp,
    asin,
};

// Основной блок программы (основное меню)
int main()
{
    setlocale(LC_ALL, "Rus");
    int choice, flag = 1;

    while (flag == 1)
    {
        do
        {
            system("cls");
            printf("Привет!\nЭта программа позволяет выполнять расчет значений для некоторого набора функций \nв заданной точке с заданной погрешностью за счет разложения этих функций в ряд Тейлора.\nВыбери режим работы программы:\n");
            printf("1) Однократный расчет функции в заданной точке\n2) Серийный эксперимент\n3) Выключить программу\n>>> ");
        } while (!scan_methods(&choice, 1, 3));

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

// Меню первого режима
void menu_mode_1()
{
    int mode, accuracy, N, count, flag = 1;;
    double x, result, result_cur, diff;

    do
    {
        system("cls");
        printf("Выберите функцию:\n1) Синус - sin(x)\n2) Косинус - cos(x)\n3) Экспонента - exp(x)\n4) Арксинус - arcsin(x)\n>>> ");
    } while (!scan_methods(&mode, 1, 4));
    system("cls");
    do
    {
        printf("Задайте точку x, в которой необходимо вычислить значение:\n>>> ");
    } while (scanf("%lf", &x) != 1);
    do
    {
        printf("Введите нужную точность (кол-во знаков после запятой):\n>>> ");
    } while (scanf("%d", &accuracy) != 1 || accuracy < 0);
    do
    {
        printf("Введите максимальное количество членов ряда:\n>>> ");
    } while (scanf("%d", &N) != 1 || N <= 0);
    result = taylor_func[mode - 1](x, accuracy, N, &count);
    result_cur = сur_func[mode - 1](x);
    diff = fabs(result - result_cur);
    system("cls");
    printf("Эталонное значение: %lf\nОценка значения функции: %lf\nРазница между оценкой и эталонным значением: %lf\nКоличество вычесленных слагаемых: %d\n", result_cur, result, diff, count);
    system("pause");
}

// Меню второго режима
void menu_mode_2()
{
    int mode, count, terms;
    double x, est, refer_value;

    do
    {
        system("cls");
        printf("Выберите функцию:\n1) Синус - sin(x)\n2) Косинус - cos(x)\n3) Экспонента - exp(x)\n4) Арксинус - arcsin(x)\n>>> ");
    } while (!scan_methods(&mode, 1, 4));
    system("cls");
    do
    {
        printf("Задайте точку x, в которой необходимо вычислить значение:\n>>> ");
    } while (scanf("%lf", &x) != 1);
    do
    {
        printf("Введите число экспериментов (от 1 до 25):\n>>> ");
    } while (scanf("%d", &count) != 1 || count < 1 || count > 25);
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

// Функция, позволяющая брать нужную математическую функцию в данный момент
double get_value(double x, int choice)
{
    return сur_func[choice - 1](x);
}

