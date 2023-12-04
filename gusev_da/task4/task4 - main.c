#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <locale.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

// Структура для товаров
struct Samsung {
    char article[5];
    char name[30];
    int price;
    int count;
    int final_price;
};

struct Samsung S23 = { "0231", "Samsung Galaxy S23", 59000, 0, 0 };
struct Samsung Flip5 = { "2015", "Samsung Galaxy Z Flip5", 70000, 0, 0 };
struct Samsung Fold5 = { "2025", "Samsung Galaxy Z Fold5", 102000, 0, 0 };
struct Samsung A54 = { "2354", "Samsung Galaxy A54", 87000, 0, 0 };
struct Samsung Watch6 = { "2306", "Samsung Galaxy Watch6", 212000, 0, 0 };

// Алгоритм для перемешивания элементов массива со скидкой
int shuffle(int* arr, int N)
{
    srand(time(0));
    for (int i = N - 1; i >= 1; i--)
    {
        int j = rand() % (i + 1);
        int temp = arr[j];
        arr[j] = arr[i];
        arr[i] = temp;
    }
}

// Алгоритм для сканирования данных в меню
int scan_methods(int* result, int min_v, int max_v)
{
    int methods;
    methods = scanf_s("%d", result);
    while (getchar() != '\n');
    if (methods == 1 && *result >= min_v && *result <= max_v)
        return 1;
    return 0;
}

// Сканер
int scanner_menu()
{
    int sale[] = { 5, 10, 15, 20, 25, 30, 35, 40, 45, 50 }; // Скидка на товар 5-50%

    char art[5]; // Артикул, вводимый пользователем
    char end[5] = "0000"; // Конечный артикул

    int total_price = 0; // Цена без скидки
    int final_price = 0; // Цена со скидкой

    /* Так как у нас массив без повторений, то нам неважно,
       какая скидка будет первой-десятой, ведь нам нужно
       всего 5 различных значений, т.е. будем брать первые
       5 индексов как рандомные значения скидки для каждого из товаров */
    shuffle(sale, 10);
    /* Мы можем сколько угодно раз запускать программу и значения скидок будут разные
       для каждого из товаров, поэтому мы можем спокойно использовать такой метод
       рандомного значения для скидки */

    system("cls");
    printf("---Сканер---\n");
    printf("Введите 0000, чтобы создать чек и закрыть программу.\n");
    printf("Введите артикул: ");

    do
    {
        scanf("%s", &art);
        if (strcmp(S23.article, art) == 0)
        {
            system("cls");
            S23.count++;
            S23.final_price = S23.count * S23.price * ((100.0 - sale[0]) / 100);
            printf("---Сканер---\n");
            printf("Введите 0000, чтобы создать чек и закрыть программу.\n");
            printf("-----------------------------------------------------------------------------------\n\n"
                "%s - %d руб. - %d шт. - %d руб. (с учётом скидки %d%%)"
                "\n\n-----------------------------------------------------------------------------------\n", S23.name, S23.price, S23.count, S23.final_price, sale[0]);
            final_price += S23.final_price;
            total_price += S23.count * S23.price;
        }
        else if (strcmp(Flip5.article, art) == 0)
        {
            system("cls");
            Flip5.count++;
            Flip5.final_price = Flip5.count * Flip5.price * ((100.0 - sale[1]) / 100);
            printf("---Сканер---\n");
            printf("Введите 0000, чтобы создать чек и закрыть программу.\n");
            printf("-----------------------------------------------------------------------------------\n\n"
                "%s - %d руб. - %d шт. - %d руб. (с учётом скидки %d%%)"
                "\n\n-----------------------------------------------------------------------------------\n", Flip5.name, Flip5.price, Flip5.count, Flip5.final_price, sale[1]);
            final_price += Flip5.final_price;
            total_price += Flip5.count * Flip5.price;
        }
        else if (strcmp(Fold5.article, art) == 0)
        {
            system("cls");
            Fold5.count++;
            Fold5.final_price = Fold5.count * Fold5.price * ((100.0 - sale[2]) / 100);
            printf("---Сканер---\n");
            printf("Введите 0000, чтобы создать чек и закрыть программу.\n");
            printf("-----------------------------------------------------------------------------------\n\n"
                "%s - %d руб. - %d шт. - %d руб. (с учётом скидки %d%%)"
                "\n\n-----------------------------------------------------------------------------------\n", Fold5.name, Fold5.price, Fold5.count, Fold5.final_price, sale[2]);
            final_price += Fold5.final_price;
            total_price += Fold5.count * Fold5.price;
        }
        else if (strcmp(A54.article, art) == 0)
        {
            system("cls");
            A54.count++;
            A54.final_price = A54.count * A54.price * ((100.0 - sale[3]) / 100);
            printf("---Сканер---\n");
            printf("Введите 0000, чтобы создать чек и закрыть программу.\n");
            printf("-----------------------------------------------------------------------------------\n\n"
                "%s - %d руб. - %d шт. - %d руб. (с учётом скидки %d%%)"
                "\n\n-----------------------------------------------------------------------------------\n", A54.name, A54.price, A54.count, A54.final_price, sale[3]);
            final_price += A54.final_price;
            total_price += A54.count * A54.price;
        }
        else if (strcmp(Watch6.article, art) == 0)
        {
            system("cls");
            Watch6.count++;
            Watch6.final_price = Watch6.count * Watch6.price * ((100.0 - sale[4]) / 100);
            printf("---Сканер---\n");
            printf("Введите 0000, чтобы создать чек и закрыть программу.\n");
            printf("-----------------------------------------------------------------------------------\n\n"
                "%s - %d руб. - %d шт. - %d руб. (с учётом скидки %d%%)"
                "\n\n-----------------------------------------------------------------------------------\n", Watch6.name, Watch6.price, Watch6.count, Watch6.final_price, sale[4]);
            final_price += Watch6.final_price;
            total_price += Watch6.count * Watch6.price;
        }
        else if (strcmp(end, art) == 0)
            printf("Конечный артикул\n");
        else
            printf("Неверный артикул\n");
    } while (strcmp(end, art) != 0);
    system("cls");
    if (S23.count == 0 && Flip5.count == 0 && Fold5.count == 0 && Watch6.count == 0 && A54.count == 0)
    {
        printf("Вы ничего не купили");
        return 0;
    }

    system("cls");
    printf("-----------------------------------------------------------------------------------\n"
        "ЧЕК НА ПОКУПКУ В МАГАЗИНЕ 'SAMSUNG STORE'"
        "\n-----------------------------------------------------------------------------------\n");

    if (S23.count != 0)
    {
        printf("\n"
            "Samsung Galaxy S23 - %d руб. - %d шт. - %d руб. (с учётом скидки %d%%)"
            "\n", S23.price, S23.count, S23.final_price, sale[0]);
    }
    if (Flip5.count != 0)
    {
        printf("\n"
            "Samsung Galaxy Z Flip5 - %d руб. - %d шт. - %d руб. (с учётом скидки %d%%)"
            "\n", Flip5.price, Flip5.count, Flip5.final_price, sale[1]);
    }
    if (Fold5.count != 0)
    {
        printf("\n"
            "Samsung Galaxy Z Fold5 - %d руб. - %d шт. - %d руб. (с учётом скидки %d%%)"
            "\n", Fold5.price, Fold5.count, Fold5.final_price, sale[2]);
    }
    if (A54.count != 0)
    {
        printf("\n"
            "Samsung Galaxy A54 - %d руб. - %d шт. - %d руб. (с учётом скидки %d%%)"
            "\n", A54.price, A54.count, A54.final_price, sale[3]);
    }
    if (Watch6.count != 0)
    {
        printf("\n"
            "Samsung Galaxy Watch6 - %d руб. - %d шт. - %d руб. (с учётом скидки %d%%)"
            "\n", Watch6.price, Watch6.count, Watch6.final_price, sale[4]);
    }

    printf("\n-----------------------------------------------------------------------------------\n"
        "Общая стоимость товаров - %d руб.\n"
        "Итоговая скидка - %d руб.\n"
        "Итоговая сумма к оплате - %d руб.\n"
        "-----------------------------------------------------------------------------------\n", total_price, total_price - final_price, final_price);
    system("pause");
}

// Меню с артикулами
int sub_menu()
{
    int option_sub;
    do
    {
        system("cls");
        printf("---Cписок доступных артикулов---\n\n");
        printf("%s - %s - %d руб.\n", S23.article, S23.name, S23.price);
        printf("%s - %s - %d руб.\n", Flip5.article, Flip5.name, Flip5.price);
        printf("%s - %s - %d руб.\n", Fold5.article, Fold5.name, Fold5.price);
        printf("%s - %s - %d руб.\n", A54.article, A54.name, A54.price);
        printf("%s - %s - %d руб.\n", Watch6.article, Watch6.name, Watch6.price);
        printf("\n1) Вернуться в меню\n2) Включить сканер\n3) Выключить программу\n\n");
        printf(">>> ");
    } while (!scan_methods(&option_sub, 1, 3));
    switch (option_sub)
    {
    case 1:
        main_menu();
        break;
    case 2:
        scanner_menu();
    case 3:
        exit(1);
    }
}

// Основное меню
int main_menu()
{
    int option_main;
    do
    {
        system("cls");
        printf("Привет вас на электронной кассе 'Samsung Store'!\n"
            "Введите артикул товара, чтобы добавить его в итоговый чек.\n"
            "Введите 0000, чтобы сформировать чек.\n\n");
        printf("1) Cписок доступных артикулов\n2) Включить сканер\n3) Выключить программу\n\n");
        printf(">>> ");
    } while (!scan_methods(&option_main, 1, 2));
    switch (option_main)
    {
    case 1:
        sub_menu();
        break;
    case 2:
        scanner_menu();
    case 3:
        exit(1);
    }
}

// Основной блок программы
void main()
{
    setlocale(LC_ALL, "Rus.UTF8");
    main_menu();
}