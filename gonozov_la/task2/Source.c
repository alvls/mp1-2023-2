#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <locale.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

void main()
{	
	int k; //����� ������ ����
	setlocale(LC_ALL, "rus");
	printf("� ����� ����� ���� �� ������ �������?\n������� 1, ���� � ������, ��� 2, ���� �� ������ ");
	scanf("%d", &k);
	switch (k) {
	case 1:
		game1();
		break;
	case 2:
		game2();
		break;
	default:
		k = 0;
		do {
			printf("����������, ������� 1 ��� 2 ");
			scanf("%d", &k);
		} while ((k != 1) || (k != 2));
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
int game1() {
	printf("1");
}
int game2() {
	printf("2");
}