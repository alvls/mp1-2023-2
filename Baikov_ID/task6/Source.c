#define _CRT_SECURE_NO_WARNINGS
#include <math.h>
#include <stdio.h>
#include "functions.c"
#include <locale.h>

int main() {
    int mode, func_choice, max_terms;
    double x, precision, result;
    int num_terms;

    setlocale(LC_ALL, "RUS");

    mode = menu();
    get_input(mode, &func_choice, &x, &precision, &max_terms);

    FunctionPointer selected_function;
    
    switch (func_choice) {
    case 1:
        selected_function = sin_a;
        break;
    case 2:
        selected_function = cos_a;
        break;
    case 3:
        selected_function = exp_a;
        break;
    case 4:
        selected_function = ln1plusx_a;
        break;
    default:
        printf("Некорректный выбор функции\n");
        return 1;
    }

    if (mode == 1) {
        calculate(selected_function, x, precision, max_terms, &result, &num_terms);
        print_results(selected_function(x), result, fabs(result - selected_function(x)), precision, num_terms);
    }
    else if (mode == 2) {
        printf("Введите число экспериментов: ");
        int num_experiments;
        scanf("%d", &num_experiments);

        if (num_experiments > 25) {
            printf("Некорректное значение! Введите число от 1 до 25: ");
            scanf("%d", &num_experiments);
        }

        double true_value = selected_function(x);

        printf("Точное значение: %.11f\n", true_value);
        printf("\n");
        printf("%-20s%-20s%-20s\n", "Количество слагаемых", "Расчетное значение", "Разница");

        for (int i = 1; i <= num_experiments; ++i) {
            calculate(selected_function, x, precision, i, &result, &num_terms);
            printf("%-20d%-20.11f%-20.11f\n", num_terms, result, fabs(result - true_value));
        }
    }

    return 0;
}