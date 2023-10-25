#include <stdio.h>
#include <locale.h>
#include <time.h>
#include <math.h>

int digit(int random, int n)
{
    int new_arr[10] = { 0 };
    int edit_input;
    int input_p = random;
    while (input_p > 0)
    {
        edit_input = input_p % 10;
        input_p = input_p / 10;
        new_arr[edit_input]++;
    }
    int i;
    for (i = 1; i < 10; i++)
    {
        if (new_arr[i] > 1)
        {
            return 1;
            break;
        }
        return 0;
    }
}

void main()
{
    setlocale(LC_ALL, "Rus");
    srand(time(0));

    int n; // Вводимое пользователем число (длина числа - от 2 до 5 цифр)
    int rand_ch; // Число, которое загадал компьютер
    int input_p = 0; // Вводимое пользователем число
    int cows = 0; // Кол-во коров
    int bulls = 0; // Кол-во быков
    int arr_a[10] = { 0 }; // Массив цифр (вычисление повтора)
    int arr_rand[10] = { 0 }; // Массив рандома (вычисление повтора)
    int last; // Последнее число массива
    int last_rand; //  Последнее число массива рандома
    int r_ch, new_input; // Заменяемые значения ввода в циклах и т.д.
    int attemts = 0; // Вводимое пользователем число
    int flag = 0;

    printf("Привет! Это игра 'Быки и Коровы' \n");

    do
    {
        printf("Впиши длину числа, которое тебе загадает компьютер.\n"
                "Это должна быть цифра, равная длине от 2 до 5.\n"
                "Длина числа - ");
        scanf_s("%d", &n);

        if ((n < 2) || (n > 5))
        {
            printf("Попробуй снова - неверная длина. \n");
            flag = 1;
        }
        else
           flag = 0;
    } while (flag == 1);
    
    do
    {
        rand_ch = rand() % ((int)(pow(10, n) - pow(10, n - 1))) + (int)pow(10, n - 1);
        if (digit(rand_ch, n))
            flag = 1;
        else
            flag = 0;
    } while (flag == 1);

    r_ch = rand_ch;

    for (int i = 1; i <= n; i++)
    {
        last_rand = r_ch % 10;
        arr_rand[last_rand]++;
        r_ch = r_ch / 10;
    }

    r_ch = rand_ch;

    for (int i = 1; i <= n; i++)
        r_ch = r_ch / 10;

    printf("Число загадано, попробуй отгадать.\n"
            "Если решишься сдаться, введи -1 в любое время.\n");

    while (1)
    {
        cows = 0;
        bulls = 0;
        for (int i = 0; i < 10; i++)
            arr_a[i] = 0;

        do
        {
            printf("Введи свой вариант ответа с цифрами без повторений.\n");
            scanf_s("%d", &input_p);
            if (input_p >= pow(10, n))
                printf("Вне диапозона.\n");
        } while (input_p >= pow(10, n));

        if (input_p == -1)
        {
            printf("Жаль, что ты сдался! Я загадал число %d!\nКол-во попыток - %d\nПока!\n", rand_ch, attemts);
            break;
        }
        if (input_p == rand_ch)
        {
            printf("Ура! Ты угадал число!\n");
            break;
        }

        r_ch = rand_ch;
        new_input = input_p;

        for (int i = 1; i <= n; i++)
        {
            if (r_ch % 10 == new_input % 10)
                bulls = bulls + 1;
            last = new_input % 10;
            arr_a[last]++;
            new_input = new_input / 10;
            r_ch = r_ch / 10;
        }

        for (int i = 0; i < 10; i++)
        {
            if ((arr_rand[i] > 0) && (arr_a[i] > 0))
                cows = cows + arr_a[i];
        }
        attemts++;
        printf("Кол-во коров - %d, кол-во быков - %d\nКол-во попыток - %d\n", cows - bulls, bulls, attemts);
    }
    system("pause");
}