#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

int GetRandomNumber(int mn, int mx)
{
    return mn + rand() % (mx - mn + 1);
}

int check(int chislo, int dlina)
{
    int pred = chislo % 10;
    chislo /= 10;
    int tmp;
    for (int i = 0; i < dlina; i++)
    {
        tmp = chislo % 10;
        if (tmp == pred)
        {
            return 1;
        }
        else
        {
            chislo /= 10;
            pred = tmp;
        }
    }

    return 0;
}

int ChislGenerator(int dlina)
{
    int* Cifri = malloc(dlina);
    int UsedCifri[10] = { 0 };

    for (int i = 0; i < dlina; i++)
    {
        int Cifra = GetRandomNumber(1, 9);
        while (UsedCifri[Cifra] == 1)
        {
            Cifra = GetRandomNumber(1, 9);
        }

        UsedCifri[Cifra] = 1;
        Cifri[i] = Cifra;
    }

    int Chislo = 0;
    for (int i = 0; i < dlina; i++)
    {
        Chislo = Chislo * 10 + Cifri[i];
    }

    return Chislo;
}

int DlinaChisla(int chislo)
{
    int dlina = 0;
    while (chislo > 0)
    {
        dlina++;
        chislo /= 10;
    }
    return dlina;
}

char* Sravnitel(int c1, int c2)
{
    char c1s[50], c2s[50];
    int pos_match = 0, dig_match = 0;
    sprintf(c1s, "%d", c1);
    sprintf(c2s, "%d", c2);

    int len1 = strlen(c1s);
    int len2 = strlen(c2s);

    for (int i = 0; i < len1; i++)
    {
        for (int j = 0; j < len2; j++)
        {
            if (c1s[i] == c2s[j])
            {
                if (i == j)
                {
                    pos_match++;
                }
                else
                {
                    dig_match++;
                }
            }
        }
    }

    char* ans = malloc(50);
    sprintf(ans, "%d коров, %d быков\n", dig_match, pos_match);
    return ans;
}

int game(int chislo, int dlina)
{
    int dogadka;
    while (1 == 1)
    {
        printf("Введите свою догадку\n");
        scanf("%d", &dogadka);
        int ChislDl = DlinaChisla(dogadka);
        int ChislCheck = check(dogadka, dlina);
        if (ChislDl == dlina && ChislCheck == 0)
        {
            char* verdikt;
            if (dogadka == chislo)
            {
                printf("Поздравляю, вы выиграли!");
                return 0;
            }
            verdikt = Sravnitel(dogadka, chislo);
            printf("%s", verdikt);
            free(verdikt);
            printf("Если вы хотите сдаться, нажмите \"CTRL+C\", иначе введите догадку\n");

        }
        else
        {
            printf("Вы ввели неподходящее число, повторите\n");
        }

    }
}

int main()
{
    setlocale(LC_ALL, "rus");
    srand(time(NULL));

    int n = 0;
    while (1 == 1)
    {
        printf("Введите длину загадываемого числа\n");
        scanf("%d", &n);
        if (n >= 2 && n <= 5)
        {
            break;
        }
        else
        {
            printf("Некорректный ввод. Попробуйте ещё раз!\n");
        }
    }

    int Chislo = ChislGenerator(n);

    printf("%d\n", Chislo);

    game(Chislo, n);

    return 0;
}