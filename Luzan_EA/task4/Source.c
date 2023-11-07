#include <stdio.h>
#include <string.h>
#include <locale.h>
#include <stdlib.h>
#include <time.h>

#define N 5

int main() {
	setlocale(LC_ALL, "rus");
	srand(time(NULL));

	char barcodes[N][5] = { "0120\0", "0200\0", "0300\0", "0400\0", "0500\0" };
	char product_names[N][50] = { "Skimmed Milk ", "Ural Bread", "Real Kefir", "Yellow Cheese", "Butter"};
	int product_costs[N] = { 1, 2, 3, 4, 5 };
	float product_disc[N] = { 0.1, 0.1, 0.1, 0.1, 0.1};
	int product_num[N] = { 0 };
	for (int i = 0; i < N; i++) {
		product_costs[i] = 100 + (rand() % 400);
		product_disc[i] = (float)(rand() % 11) * 0.05f;
	}
	int sum = 0; // ����� ����� �� ������
	float disc_sum = 0; // ����� ������
	int end_sum = 0; // ����� � ������ ������
	char inp_barcode[5] = "0000\0";
	int correct_barcode = 1; // �������� ������������ ���������
	int pos = -1; // ����� ������
	
	do {
		correct_barcode = 1;
		printf_s("Enter/Scan barcode\n");
		printf_s("If you want to get the cheque, enter 0000\n");

		//entering barcode
		for (int i = 0; i < 5 - 1; i++) {  
			inp_barcode[i] = getchar();
			if (inp_barcode[i] == '\n') {
				printf_s("Barcode must be 4-digit length\n");
				correct_barcode = 0;
				break;
			}
		}
		if (correct_barcode == 0) { 
			continue; 
		}
		else {
			if (getchar() != '\n') {
				printf_s("Barcode must be 4-digit length\n");
				correct_barcode = 0;
				while (getchar() != '\n') { ; }
				continue;
			}
		}
		inp_barcode[4] = '\0';
		if (strcmp("0000\0", inp_barcode) == 0) { continue; }

		//searching for product
		pos = -1;
		for (int i = 0; i < N; i++) {
			if (strcmp(inp_barcode, barcodes[i]) == 0) {
				pos = i;
			}
		}
		if (pos == -1) {
			printf_s("There is no one product with such barcode. Please try again...\n");
			continue;
		}

		//info about product
		printf_s("\n");
		printf_s("%s\n", product_names[pos]);
		printf_s("barcode - %s, cost - %i rub, discount -  %g%%\n", barcodes[pos], product_costs[pos], product_disc[pos] * 100);
		printf_s("summary cost - %g rub\n", product_costs[pos] * (1 - product_disc[pos]));
		printf_s("\n");

		product_num[pos]++; // number of this product in cheque
	} while ( strcmp( inp_barcode, "0000\0") != 0);


	// cheque
	printf_s("Your cheque:");
	printf_s("\n");
	for (int i = 0; i < N; i++) {
		if (product_num[i] == 0) { continue; }
		printf_s("   %s\n", product_names[i]);
		printf_s("     cost - % i rub, nums - % i \n", product_costs[i], product_num[i]);
		printf_s("     summary cost - %g rub\n", product_num[i] * product_costs[i] * (1 - product_disc[i]));
		printf_s("\n");

		sum += product_num[i] * product_costs[i];
		disc_sum = disc_sum + (float)product_num[i] * (float)product_costs[i] * product_disc[i];
	}
	end_sum = sum - (int)disc_sum; // rounding down, without kopecks

	printf_s("Sum for all: %i rub\n", sum);
	printf_s("Discount: %i rub\n", (int)disc_sum);
	printf_s("To payment: %i rub\n", (int)end_sum);

	system("pause");
	return 0;
}