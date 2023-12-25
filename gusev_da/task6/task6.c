#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

#include "func.h"


void menu_mode_1();
void menu_mode_2();
double get_value(double x, int choice);
double calc_est(double x, int choice, int count);

double (*taylor_func[4])(double, int, int, int*) =
{
    taylor_exp,
    taylor_sin,
    taylor_cos,
    taylor_arcsin,
};

double (*�ur_func[4])(double) =
{
    exp,
    sin,
    cos,
    asin,
};

int main()
{
    setlocale(LC_ALL, "Rus");
    int choice, flag = 1;

    while (flag == 1)
    {
        printf("������!\n��� ��������� ��������� ��������� ������ �������� ��� ���������� ������ ������� \n� �������� ����� � �������� ������������ �� ���� ���������� ���� ������� � ��� �������.\n������ ����� ������ ���������:\n");
        printf("1) ����������� ������ ������� � �������� �����\n2) �������� �����������\n3) ��������� ���������\n>>> ");
        if (scanf("%d", &choice) != 1)
        {
            while (getwchar() != "\n");
            continue;
        }

        switch (choice)
        {
        case 1:
            menu_mode_1();
            flag = 0;
            break;
        case 2:
            menu_mode_2();
            flag = 0;
            break;
        case 3:
            return;
        default:
            system("cls");
            break;
        }
    }
    return 0;
}

void menu_mode_1()
{
    int mode, accuracy, N, count, flag = 1;;
    double x, result, result_cur, diff;

    system("cls");
    printf("�������� �������:\n1) ����� - sin(x)\n2) ������� - cos(x)\n3) ���������� - exp(x)\n4) �������� - arcsin(x)\n5) ����� � ����\n>>> ");
    if (scanf("%d", &mode) != 1 || mode < 1 || mode > 5)
    {
        printf("������ �����. ���������� ��� ���.\n");
        return;
    }
    system("cls");
    printf("������� ����� x, � ������� ���������� ��������� ��������: \n");
    if (scanf("%lf", &x) != 1)
    {
        printf("������ �����. ���������� ��� ���.\n");
        return;
    }
    printf(L"������� ������ �������� (���-�� ������ ����� �������)\n");
    if (scanf("%d", &accuracy) != 1 || accuracy < 0)
    {
        printf("������ �����. ���������� ��� ���.\n");
        return;
    }
    printf("������� ������������ ���������� ������ ����\n");
    if (scanf("%d", &N) != 1 || N <= 0)
    {
        printf("������ �����. ���������� ��� ���.\n");
        return;
    }
    if (mode == 2 || mode == 3)
    {
        result = taylor_func[mode - 1](x + 1, accuracy, N, &count);
        result_cur = �ur_func[mode - 1](x + 1);
    }
    else
    {
        result = taylor_func[mode - 1](x, accuracy, N, &count);
        result_cur = �ur_func[mode - 1](x);
    }
    diff = fabs(result - result_cur);
    system("cls");
    printf("��������� ��������: %lf\n������ �������� �������: %lf\n������� ����� ������� � ��������� ���������: %lf\n���������� ����������� ���������: %d\n", result_cur, result, diff, count);
    system("pause");
}

void menu_mode_2()
{
    int mode, count, terms;
    double x, est, refer_value;

    system("cls");
    printf("�������� �������:\n1) ����� - sin(x)\n2) ������� - cos(x)\n3) ���������� - exp(x)\n4) �������� - arcsin(x)\n5) ����� � ����\n>>> ");
    if (scanf("%d", &mode) != 1 || mode < 1 || mode > 5)
    {
        printf("������ �����. ���������� ��� ���.\n");
        return;
    }
    system("cls");
    printf("������� ����� x, � ������� ���������� ��������� ��������: \n");
    scanf("%lf", &x);
    printf("������� ����� ������������� (�� 1 �� 25):\n");
    if (scanf("%d", &count) != 1 || count < 1 || count > 25)
    {
        printf("������ �����. ���������� ��� ���.\n");
        return;
    }
    system("cls");
    if (mode == 2 || mode == 3)
    {
        refer_value = get_value(x + 1, mode);
    }
    else
    {
        refer_value = get_value(x, mode);
    }
    printf("��������� ��������: %lf\n������ ��������   ������� \n", refer_value);
    for (int i = 1; i <= count; ++i)
    {
        if (mode == 2 || mode == 3)
        {
            est = taylor_func[mode - 1](x + 1, 10000, i, &terms);
        }
        else
        {
            est = taylor_func[mode - 1](x, 10000, i, &terms);
        }
        double difference = fabs(est - refer_value);
        printf("%-16lf  %-8lf \n", est, difference);
    }
    system("pause");
}

double get_value(double x, int choice)
{
    return �ur_func[choice - 1](x);
}
