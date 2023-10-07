#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <locale.h>
#include <time.h>
#include <stdlib.h>

void regime_1() {
    srand(time(0));
    int num = rand() % 1000;
    //printf("%d \n", num);
    int a;
    int count = 0;
    int flag = 1;
    printf("Я (программа) загадала случайное число из диапазона от 1 включительно до 1000 невключительно. Попытайся угадать его: \n");
    while (flag == 1) {
        scanf("%d", &a);
        if (a < num) {
            count++;
            printf("Загаданное число больше \n");
        }
        else if (a == num) {
            count++;
            printf("Угадали! \n");
            printf("Число попыток: %d \n", count);
            flag = 0;
        }
        else if (a > num) {
            count++;
            printf("Загаданное число меньше \n");
        }
    }
}

void regime_2() {
    int num;
    char symbol;
    int count = 0;
    int flag = 1;
    int min = 0, max = 1000;
    printf("Загадайте случайное число из диапазона от 1 включительно до 1000 невключительно. Я (программа) попытаюсь угадать его. Мне можно отвечать символами > (загаданное число больше), < (загаданное число меньше) или = . \n");
    while (flag == 1) {
        srand(time(0));
        num = min + rand() % (max - min);
        printf("Это число %d ?\n", num);
        scanf(" %c", &symbol);
        if (symbol == '<') {
            count++;
            max = num;
        }
        else if (symbol == '=') {
            count++;
            printf("я угадала! \n");
            printf("Число попыток: %d \n", count);
            flag = 0;
        }
        else if (symbol == '>') {
            count++;
            min = num;
        }
    }
}


void main() {
    int r, ch; // r - режим программы, ch - для очистки буфера клавиатуры
    setlocale(LC_ALL, "rus");
    printf("У меня есть 2 режима игры для вас. Выберите режим игры: regime_1 или regime_2. \nВведите 1, если выбрали первый режим, или 2, если выбрали второй: \n");
    scanf("%d", &r);
    while ((r != 1) && (r != 2)) {
        printf("Введите 1 или 2: \n");
        scanf("%d", &r);
    }
    if (r == 1) {
        regime_1();
    }
    else if (r == 2) {
        regime_2();
    }
}

