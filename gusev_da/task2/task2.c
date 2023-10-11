#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <time.h>

void main()
{
	setlocale(LC_ALL, "Rus");
	srand(time(0));

	int option; // ����� ������
	int answer; // ����� ������������ -- �����
	int correct; // ���������� �����
	int attemts; // ���-�� ������� ������� �����
	int sup; // �������
	int interval; // �������� ����������/���������� �����
	int chislo; // ������ ������� ������ ������� ����� (50/50)
	char new_ans; // ����� ������������ ������ -- <, > ��� =

	sup = 1000;
	chislo = interval = sup / 2;
	attemts = 1;
	correct = rand() % 999 + 1;

	printf("������! ��� ���� '������ �����'.\n"
		"� ���� ���� ��� ������.\n"
		"1) ��������� ���������� �����.\n"
		"2) �� ����������� �����.\n");
	do
	{
		printf("����� ����� ������, ��� ������ ����: ");
		scanf_s("%d", &option);
	} while (option > 2 || option < 1);
	if (option == 1) 
	{
		printf("��������� ������� ����� [1,1000). ����� ��������� �����: ");
		do 
		{
			scanf_s("%d", &answer);
			if (answer < 1 || answer > 999)
			{
				printf("��� ���������. �������� �����: ");
			}
			if (answer > correct && answer < 1000)
			{
				printf("���������� ����� ������. �������� �����: ");
				attemts += 1;
			}
			if (answer < correct && answer > 0)
			{
				printf("���������� ����� ������. �������� �����: ");
				attemts += 1;
			}
			if (answer == correct)
			{
				printf("������! ��� �������� ���������� ������� - %d\n", attemts);
			}
		} while (answer != correct);
	}
	else
	{
		do
		{
			printf("����� ����� [1,1000), � ��������� ��������� ��� �������: ");
			scanf_s("%d", &correct);
		} while (correct < 1 || correct > 999);
		printf("���������� ����� - %d ? ", chislo);
		do
		{
			scanf_s("%c", &new_ans);
			if (new_ans == 60)
			{
				printf("������ ���������� ����� ������.");
				attemts += 1;
				interval = interval / 2 + interval % 2;
				chislo -= interval;
				printf("���������� ����� - %d ? ", chislo);
			}
			if (new_ans == 62)
			{
				printf("������ ���������� ����� ������.");
				attemts += 1;
				interval = interval / 2 + interval % 2;
				chislo += interval;
				printf("���������� ����� - %d ? ", chislo);
			}
			if (new_ans == 61)
			{
				printf("������! ��� �������� ���������� ������� - %d\n", attemts);
			}
		} while (new_ans != 61);
	}
	system("pause");
}