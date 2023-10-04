#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <locale.h>
#include <math.h>


// ������������� � main 
void main1() {
	setlocale(LC_ALL, "rus");

	float x1, y1, r1;
	float x2, y2, r2;
	float delta_x, delta_y;
	float radius_sum;
	float distance;

	printf("������� ����� ������ ��� ���������� � ������ ������ ����������: ");
	scanf("%f %f %f", &x1, &y1, &r1);
	printf("������� ����� ������ ��� ���������� � ������ ������ ����������: ");
	scanf("%f %f %f", &x2, &y2, &r2);

	delta_x = x2 - x1;
	delta_y = y2 - y1;
	radius_sum = r1 + r2;
	distance = sqrt(delta_x * delta_x + delta_y * delta_y);

	if (x1 > x2) {
		printf("������ ���������� ����������� ������ ������\n");
	}
	else if (x1 < x2) {
		printf("������ ���������� ����������� ����� ������\n");
	}
	else {
		printf("���������� ��������� �� ����� ������������ ��� (���������� �� ����������� ���������)\n");
	}

	if (y1 > y2) {
		printf("������ ���������� ����������� ���� ������\n");
	}
	else if (y1 < y2) {
		printf("������ ���������� ����������� ���� ������\n");
	}
	else {
		printf("���������� ��������� �� ����� �������������� ��� (��������� �� ��������� ���������)\n");
	}

	if (distance > radius_sum) {
		printf("���������� �� ������������\n");
	}
	else if (distance == radius_sum) {
		printf("���������� �������� ���� ����� ������� �������\n");
	}
	else {
		printf("���������� ������������\n");
	}

	if (distance + r1 == r2) {
		printf("������ ���������� �������� ������ ���������� �������\n");
	}
	else if (distance + r1 < r2) {
		printf("������ ���������� ��������� ������ ������\n");
	}

	if (distance + r2 == r1) {
		printf("������ ���������� �������� ������ ���������� �������\n");
	}
	else if (distance + r2 < r1) {
		printf("������ ���������� ��������� ������ ������\n");
	}

	if (distance == 0 && r1 == r2) {
		printf("���������� ���������\n");
	}

	system("pause");
}