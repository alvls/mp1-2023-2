#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

int GetRandomNumber (int mn,  int mx)
{
    return mn + rand() % (mx - mn + 1);
}

int check(int chislo, int dlina)
{
    int pred = chislo % 10;
    chislo /= 10;
    int tmp;
    for(int i = 0; i < dlina; i++)
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
    int PredCifra = GetRandomNumber(1, 9);
    int chislo = PredCifra * pow(10, dlina - 1);
    int tmp = -1;
    for (int i = 0; i < dlina - 1; i++)
    {
        do
        {
            tmp = GetRandomNumber(0, 9);
        } while(tmp == PredCifra);
        chislo += tmp * pow(10, i);
        PredCifra = tmp;
    }
    return chislo;
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
    int pos_match = 0;
    int dig_match = 0;
    int byks = 0;
    int tmp1 = c1, tmp2 = c2;
    int checked[10] = {0};

    while (tmp1 > 0)
    {
        int dig1 = tmp1 % 10;
        int tmp = tmp2;
        int pos_fnd = 0;

        while(tmp > 0)
        {
            int dig2 = tmp % 10;

            if (dig1 == dig2)
            {
                dig_match++;
                if (!checked[dig2])
                {
                    checked[dig2] = 1;
                    pos_match++;
                    pos_fnd = 1;
                    break;
                }
            }
            tmp /= 10;
        }

        if (pos_fnd)
        {
            checked[dig1] = 1;
        }
        tmp1 /= 10;
    }
    char* ans = malloc(50); 
    sprintf(ans, "%d коров, %d быков", dig_match - pos_match, pos_match);
    return ans;
}

int game(int chislo, int dlina)
{
    int dogadka;
    while (1 == 1)
    {
        printf("Введите свою догадку");
        scanf("%d", dogadka);
        if (DlinaChisla(dogadka) > dlina || DlinaChisla(dogadka) < dlina || check(dogadka, dlina) == 1)
        {
            printf("Вы ввели неподходящее число, повторите");
        }
        else
        {
            break;
        }
        char* verdikt;
        verdikt = Sravnitel(dogadka, chislo);
        printf("%s", verdikt);
        free(verdikt);
        printf("Если вы хотите сдаться, введите \"s\", иначе введите догадку");
    }
}

int main()
{
    setlocale(LC_ALL, "rus");
    srand(time(NULL));
    
    int n;
    printf("Введите длину загадываемого числа\n");
    scanf("%d", &n);

    game(1251, 4);
    
    return 0;
}