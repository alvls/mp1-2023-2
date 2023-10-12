#define _CRT_SECURE_NO_WARNINGS
//#define SIZE 2
#include <stdio.h>
#include <locale.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include < string.h > 

void game1();
void game2();

void main()
{	
	int k; //����� ������ ����
	setlocale(LC_ALL, "rus");
	printf("����� ���������� � ��������� \"������ �����\"\n� ����� ����� ���� �� ������ ������� ?\n������� 1, ���� � ������, ��� 2, ���� �� ������ ");
	scanf("%d", &k);
	switch (k) {
	case 1:
		game1();
		break;
	case 2:
		game2();
		break;
	default:
		do {
			printf("����������, ������� 1 ��� 2 ");
			scanf("%d", &k);
		} while ((k != 1) && (k != 2));
		switch (k) {
		case 1:
			game1();
			break;
		case 2:
			game2();
			break;
		}
	}
	system("pause");
}
void game1() {
	srand(time(0));
	int num = (rand() % 999) + 1; //���������� ���������� �����
	int s; //������������ ������������� �����
	int count = 0; //���������� �������
	printf("�������� �������, ����� ����� �� ��������� �� 1 �� 999 ������������: ");
	scanf("%d", &s);
	while (!(0 < s && s < 1000)) {
		printf("�� ����� ����� �� �� ��������� �� 1 �� 999 ������������, ������� ��� ���: ");
		scanf("%d", &s);
	}
	count++;
	while (s != num)
		if (s > num)
		{
			printf("�������� ����� ������ �����������\n����������� ��� ���: ");
			scanf("%d", &s);
			count++;
		}
		else if (s < num)
		{
			printf("�������� ����� ������ �����������\n����������� ��� ���: ");
			scanf("%d", &s);
			count++;
		}
	printf("�������! ���������� ����������� �������: %d ", count);
}
void game2() {
	int s; //������������ ���������� �����
	srand(time(NULL));
	int num; //������� ���������
	char c; //������� �������� �������������
	int count = 0; //���������� �������
	int vg = 1000; // ������� �������
	int ng = 0; //������ �������
	printf("������� ����� �� ��������� �� 1 �� 999 ������������, ������� ������ �������� ���������: ");
	scanf("%d", &s);
	while (!(0 < s && s < 1000)) {
		printf("�� ����������� ����� ����������� ���������� �����, ������� ��� ���: ");
		scanf("%d", &s);
	}
	printf("��������� ����� ����������� �������,\n���� ���������� ����� ������ ������� ���������, ������ \">\",\n���� ������ - \"<\", ���� ����� - \"=\"\n");
	do {
		num = (rand()) % (vg - ng - 1) + ng + 1;
		int �;
		while ((� = getchar()) != '\n' && � != EOF) {}
		printf("���������� ����� ����� %d?\n������� ����� �� �������: ", num);
		scanf_s("%c", &c);
		while ((c != '>') && (c != '<') && (c != '=')) {
			while ((� = getchar()) != '\n' && � != EOF) {}
			printf("�� ����������� ����� ����� �� �������, ������� ��� ��� \">\", \"<\" ��� \"=\": ");
			scanf("%c", &c);
		}
		count++;
		if (c == '>')
		{
			ng = num;
		}
		else if (c == '<')
		{
			vg = num;
		}
	} while (c != '=');
	printf("��������� ������� �����, ������ ���������� ������� ����� %d ", count);
}