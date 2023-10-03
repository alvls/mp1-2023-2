/*
#include <stdio.h>
#include <math.h>
#include <locale.h>


void main() {

    setlocale(LC_ALL, "rus");
    double r, R, dist; // first radius, second radius, distance
    double x1, x2, y1, y2; // coordinates

    scanf_s("%lg %lg %lg", &x1, &y1, &R);
    scanf_s("%lg %lg %lg", &x2, &y2, &r);


    // determining the maximum radius, dist is used to avoid creating new variables
    if (r > R) {
        dist = R;
        R = r;
        r = dist;
    }


    dist = sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));


    if (((R + r) > dist) && (R < dist)) { printf_s("���������� ����������� \n the circles intersect \n"); }
    if (dist > r + R) { printf_s("������� �� ����������� �� ����� ������ ������, �� ��������, �� ������������ \n none of the circles lies inside the other, do not touch, do not intersect \n"); }
    if (R == dist + r) { printf_s("���������� ������� \n inner touch \n"); }
    if (R + r == dist) { printf_s("������� ������� \n external touch \n"); }
    if ((dist + r < R) && (R > dist)) { printf_s("���� ���������� ����� � ������ \n one circle lies in the other \n"); }




    system("pause");
}
*/



#include <stdio.h>
#include <math.h>

int main()
{
   
    int h, w, d;

    do {
        printf_s("Parametri shkafa \n");
        scanf_s("%i %i %i", &h, &w, &d);
    } while (!((180 <= h) && (h <= 220)) || !((80 <= w) && (w <= 120)) || !((50 <= d) && (d <= 90)));


    int pl_dvp = 950;
    int pl_dsp = 750;
    int pl_dereva = 700;


    double zadnya_stenka = (h * w * 0.5) / 100 / 100 / 100 * pl_dvp;
    double bokovina_1 = (h * d * 1.5) / 100 / 100 / 100 * pl_dsp;
    double krishki_1 = (w * d * 1.5) / 100 / 100 / 100 * pl_dsp;
    double dveri = (h * w * 1.0) / 100 / 100 / 100 * pl_dereva;
    double polki_mnogo = (d * (w - 2 * 1.5) * 1.5) / 100 / 100 / 100 * pl_dsp;
    // (w - 2 * 1.5) ���� ��������� ������� ������� ������ (��� ���������� �� ���������)


    // kolvo polok
    int kolvo_polok = h / 40.15;
    // h * w *1 == 0 ���� ���������� � double


    double m = zadnya_stenka + bokovina_1 * 2 + krishki_1 * 2 + dveri + polki_mnogo * kolvo_polok;
    printf_s("%lg Kg", m);


}


