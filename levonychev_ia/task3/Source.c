#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <locale.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>
#include <Windows.h>
#include <wincon.h>

void game(int n);
int exit_status(); // Если пользователь захочет сдаться
int f(int num, int n); // Возвращает 0, если в числе есть повторяющиеся цифры, 1 - если их нет
int cows_bulls(int num, int user_num, int flag); // flag = 0 - коровы, flag = 1 - быки
int len_num(int num, int n); // Возвращает 0, если длина num не совпадает с n, 1 - если совпадает 


void main()
{   
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN);
    int n;
    setlocale(LC_ALL, "rus");
    srand(time(NULL));
    printf("    Игра \'Быки и коровы\'. Если вы угадали, что цифра есть в загаданном числе, но не на своем месте - это \'Корова\'. Если угадали вплоть до позиции - \'Бык\'.");
    
    do
    {   
        printf("\n\n\nВыберите n от ");
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
        printf("2 ");
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN);
        printf("до ");
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
        printf("5 ");
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN);
        printf(". Введите ");
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
        printf("0 ");
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN);
        printf("если хотите выйти.\n");
        do
        {   
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
            scanf("%d", &n);
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN);
            if (!(n == 0 || (n >= 2 && n <= 5)))
                printf("Некорректный ввод.\n");
        } while (!(n == 0 || (n >= 2 && n <=5)));
        
        if (n >= 2 && n <= 5)
            game(n);

    } while (n >= 2 && n <= 5);

    system("pause");
    return;

}   

void game(int n)
{
    int num;
    int user_num;
    int bulls, cows;
    int i = 1;
    int flag_exit;
    int a = 9 * pow(10, n-1);

    // Генерация числа
    do
    {
        num = pow(10, n-1) + (rand() % a);
    } while (f(num, n) == 0);
    // Генерация числа
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
    printf("\n--------------------\n");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN);
    if (n == 2)
        printf("Вы выбрали режим с двузначным числом.\n");
    if (n == 3)
        printf("Вы выбрали режим с трехзначным числом.\n");
    if (n == 4)
        printf("Вы выбрали режим с четырехзначным числом.\n");
    if (n == 5)
        printf("Вы выбрали режим с пятизначным числом.\n");
    printf("Пытайтесь угадать число. Программа ожидает число с неповторяющимися цифрами. Если вы введете с повторяющимися, она попросит ввод заново. Вы всегда можете сдаться, введя 0.\n");
    //printf("%d\n", num); // показать загаданное число
    do
    {   
        printf("%d.\n", i);
        do
        {   
            printf("   ");
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
            scanf("%d", &user_num);
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN);
            if (f(user_num, n) == 0 || len_num(user_num, n) == 0)
                printf("   Некорректный ввод.\n");
        } while (f(user_num, n) == 0 || len_num(user_num, n) == 0);
        
        cows = bulls = 0;

        if (user_num == 0)
        {

            flag_exit = exit_status();
            if (flag_exit == 1)
            {   
                printf("Загаданное число: ");
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
                printf("%d", num);
                printf("\n--------------------\n", num);
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN);
                return;
            }
            if (flag_exit == 0)
                continue;
        }
        else
        {  
            cows = cows_bulls(num, user_num, 0);
            bulls = cows_bulls(num, user_num, 1);
            printf("   Количество коров: ");
            if (cows > 0)
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
            printf("%d\n", cows);
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN);
            printf("   Количество быков: ");
            if (bulls > 0)
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
            printf("%d\n", bulls);
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN);
        }

        i++;
    } while (bulls != n);

    printf("Вы угадали! Это число: ");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
    printf("%d", num);
    printf("\n--------------------\n", num);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN);

    return;
}

int exit_status()
{   
    int flag;
    do
    {      
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
        printf("Вы точно хотите сдаться? 0 - НЕТ, 1 - ДА: ");
        scanf("%d", &flag);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN);
        if ((flag != 1) && (flag != 0))
            printf("Некорректный ввод.\n");
    } while ((flag != 1) && (flag != 0));
    
    return flag;
}

int f(int num, int n)
{   
    int mas[5];
    int i = 0;
    int j;
    if (num == 0)
        return 1;
    while (num > 0)
    {
        mas[i] = num % 10;
        i++;
        num = num / 10;
    }
    for (i = 0; i < n; i++)
    {   
        j = i+1;
        for (j; j < n; j++)
        {
            if (mas[i] == mas[j])
            {
                return 0;
            }
        }
    }
    return 1;
}

int cows_bulls(int num, int user_num, int flag)
{   
    int i, j;
    int k = 0;
    int n1 = num, n2 = user_num;
    int mas_num[5], mas_user_num[5];
    int cows_bulls = 0;

    while (n1 > 0)
    {
        mas_num[k] = n1 % 10;
        mas_user_num[k] = n2 % 10;
        k++;
        n1 = n1 / 10;
        n2 = n2 / 10;

    }

    for (i = 0; i < k; i++)
    {
        for (j = 0; j < k; j++)
        {   
            if (flag == 0)
            {
                if ((mas_num[i] == mas_user_num[j]) && (i != j))
                    cows_bulls++;
            }
            
            if (flag == 1)
            {
                if ((mas_num[i] == mas_user_num[j]) && (i == j))
                    cows_bulls++;
            }
            
        }
    }
    return cows_bulls;
}

int len_num(int num, int n)
{   
    if (num == 0)
        return 1;
    int i = 0;
    while (num > 0)
    {
        i++;
        num = num / 10;
    }
    if (i == n)
        return 1;
    else
        return 0;
}