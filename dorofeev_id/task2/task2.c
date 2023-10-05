#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int RandomNumber(int min, int max)
{
  srand(time(NULL));

  int rn = min + rand() % (max - min + 1);

  return rn;
}

int mode1(int Popytka, int UgadNumber)
{
    int KolPop = 0;
    while(1 == 1)
    {
        KolPop++;
        if (Popytka == UgadNumber)
        {
            printf("Угадали за %d попыток\n", KolPop);
            return 0;
        }
        else if (Popytka > UgadNumber)
        {
            printf("Загаданное число меньше\n");
            scanf("%d", &Popytka);
        }
        else if (Popytka < UgadNumber)
        {
            printf("Загаданное число больше\n");
            scanf("%d", &Popytka);
        }            
    }
}

int mode2(int UgadNumber)
{
    int KolPop = 0;
    int LeftGr = 1;
    int RightGr = 999;
    int Popytka = (LeftGr + RightGr) / 2;
    while (1 == 1)
    {
        KolPop++;
        Popytka = (LeftGr + RightGr) / 2;
        char Verdikt;
        printf("Если вы загадали число %d, введите \"=\".\n", Popytka);
        printf("Если число %d больше загаданного вами, введите \">\".\n", Popytka);
        printf("Если число %d меньше загаданного вами, введите \"<\".\n", Popytka);
        scanf("\n%c", &Verdikt);

        if (Verdikt == '>')
            RightGr = (LeftGr + RightGr) / 2;
        else if (Verdikt == '<')
            LeftGr = (LeftGr + RightGr) / 2;
        else
        {
            printf("Программа угадала число за %d попыток\n", KolPop);
            return 0;
        }

    }

    return 0;
}



int main()
{
    
    int mode = 0;
    while (1 == 1)
    {
        printf("Выберите режим (1 | 2)\n");
        scanf("%d", &mode);
        if (mode == 1 || mode == 2)
            break;
        else
            printf("Некорректный ввод. Попробуйте ещё раз!\n");
    }

    if (mode == 1)
    {
        int UgadNumber = RandomNumber(1, 999);
        int Popytka;
        printf("Программой было загадано число от 1 до 999, попробуйте его угадать\n");
        scanf("%d", &Popytka);
        mode1(Popytka, UgadNumber);
    }

    if (mode == 2)
    {
        int ZagadNumber;
        while (1 == 1)
        {
            printf("Загадайте число от 1 до 999, программа попытается его угадать\n");
            scanf("%d", &ZagadNumber);
            if (ZagadNumber >= 1000 || ZagadNumber < 0)
                printf("Некорректный ввод. Попробуйте ещё раз!\n");
            else
                break;
        }
        mode2(ZagadNumber);
    }

    return 0;
}
