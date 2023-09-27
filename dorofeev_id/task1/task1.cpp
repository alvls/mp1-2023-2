#define _CRT_NO_SECURE_WARNINGS
#include <stdio.h>
#include <math.h>
#include <locale.h>


int main()
{
    setlocale (LC_ALL, "rus");
    double PlDvp = (950*0.000001);
    double PlDsp = (750*0.000001);
    double PlWood = (700*0.000001);
    double WDsp = 1.5;

    int h, w, d;
    while (1 == 1)
    {
        printf("Введите высоту\n");
        scanf("%d", &h);
        if (h >= 180 && h <= 220)
        {
            break;
        }
        else
        {
            printf("Некорректная высота\n");
        }
    }

    while (1 == 1)
    {
        printf("Введите ширину\n");
        scanf("%d", &w);
        if (w >= 80 && w <= 120)
        {
            break;
        }
        else
        {
            printf("Некорректная ширина\n");
        }
    }

    while (1 == 1)
    {
        printf("Введите глубину\n");
        scanf("%d", &d);
        if (d >= 50 && d <= 90)
        {
            break;
        }
        else
        {
            printf("Некорректная глубина\n");
        }
    }



    double WeightSt = h*w*PlDvp;
    double WeightBok = 2*(h*d*WDsp*PlDsp);
    double WeightKr = 2*(w*d*WDsp*PlDsp);
    double WeightDoor = 2*(h*(w/2)*1*PlWood);

    double WPolka = w - 0.3;
    int KolPolok = 0;
    double HPolki = 40.15;
    double hh = h;
    while (hh - HPolki > 0)
    {
        KolPolok++;
        hh -= HPolki;
    }

    double WeightPolok = KolPolok*(WPolka * WDsp * d * PlDsp);
    double Weight = WeightBok + WeightDoor + WeightKr + WeightSt + WeightPolok;
    printf("Вес шкафа %g кг\n", Weight);

    return 0;
}


