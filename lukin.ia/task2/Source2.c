#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <locale.h>

int main()
{
	setlocale(LC_ALL, "rus");
	int vybor_r, chislo, ch1, ch1p, itog, att, ch2, ot, doo;
	char ocenka;
	printf("�������� �����:\n1 - ��������� ����� 1-999\n2 - �������� ����� 1-999\n");
	scanf("%i", &vybor_r);
	att = 0;
	itog = 0;
	if (vybor_r == 1)//����� �����������
	{
		srand(time(NULL));
		ch1 = (1 + rand() % (1000));
		do
		{
			att++;
			printf("���������� ������� �����\n");
			scanf("%i", &ch1p);
			if (ch1p == ch1)
			{
				printf("�� ��������!\n");
				itog = 1;
			}
			else if (ch1p < ch1)
			{
				printf("���� ����� ������ �����������, ���������� ���!\n");
				itog = 0;
			}
			else if (ch1p > ch1)
			{
				printf("���� ����� ������ �����������, ���������� ���!\n");
				itog = 0;
			}
		} while (itog != 1);
	}
	else if (vybor_r == 2)//����� �����������
	{
		ot = 1;
		doo = 999;
		printf("��������� ����� �� 1 �� 999, ��������� ���\n");
		do//��� ������ ������� att, �.� ���� ���� ������-�� ����������� ������ 
		{ 
			srand(time(NULL));
			ch2 = ot + rand() % (doo - ot);//�� ������������ �������� �� �������������
			printf("����� %i ������, ������ ��� ����� �����, ��� �� ��������?  ", ch2);//��� ��� ������ ������ ��������� �� ����� �� �������
			scanf("%c", &ocenka);
			if (ocenka == '=')
			{
				printf("��� ������ ���� �����\n");
				itog = 1;
				att++;
			}
			else if (ocenka == '>')
			{
				doo = ch2 - 1;//����� ���� ���������� ����� ������ �� ��������
				itog = 0;
				att++;
			}
			else if (ocenka == '<')//�� �� ����� ��� � 60
			{
				ot = ch2 + 1;
				itog = 0;
				att++;
			}
		} while (itog != 1);
	}
	printf("���������� �������: %i\n", att);
	system("pause");
}