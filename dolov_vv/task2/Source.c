#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <locale.h>
#include <time.h>

int res_1()
{
	int a=0;//�������� ������������� �����
	int count = 0;
	srand(time(0));
	int rand_ch = rand() % 1000;
	printf("���� ��������, �������� ����� �� 1 �� 1000 \n");
	while (1)
	{
		printf("������� �����\n");
		scanf("%d", &a);
		if (a < rand_ch)
		{
			printf("���������� ����� ������ \n");
			count += 1;
		}
		else if (a > rand_ch)
		{
			printf("���������� ����� ������ \n");
			count += 1;
		}
		else
		{
			printf("������� \n");
			count += 1;
			printf("����� ����� �������  %d \n", count);
			system("pause");
			break;
		}
	}

}

int res_2()
{
	int a = 0;
	int count = 0;
	char zn;
	printf("������� ���� > ���� ���� ����� ������ ����� \n");
	printf("������� ���� < ���� ���� ����� ������ ����� \n");
	printf("������� ���� = ���� � ������� ���� ����� \n");
	printf("����������� ����� \n");
	scanf("%d", &a);
	srand(time(0));
	int rand_ch1 = rand() % 1000;
	int mx_gr = 1000;
	int mn_gr = 0;
	int cash;
	while (1)
	{
		printf("��� ����� %d\n", rand_ch1);
		cash = rand_ch1;
		printf("������� ���� > ��� < ��� = : \n");
		scanf(" %c", &zn);
		if (zn == '>')
		{
			rand_ch1 = rand() % (mx_gr - rand_ch1-1) + rand_ch1 + 1;
			mn_gr = cash;
			count += 1;
		}
		else if (zn == '<')
		{
			rand_ch1 = rand() % (rand_ch1 - mn_gr-1) + mn_gr + 1;
			mx_gr = cash;
			count += 1;
		}
		else if (zn == '=')
		{
			printf("� ������� \n");
			count += 1;
			printf("����� ���� �������  %d \n", count);
			system("pause");
			break;
		}
	}
}




int main()
{
	setlocale(LC_ALL, "rus");
	printf("������� ������� � ����) \n");
	int ch_res;
	int flag = 0;

	do
	{
		printf("������� ����� 1 ���� ������ ������� � ������ ����� \n");
		printf("������� ����� 2 ���� ������ ������� �� ������ ����� \n");
		scanf("%d", &ch_res);
		if (ch_res==1)
		{
			flag = 0;
			res_1();
		}
		else if (ch_res == 2)
		{
			flag = 0;
			res_2();
		}
		else
		{
			printf("������� ����������� �����, ������� 1 ��� 2 \n");
			system("pause");
			flag = 1;
		}
	} while (flag == 1);
}