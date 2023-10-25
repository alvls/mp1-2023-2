#include <stdio.h>
#include <locale.h>
#include <time.h>
#include <math.h>
#include <Windows.h>
#include <wincon.h>

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

    int n; // Ââîäèìîå ïîëüçîâàòåëåì ÷èñëî (äëèíà ÷èñëà - îò 2 äî 5 öèôð)
    int rand_ch; // ×èñëî, êîòîðîå çàãàäàë êîìïüþòåð
    int input_p = 0; // Ââîäèìîå ïîëüçîâàòåëåì ÷èñëî
    int cows = 0; // Êîë-âî êîðîâ
    int bulls = 0; // Êîë-âî áûêîâ
    int arr_a[10] = { 0 }; // Ìàññèâ öèôð (âû÷èñëåíèå ïîâòîðà)
    int arr_rand[10] = { 0 }; // Ìàññèâ ðàíäîìà (âû÷èñëåíèå ïîâòîðà)
    int last; // Ïîñëåäíåå ÷èñëî ìàññèâà
    int last_rand; //  Ïîñëåäíåå ÷èñëî ìàññèâà ðàíäîìà
    int r_ch, new_input; // Çàìåíÿåìûå çíà÷åíèÿ ââîäà â öèêëàõ è ò.ä.
    int attemts = 0; // Ââîäèìîå ïîëüçîâàòåëåì ÷èñëî
    int flag = 0;

    printf("Ïðèâåò! Ýòî èãðà 'Áûêè è Êîðîâû' \n");

    do
    {
        printf("Âïèøè äëèíó ÷èñëà, êîòîðîå òåáå çàãàäàåò êîìïüþòåð.\n"
                "Ýòî äîëæíà áûòü öèôðà, ðàâíàÿ äëèíå îò 2 äî 5.\n"
                "Äëèíà ÷èñëà - ");
        scanf_s("%d", &n);

        if ((n < 2) || (n > 5))
        {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
            printf("Ïîïðîáóé ñíîâà - íåâåðíàÿ äëèíà. \n");
            flag = 1;
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_WHITE);
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

    printf("×èñëî çàãàäàíî, ïîïðîáóé îòãàäàòü.\n"
            "Åñëè ðåøèøüñÿ ñäàòüñÿ, ââåäè -1 â ëþáîå âðåìÿ.\n");

    while (1)
    {
        cows = 0;
        bulls = 0;
        for (int i = 0; i < 10; i++)
            arr_a[i] = 0;

        do
        {
            printf("Ââåäè ñâîé âàðèàíò îòâåòà ñ öèôðàìè áåç ïîâòîðåíèé.\n");
            scanf_s("%d", &input_p);
            if (input_p >= pow(10, n))
            {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
                printf("Âíå äèàïîçîíà.\n");
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_WHITE);
            }
        } while (input_p >= pow(10, n));

        if (input_p == -1)
        {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
            printf("Æàëü, ÷òî òû ñäàëñÿ! ß çàãàäàë ÷èñëî %d!\nÊîë-âî ïîïûòîê - %d\nÏîêà!\n", rand_ch, attemts);
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_WHITE);
            break;
        }
        if (input_p == rand_ch)
        {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN);
            printf("Óðà! Òû óãàäàë ÷èñëî!\n");
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_WHITE);
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
SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_YELLOW);
        printf("Êîë-âî êîðîâ - %d, êîë-âî áûêîâ - %d\nÊîë-âî ïîïûòîê - %d\n", cows - bulls, bulls, attemts);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_WHITE);
    }
    system("pause");
}