#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <locale.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

int shuffle(int* arr, int N) // Алгоритм для перемешивания элементов массива со скидкой
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

void main()
{
    setlocale(LC_ALL, "Rus.UTF8");

    int sale[] = { 5, 10, 15, 20, 25, 30, 35, 40, 45, 50 }; // Скидка на товар 5-50%

    char s23[5] = "0231"; // Артикул Samsung Galaxy S23
    int price_s23 = 99990; // Цена Samsung Galaxy S23
    int kol_s23 = 0; // Кол-во Samsung Galaxy S23
    int fp_s23 = 0; // Финальная цена за все Samsung Galaxy S23

    char flip5[5] = "2015"; // Артикул Samsung Galaxy Z Flip5
    int price_flip5 = 89990; // Цена Samsung Galaxy Z Flip5
    int kol_flip5 = 0; // Кол-во Samsung Galaxy Z Flip5
    int fp_flip5 = 0; // Финальная цена за все Samsung Galaxy Z Flip5

    char fold5[5] = "2025"; // Артикул Samsung Galaxy Z Fold5
    int price_fold5 = 139990; // Цена Samsung Galaxy Z Fold5
    int kol_fold5 = 0; // Кол-во Samsung Galaxy Z Fold5
    int fp_fold5 = 0; // Финальная цена за все Samsung Galaxy Z Fold5

    char a54[5] = "2354"; // Артикул Samsung Galaxy A54
    int price_a54 = 39990; // Цена Samsung Galaxy A54
    int kol_a54 = 0; // Кол-во Samsung Galaxy A54
    int fp_a54 = 0; // Финальная цена за все Samsung Galaxy A54

    char w6[5] = "2306"; // Артикул Samsung Galaxy Watch6
    int price_w6 = 24990; // Цена Samsung Galaxy Watch6
    int kol_w6 = 0; // Кол-во Samsung Galaxy Watch6
    int fp_w6 = 0; // Финальная цена за все Samsung Galaxy Watch6

    char art[5]; // Артикул, вводимый пользователем
    char end[5] = "0000"; // Конечный артикул

    int total_price = 0; // Цена без скидки
    int fp = 0; // Цена со скидкой

    /* Так как у нас массив без повторений, то нам неважно,
       какая скидка будет первой-десятой, ведь нам нужно
       всего 5 различных значений, т.е. будем брать первые
       5 индексов как рандомные значения скидки для каждого из товаров */
    shuffle(sale, 10);
    /*for (int i = 0; i < 5; i++)
        printf("%d", sale[i]); */
        /* Мы можем сколько угодно раз запускать программу и значения скидок будут разные
           для каждого из товаров, поэтому мы можем спокойно использовать такой метод
           рандомного значения для скидки */

    printf("Привет вас на электронной кассе 'Samsung Store'!\n"
        "Введите артикул товара, чтобы добавить его в итоговый чек.\n"
        "Введите 0000, чтобы сформировать чек.\n");

    do
    {
        scanf("%s", &art);
        if (strcmp(s23, art) == 0)
        {
            system("cls");
            kol_s23++;
            fp_s23 = kol_s23 * price_s23 * ((100.0 - sale[0]) / 100);
            printf("-----------------------------------------------------------------------------------\n\n"
                "Samsung Galaxy S23 - %d руб. - %d шт. - %d руб. (с учётом скидки %d%%)"
                "\n\n-----------------------------------------------------------------------------------\n", price_s23, kol_s23, fp_s23, sale[0]);
            fp += fp_s23;
            total_price += kol_s23 * price_s23;
        }
        else if (strcmp(flip5, art) == 0)
        {
            system("cls");
            kol_flip5++;
            fp_flip5 = kol_flip5 * price_flip5 * ((100.0 - sale[1]) / 100);
            printf("-----------------------------------------------------------------------------------\n\n"
                "Samsung Galaxy Z Flip5 - %d руб. - %d шт. - %d руб. (с учётом скидки %d%%)"
                "\n\n-----------------------------------------------------------------------------------\n", price_flip5, kol_flip5, fp_flip5, sale[1]);
            fp += fp_flip5;
            total_price += kol_flip5 * price_flip5;
        }
        else if (strcmp(fold5, art) == 0)
        {
            system("cls");
            kol_fold5++;
            fp_fold5 = kol_fold5 * price_fold5 * ((100.0 - sale[2]) / 100);
            printf("-----------------------------------------------------------------------------------\n\n"
                "Samsung Galaxy Z Fold5 - %d руб. - %d шт. - %d руб. (с учётом скидки %d%%)"
                "\n\n-----------------------------------------------------------------------------------\n", price_fold5, kol_fold5, fp_fold5, sale[2]);
            fp += fp_fold5;
            total_price += kol_fold5 * price_fold5;
        }
        else if (strcmp(a54, art) == 0)
        {
            system("cls");
            kol_a54++;
            fp_a54 = kol_a54 * price_a54 * ((100.0 - sale[3]) / 100);
            printf("-----------------------------------------------------------------------------------\n\n"
                "Samsung Galaxy A54 - %d руб. - %d шт. - %d руб. (с учётом скидки %d%%)"
                "\n\n-----------------------------------------------------------------------------------\n", price_a54, kol_a54, fp_a54, sale[3]);
            fp += fp_a54;
            total_price += kol_a54 * price_a54;
        }
        else if (strcmp(w6, art) == 0)
        {
            system("cls");
            kol_w6++;
            fp_w6 = kol_w6 * price_w6 * ((100.0 - sale[4]) / 100);
            printf("-----------------------------------------------------------------------------------\n\n"
                "Samsung Galaxy Watch6 - %d руб. - %d шт. - %d руб. (с учётом скидки %d%%)"
                "\n\n-----------------------------------------------------------------------------------\n", price_w6, kol_w6, fp_w6, sale[4]);
            fp += fp_w6;
            total_price += kol_w6 * price_w6;
        }
        else if (strcmp(end, art) == 0)
            printf("Конечный артикул\n");
        else
            printf("Неверный артикул\n");
    } while (strcmp(end, art) != 0);
    system("cls");
    if (kol_s23 == 0 && kol_flip5 == 0 && kol_fold5 == 0 && kol_w6 == 0 && kol_a54 == 0)
    {
        printf("Вы ничего не купили");
        return 0;
    }

    system("cls");
    printf("-----------------------------------------------------------------------------------\n"
        "ЧЕК НА ПОКУПКУ В МАГАЗИНЕ 'SAMSUNG STORE'"
        "\n-----------------------------------------------------------------------------------\n");
    
    if (kol_s23 != 0)
    {
        printf("\n"
            "Samsung Galaxy S23 - %d руб. - %d шт. - %d руб. (с учётом скидки %d%%)"
            "\n", price_s23, kol_s23, fp_s23, sale[0]);
    }
    if (kol_flip5 != 0)
    {
        printf("\n"
            "Samsung Galaxy Z Flip5 - %d руб. - %d шт. - %d руб. (с учётом скидки %d%%)"
            "\n", price_flip5, kol_flip5, fp_flip5, sale[1]);
    }
    if (kol_fold5 != 0)
    {
        printf("\n"
            "Samsung Galaxy Z Fold5 - %d руб. - %d шт. - %d руб. (с учётом скидки %d%%)"
            "\n", price_fold5, kol_fold5, fp_fold5, sale[2]);
    }
    if (kol_a54 != 0)
    {
        printf("\n"
            "Samsung Galaxy A54 - %d руб. - %d шт. - %d руб. (с учётом скидки %d%%)"
            "\n", price_a54, kol_a54, fp_a54, sale[3]);
    }
    if (kol_w6 != 0)
    {
        printf("\n"
            "Samsung Galaxy Watch6 - %d руб. - %d шт. - %d руб. (с учётом скидки %d%%)"
            "\n", price_w6, kol_w6, fp_w6, sale[4]);
    }

    printf("\n-----------------------------------------------------------------------------------\n"
        "Общая стоимость товаров - %d руб.\n"
        "Итоговая скидка - %d руб.\n"
        "Итоговая сумма к оплате - %d руб.\n"
        "-----------------------------------------------------------------------------------\n", total_price, total_price - fp, fp);
    system("pause");
}
