#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <time.h>
#define _CRT_SECURE_NO_WARNINGS

int main()
{
    setlocale(LC_ALL, "rus");

    char ch;
    int try = 1;
    int ans;
    int hidden;

    printf("���� <������ �����> \n");
    printf("�������� �����: \n");
    printf("   1. ��������� ���������� - �� ����������� \n");
    printf("   2. �� ����������� - ���������� ���������� \n");
    printf("��� �������� ������� ����� ������� \n");
    printf("������� ��� �����: ");

    ch = getchar();

    srand(time(0));
    int num = rand() % 1000;

    switch (ch)
    {
    case '1':
        printf("���������� ������� \n");
        do {
            scanf_s("%d", &ans);
            if (ans == num)
                printf("�������!!! ����� �������: %d \n", try);
            else
            {
                try += 1;
                if (ans < num)
                    printf("���������� ����� ������ \n");
                else
                    printf("���������� ����� ������ \n");
            }

        } while (ans != num);

        break;

    case '2':
        printf("��������� ��� �����: ");
        scanf_s("%d", &hidden);
        int n1 = 0;
        int n2 = 1001;
        char user;
        int x;
        x = (n1 + n2) / 2;
        printf("���� ����� - %d? \n", x);
        do {
            scanf_s("%c", &user);
            if (user == '=')
            {
                printf("��������� ������. ����� �������: %d \n", try);
                break;
            }
            else if (user == '<')
            {
                n2 = x;
                try += 1;
                x = (n1 + n2) / 2;
                printf("���� ����� - %d? \n", x);
            }
            else if (user == '>')
            {
                n1 = x;
                try += 1;
                x = (n1 + n2) / 2;
                printf("���� ����� - %d? \n", x);
            }
            else
                continue;
            
        } while (user != '=');

        break;

    default: printf("����� �� ������");
    }
    
    system("pause");
}

