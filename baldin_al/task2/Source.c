#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <time.h>
#define _CRT_SECURE_NO_WARNINGS

int main()
{
    setlocale(LC_ALL, "rus");

    char ch;
    int try = 1;
    int ans;
    int hidden;

    printf("Игра <Угадай число> \n");
    printf("Выберите режим: \n");
    printf("   1. Программа загадывает - вы отгадываете \n");
    printf("   2. Вы загадываете - программма отгадывает \n");
    printf("Для пропуска нажмите любую клавишу \n");
    printf("Введите Ваш выбор: ");

    ch = getchar();

    srand(time(0));
    int num = rand() % 1000;

    switch (ch)
    {
    case '1':
        printf("Попробуйте угадать \n");
        do {
            scanf_s("%d", &ans);
            if (ans == num)
                printf("Угадали!!! Число попыток: %d \n", try);
            else
            {
                try += 1;
                if (ans < num)
                    printf("Загаданное число больше \n");
                else
                    printf("Загаданное число меньше \n");
            }

        } while (ans != num);

        break;

    case '2':
        printf("Загадайте своё число: ");
        scanf_s("%d", &hidden);
        int n1 = 0;
        int n2 = 1001;
        char user;
        int x;
        x = (n1 + n2) / 2;
        printf("Ваше число - %d? \n", x);
        do {
            scanf_s("%c", &user);
            if (user == '=')
            {
                printf("Компьютер угадал. Число попыток: %d \n", try);
                break;
            }
            else if (user == '<')
            {
                n2 = x;
                try += 1;
                x = (n1 + n2) / 2;
                printf("Ваше число - %d? \n", x);
            }
            else if (user == '>')
            {
                n1 = x;
                try += 1;
                x = (n1 + n2) / 2;
                printf("Ваше число - %d? \n", x);
            }
            else
                continue;
            
        } while (user != '=');

        break;

    default: printf("Режим не выбран");
    }
    
    system("pause");
}

