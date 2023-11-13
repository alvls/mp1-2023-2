#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
struct shop { //������������, ��������� �� ������� ������, ������
	char name[100];
	int price;
	double discount;
};
void main() {
	struct shop product[] = {{"������,1�", 70, 0.15}, {"���, 500�", 120, 0.2}, {"������ ��� \"������� ���������\"", 100, 0.1}};
	int c2354 = 0, c3576 = 0, c8903 = 0;
	setlocale(LC_ALL, "rus");
	int action;
	int barcode[5] = { -1, -1, -1, -1 };
	int number;
	int total_cost = 0;
	double total_disc = 0;
	printf("����� ���������� � ��������� ������������ �����\n��� ��� �������� ��������� ��������:\n1. ������������� �����\n2. ������� �������� ���������������� ������\n3. �������� ������ � ������ � ���\n4. ������������ ��� �� �������\n5. ���������� �������� ����� � ������\n6. ������� �����, - ��� ������ ������ �� ���� �������� ��������� �����, ������� ��� �������������");
	scanf("%d", &action);
	while (!(1 <= action && action <= 6)) {
		printf("������������ ����, ������� ����� � ���������� �� 1 �� 6 ������������: ");
		int �;
		scanf("%d", &action);
		while ((� = getchar()) != '\n' && � != EOF) {}
	}
	while (action != 6) {
		if (action == 1) {
			printf("��������� ������ ��������� ��������. ������� 4 �����, ���������� ��������: ");
			for (int i = 0; i < 4; i++) {
				int �;
				scanf("%d", &barcode[i]);
				while (!(0 <= barcode[i] && barcode[i] <= 9)) {
					printf("������������ ����, ������� ����� � ���������� �� 0 �� 9 ������������: ");
					scanf("%d", &barcode[i]);
					while ((� = getchar()) != '\n' && � != EOF) {}
				}
			}
			number = barcode[0] * 1000 + barcode[1] * 100 + barcode[2] * 10 + barcode[3];
			if (number == 2354) {
				printf("�������� ������������");
			}
			else if (number == 3576) {
				printf("�������� ������������");
			}
			else if (number == 8903) {
				printf("�������� ������������");
			}
			else {
				printf("����� � ����� ���������� �����������");
				barcode[0] = -1;
			}
		}
		if (action == 2) {
			if (barcode[0] == -1) {
				printf("������� �� ������ ������������� �����");
			}
			else if (number == 2354) {
				printf("%s, ���������: %d ���, ������: %.0lf%%", product[0].name, product[0].price, product[0].discount * 100);
			}
			else if (number == 3576) {
				printf("%s, ���������: %d ���, ������: %.0lf%%", product[1].name, product[1].price, product[1].discount * 100);
			}
			else if (number == 8903) {
				printf("%s, ���������: %d ���, ������: %.0lf%%", product[2].name, product[2].price, product[2].discount * 100);
			}
		}
		if (action == 3) {
			if (barcode[0] == -1) {
				printf("������� �� ������ ������������� �����");
			}
			else if (number == 2354) {
				c2354++;
				printf("����� �������� � ���");
				total_cost += product[0].price;
				total_disc += product[0].price * product[0].discount;
			}
			else if (number == 3576) {
				c3576++;
				printf("����� �������� � ���");
				total_cost += product[1].price;
				total_disc += product[1].price * product[1].discount;
			}
			else if (number == 8903) {
				c8903++;
				printf("����� �������� � ���");
				total_cost += product[2].price;
				total_disc += product[2].price * product[2].discount;

			}
		}
		if (action == 4) {
			if (total_cost != 0) {
				printf("��� ���:");
				if (c2354 != 0) {
					printf("%s, ��������� �� �������: %d, ����������: %d,\n����� ��������� �� �����: %lf\n", product[0].name, product[0].price, c2354, (double)c2354 * ((double)product[0].price - (double)product[0].price * product[0].discount));
				}
				if (c3576 != 0) {
					printf("%s, ��������� �� �������: %d, ����������: %d,\n����� ��������� �� �����: %lf\n", product[1].name, product[1].price, c3576, (double)c3576 * ((double)product[1].price - (double)product[1].price * product[1].discount));
				}
				if (c8903 != 0) {
					printf("%s, ��������� �� �������: %d, ����������: %d,\n����� ��������� �� �����: %lf\n", product[2].name, product[2].price, c8903, (double)c8903 * ((double)product[2].price - (double)product[2].price * product[2].discount));
				}
				printf("����� ��������� ������� � �������: %d, C�������� ������: %lf, �������� ����� � ������: %lf", total_cost, total_disc, (double)total_cost - total_disc);
			}
			else {
				printf("��� �� ����� ���� �����������, ��� ��� ����������� ������");
			}

		}
		if (action == 5)
			if (total_cost != 0)
				printf("�������� ����� � ������: %.1lf", (float)total_cost - total_disc);
			else
				printf("�� ��� �� �������� �� ������ ������");
		printf("\n");
		scanf("%d", &action);
		while (!(1 <= action && action <= 6)) {
			printf("������������ ����, ������� ����� � ���������� �� 1 �� 6 ������������: ");
			int �;
			scanf("%d", &action);
			while ((� = getchar()) != '\n' && � != EOF) {}
		}
	}
	printf("�� ��������, �������� ��� ���!\n�������, ��� ������������ ���� �����!");
}