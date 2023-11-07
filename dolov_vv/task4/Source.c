#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <locale.h>
#include <time.h>
#include <time.h>

struct product
{
	char strih[4];
	char name[30];
	int cost;
	int count;
	int discount;
};

void main()
{
	setlocale(LC_ALL, "rus");
	srand(time(NULL));
	
	struct product pr[10];

	strcpy(pr[0].strih, "1234");
	strcpy(pr[0].name, "����������� ���� � �������");
	pr[0].cost = 42;
	pr[0].discount =  5 * (rand() % 10 + 1);
	
	strcpy(pr[1].strih, "1207");
	strcpy(pr[1].name, "������������ �����");
	pr[1].cost = 112;
	pr[1].discount = 5 * (rand() % 10 + 1);

	strcpy(pr[2].strih, "3007");
	strcpy(pr[2].name, "����� �������� � ���������");
	pr[2].cost = 119;
	pr[2].discount = 5 * (rand() % 10 + 1);

	strcpy(pr[3].strih, "4625");
	strcpy(pr[3].name, "������� � �����");
	pr[3].cost = 28;
	pr[3].discount = 5 * (rand() % 10 + 1);

	strcpy(pr[4].strih, "9999");
	strcpy(pr[4].name, "������ ��������");
	pr[4].cost = 51;
	pr[4].discount = 5 * (rand() % 10 + 1);

	strcpy(pr[5].strih, "2678");
	strcpy(pr[5].name, "����� �����");
	pr[5].cost = 65;
	pr[5].discount = 5 * (rand() % 10 + 1);

	strcpy(pr[6].strih, "5858");
	strcpy(pr[6].name, "���� ���������");
	pr[6].cost = 38;
	pr[6].discount = 5 * (rand() % 10 + 1);

	strcpy(pr[7].strih, "3021");
	strcpy(pr[7].name, "������ ��������");
	pr[7].cost = 49;
	pr[7].discount = 5 * (rand() % 10 + 1);

	strcpy(pr[8].strih, "8057");
	strcpy(pr[8].name, "�������� ����");
	pr[8].cost = 15;
	pr[8].discount = 5 * (rand() % 10 + 1);

	strcpy(pr[9].strih, "7741");
	strcpy(pr[9].name, "������ ���������");
	pr[9].cost = 75;
	pr[9].discount = 5 * (rand() % 10 + 1);

	char strihcode[4];
	int fl1;
	int fl2;
	int end;
	char count[10] = {0};
	float total_discount = 0;
	int cost_of_goods = 0;

	printf("������������, ���� ������ ��� � ����� ��������!\n");
	printf("������ � ��� ����� ������� ������ � ����� ������������ �����.\n");
	printf("������� �� ���������� �������� ������� ��������� ������������ ��������� ��������)\n");
	printf("\n");
	printf("��������� ��� ������� ��������\n");
	printf("1234 - ����������� ���� � �������\n");
	printf("1207 - ������������ �����\n");
	printf("3007 - ����� �������� � ���������\n");
	printf("4625 - ������� � �����\n");
	printf("9999 - ������ ��������\n");
	printf("2678 - ����� �����\n");
	printf("5858 - ���� ���������\n");
	printf("3021 - ������ ��������\n");
	printf("8057 - �������� ����\n");
	printf("7741 - ������ ���������\n");
	printf("\n");
	while (1) {
		printf("������� ���������� �������� ������ \n");
		for (int i = 0; i < 4; i++) {
			scanf_s(" %c", &strihcode[i]);
		}
		fl1 = -1;
		for (int i = 0; i < 10; i++) {
			fl2 = 1;
			for (int j = 0; j < 4; j++) {
				if (pr[i].strih[j]!= strihcode[j]) {
					fl2 = 0;
					break;
				}
			}
			if (fl2 == 1)
				fl1 = i;
		}
		if (fl1 == -1) {
			printf("����� �� ���������, ��������� ����������� ���������!\n");
		}
		else {
			printf("������������: %s, ��������� �� �����: %d ���., ������: %d%% \n", pr[fl1].name, pr[fl1].cost, pr[fl1].discount);
			count[fl1]++;

			total_discount = total_discount + pr[fl1].cost * pr[fl1].discount * 0.01;
			cost_of_goods = cost_of_goods + pr[fl1].cost;
			printf("���� �� ������� ��� ������,������� ������, ������� 1, ����� ������� ������ ����� \n");
			scanf_s("%d", &end);
			if (end == 1) {
				break;
			}
		}
	}
	printf("\n");
	printf("���������, ��� �����������...\n");
	printf("\n");
	printf("					!���!\n");
	for (int i = 0; i < 10; i++) {
		if (count[i] != 0)
			printf("������������ ������: %s, ��������� �� ������� ������: %d ���., ���������: %d, ����� ���������: %d ���.\n", pr[i].name, pr[i].cost, count[i], pr[i].cost*count[i] - (int)(pr[i].cost*count[i] * pr[i].discount * 0.01));
	}
	printf("����� ��������� ������� - %d ���.\n", cost_of_goods);
	printf("����� ������ - %d ���.\n", (int)total_discount);
	printf("�������� ����� � ������ - %d ���.\n", cost_of_goods - ((int)total_discount));
	system("pause");
}
