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
	int sum = 0; // общая сумма за товары
	float disc_sum = 0; // сумма скидок
	int end_sum = 0; // сумма с учётом скидок
	char inp_barcode[5] = "0000\0";
	int correct_barcode = 1; // проверка корректности штрихкода
	int pos = -1; // номер товара
	
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
		printf_s(" cost - %i rub, discount -  %g%%\n", product_costs[pos], product_disc[pos] * 100);
		printf_s(" cost with disc. - %g rub\n", product_costs[pos] * (1 - product_disc[pos]));
		printf_s("\n");

		product_num[pos]++; // number of this product in cheque
	} while ( strcmp( inp_barcode, "0000\0") != 0);


	// cheque
	printf_s("\n\n\nYour cheque:\n\n");
	printf_s("Name  -  Price  -  discount  -  total cost\n");
	for (int i = 0; i < N; i++) {
		if (product_num[i] == 0) { continue; }
		printf_s("%s  -  %i rub/item  -  %i pcs  -   %g rub\n", product_names[i], product_costs[i], product_num[i], product_num[i] * product_costs[i] * (1 - product_disc[i]));
		//printf_s("     cost - %i rub, pcs - %i \n", product_costs[i], product_num[i]);
		//printf_s("     cost with disc. - %g rub\n", product_num[i] * product_costs[i] * (1 - product_disc[i]));
		//printf_s("\n");

		sum += product_num[i] * product_costs[i];
		disc_sum = disc_sum + (float)product_num[i] * (float)product_costs[i] * product_disc[i];
	}
	end_sum = sum - (int)disc_sum; // rounding down, without kopecks

	printf_s("\n\n");
	printf_s("Total cost of products: %i rub\n", sum);
	printf_s("Discount: %i rub\n", (int)disc_sum);
	printf_s("For payment: %i rub\n\n", (int)end_sum);

	system("pause");
	return 0;
}
/*
0500
0400
0000
*/