#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <locale.h>

int main()
{
    setlocale(LC_ALL, "rus");

    float h, w, d, m1, m2, m3, m4, m5, t1, t2, t3, chipboard_density, fiberboard_density, wood_density, m;
    int N;

    chipboard_density = 600;    //ДСП
    fiberboard_density = 850;   //ДВП
    wood_density = 800;         //Дерево
    t1 = 0, 5;                   //Толщина накладной задней стенки
    t2 = 1, 5;                   //накладной верхней и нижней крышки, двух боковин из ДСП
    t3 = 1;                     //двух накладные двери

    printf("Введите высоту h от 180 до 220см: ");
    scanf("%f", &h);

    printf("Введите ширину w от 80 до 120см: ");
    scanf("%f", &w);

    printf("Введите глубину d от 50 до 90см: ");
    scanf("%f", &d);

    if (h > 220 || h < 180)
    {
        printf("Неверные данные в h");
        return 0;
    }
    else if (w > 120 || w < 80)
    {
        printf("Неверные данные в w");
        return 0;
    }
    else if (d > 90 || d < 50)
    {
        printf("Неверные данные в d");
        return 0;
    }
    else
    {
        m1 = (h / 100) * (w / 100) * (t1 / 100) * fiberboard_density;

        m2 = 2 * (h / 100) * (d / 100) * (t2 / 100) * chipboard_density;

        m3 = 2 * (w / 100) * (d / 100) * (t2 / 100) * chipboard_density;

        m4 = (h / 100) * (w / 100) * (t3 / 100) * wood_density;

        N = (int)(h - 1) / 40;


        m5 = N * ((w / 100) - (2 * (t2 / 100))) * (d / 100) * (t2 / 100) * chipboard_density;

        m = m1 + m2 + m3 + m4 + m5;

        printf("%f", m);
    }

}
