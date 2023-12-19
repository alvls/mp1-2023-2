#ifndef modes_h
#define modes_h

#include <math.h>
#include "myfunctions.h"

// однократный расчет функции в заданной точке
void mode1() {
    double (* my_functions[4]) (double, double, int) = {my_sin, my_cos, my_exp, my_th};
    double (* functions[4]) (double) = {sin, cos, exp, tanh};
    int func_num; // номер функции
    double x; // аргумент функции
    double y1; // значение функции, вычисляемое моими функциями
    double y2; // значение функции, вычисляемое встроенными математическими функциями
    double diff; //  разница между результатом работы моей функции и эталонным значением
    double accuracy; // точность вычисления
    int N; // число элементов ряда
    
    printf("\nSelect function: \n");
    printf("1 - sin(x);\n");
    printf("2 - cos(x);\n");
    printf("3 - exp(x);\n");
    printf("4 - th(x);\n");
    printf("Enter the function number: ");
    
    scanf("%d", &func_num);
    while ((func_num < 1) || (func_num > 4)) {
        printf("Try again. There is no function for the number you entered \n");
        printf("Enter the function number from 1 to 4: ");
        scanf("%d", &func_num);
    }
    
    
    printf("Enter the point x where you want to calculate the value: ");
    scanf("%lf", &x); // lf - тип double
    if (func_num == 4) {
        while ((x > 1.570796) || (x < - 1.570796)) { // pi / 2 = 1.570796
            printf("The point x where you want to calculate the value must be from -pi/2 (- 1.570796) to pi/2 (1.570796) \n");
            printf("Enter again the point x where you want to calculate the value: ");
            scanf("%lf", &x);
        }
    }
    
    printf("Enter the accuracy of the calculation (>= 0.000001): ");
    scanf("%lf", &accuracy); // lf - тип double
    while (accuracy < 0.000001) {
        printf("The accuracy of the calculation must be no less than 0.000001 \n");
        printf("Enter again the accuracy of the calculation (>= 0.000001): ");
        scanf("%lf", &accuracy);
    }
    
    printf("Enter the number of Taylor series elements to perform the calculation: ");
    scanf("%d", &N);
    if (func_num != 4) {
        while ((N < 1) || (N > 1000)) {
            printf("The number of series elements to perform the calculation must be from 1 to 1000 \n");
            printf("Enter again the number of Taylor series elements to perform the calculation: ");
            scanf("%d", &N);
        }
    } else if (func_num == 4) {
        while ((N < 1) || (N > 20)) {
            printf("The number of series elemets for hyperbolic tangent must be from 1 to 20 \n");
            printf("This is due to the complexity of calculating Bernoulli numbers \n");
            printf("Enter again the number of Taylor series elements to perform the calculation: ");
            scanf("%d", &N);
        }
    }
    
    // сдвиг в индексе на единицу обусловлен нумерацией массивов в си с нуля
    y1 = my_functions[func_num - 1](x, accuracy, N); // вычисляем значение моими функциями
    y2 = functions[func_num - 1](x); // вычисляем значение встроенными математическими функциями
    diff = Abs(y1 - y2);
    
    printf("Result of calculations using Taylor series: %.10lf \n", y1);
    printf("Result of calculations using the built-in function: %.10lf \n", y2);
    printf("The difference between the calculated value by Taylor series and by built-in function: %.10lf \n", diff);
}

// серийный эксперимент
void mode2() {
    double (* my_functions[4]) (double, int) = {my_sin_2, my_cos_2, my_exp_2, my_th_2};
    double (* functions[4]) (double) = {sin, cos, exp, tanh};
    int func_num; // номер функции
    double x; // аргумент функции
    double y1; // значение функции, вычисляемое моими функциями
    double y2; // значение функции, вычисляемое встроенными математическими функциями
    double diff; //  разница между результатом работы моей функции и эталонным значением
    int NMax; // число экспериментов
    
    
    printf("\nSelect function: \n");
    printf("1 - sin(x);\n");
    printf("2 - cos(x);\n");
    printf("3 - exp(x);\n");
    printf("4 - th(x);\n");
    printf("Enter the function number: ");
    
    scanf("%d", &func_num);
    while ((func_num < 1) || (func_num > 4)) {
        printf("Try again. There is no function for the number you entered \n");
        printf("Enter the function number from 1 to 4: ");
        scanf("%d", &func_num);
    }
    
    printf("Enter the point x where you want to calculate the value: ");
    scanf("%lf", &x); // lf - тип double
    if (func_num == 4) {
        while ((x > 1.570796) || (x < - 1.570796)) { // pi / 2 = 1.570796
            printf("The point x where you want to calculate the value must be from -pi/2 (- 1.570796) to pi/2 (1.570796) \n");
            printf("Enter again the point x where you want to calculate the value: ");
            scanf("%lf", &x);
        }
    }
    
    printf("Enter the number of experiments (from 1 to 25): ");
    scanf("%d", &NMax);
    if (func_num != 4) {
        while ((NMax < 1) || (NMax > 25)) {
            printf("The number of experiments must be from 1 to 25 \n");
            printf("Enter again the number of experiments: ");
            scanf("%d", &NMax);
        }
    } else if (func_num == 4) {
        while ((NMax < 1) || (NMax > 20)) {
            printf("The number of series elemets for hyperbolic tangent must be from 1 to 20 \n");
            printf("This is due to the complexity of calculating Bernoulli numbers \n");
            printf("Enter again the number of Taylor series elements to perform the calculation: ");
            scanf("%d", &NMax);
        }
    }
    
    y2 = functions[func_num - 1](x); // вычисляем значение встроенными математическими функциями
    printf("_________________________________________________________________________________________________\n");
    printf("Number of terms      |Calculated value by Taylor series          |Difference with reference value \n");
    
    for (int i = 1; i <= NMax; i++) { // i - число членов
        y1 = my_functions[func_num - 1](x, i); // вычисляем значение моими функциями
        diff =  Abs(y1 - y2);
        printf("%d                    |%.10lf                               |%.10lf \n", i, y1, diff);
    }
    printf("_________________________________________________________________________________________________\n");
}

#endif
