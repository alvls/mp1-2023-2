#include <stdio.h>
#include <stdlib.h>
#include <time.h>



int mas_to_num(int a[], int len) {
    int num = 0;
    for (int i = 0; i < len; i++) {
        num = num*10 + a[i];
    }

    return num;
}


int one_per_num(int num)
{
    int a[10] = {0};

    while (num > 0) {
        a[num % 10]++;
        num /= 10;
    }

    int flag = 1;
    for (int i = 0; i < 10; i++) 
    {
        if (a[i] > 1) { flag = 0; break; }
    }

    return flag;
}


int num_gen(int len) {
    int num = 0;
    int a[5] = { 100, 100, 100, 100, 100 };
    while ((a[0] = rand() % 10) == 0) {}
    //printf_s("a[%i]:  %i\n", 0, a[0]);
    for (int i = 1; i < len; i++)
    {
        do
        {
            a[i] = rand() % 10;
            printf_s("a[%i]:  %i\n", i, a[i]);
        } 
        while (one_per_num(mas_to_num(a, i+1)) != 1);
    }

    num = mas_to_num(a, len);
    return num;
}


int check_length(num, len)
{
    int num_len = 0;
    for (; num > 0; num_len++) 
    {
        num /= 10;
    }
    return num_len;
}

int main()
{
    srand(time(NULL));

    // блок ввода длины
    int n = 0;
    printf_s("Choose the length of the number (from 2 to 5): ");
    while ((n > 5) || (n < 2))
    {
        printf_s("Length must be from 2 to 5: ");
        scanf_s("%i", &n);
    }

    // блок генерации числа
    int pc_num = 0;
    int a[5] = { 100, 100, 100, 100, 100 };
    while ((a[0] = rand() % 10) == 0) {}
    for (int i = 1; i < n; i++)
    {
        do
        {
            a[i] = rand() % 10;
        } 
        while (one_per_num(mas_to_num(a, i + 1)) != 1);
    }
    pc_num = mas_to_num(a, n);

    // пользователь вводит число
    int num = 0, flag = 0, user_len = NULL, b[5] = { 0 };
    while (flag == 0) 
    {
        printf_s("Enter your number or '0' to give up\n");
        scanf_s("%i", &num);
        
        // проверка пользовательского ввода
        if (num == 0)
        {
            flag = -1;
            continue;
        }
        user_len = check_length(num, n);
        if (user_len != n) 
        { 
            printf("Incorrect length\nIt must be %i, but your number is %i-digits\n", n, user_len);
            continue;
        }
        if (one_per_num(num) != 1)
        {
            printf("There are repeating digits in your number\n That's wrong\n");
            continue;
        }
        if (num == pc_num)
        {
            flag = 1;
            continue;
        }

        // перевод пользовательского числа в массив (для удобства)
        for (int i = 0; i < n; i++)
        {
            b[n - i - 1] = num % 10;
            num /= 10;
        }

        // подсчёт быков и коров
        int cow = 0, ox = 0;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (a[i] == b[j])
                {
                    if (i == j)
                        ox++;
                    else
                        cow++;
                }
            }
        }
        printf("cows = %i, oxen = %i \n", cow, ox);
    }
    
    // завершение
    if (flag == 1) { printf_s("\nYes, it was %i\n", pc_num); }
    else { printf_s("\nIt was %i, try harder next time\n", pc_num); }
   
    system("pause");
    return 0;
} 