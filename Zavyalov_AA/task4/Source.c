#include <stdio.h>
#include <memory.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>

#define N 7

int check(char k) {
	return (0 <= k - '0' && k - '0' <= 9);
}

int main() {
	srand(time(NULL));

	char* names[N];
	for (int i = 0; i < N; i++) {
		names[i] = malloc(15 * sizeof(char));
	}
	names[0] = "Milk", names[1] = "White bread", names[2] = "Greenfield tea", names[3] = "Apple juice", names[4] = "Sugar", names[5] = "Cat food", names[6] = "Headphones";

	int cost[N] = { 60, 30, 200, 80, 60, 25, 4000};
	float discounts[N];
	for (int i = 0; i < N; i++) {
		discounts[i] = (rand() % 10 + 1) * 0.05;
	}

	char* barcode_to_index[N];
	for (int i = 0; i < N; i++) {
		barcode_to_index[i] = malloc(4 * sizeof(char));
	}
	barcode_to_index[0] = "0052", barcode_to_index[1] = "1337", barcode_to_index[2] = "2023", barcode_to_index[3] = "3024", barcode_to_index[4] = "8453", barcode_to_index[5] = "4096", barcode_to_index[6] = "8192";

	// receipt formation
	int quantity[N] = { 0 };
	char bar[] = "aaaa";
	int empty = 1;
	while (bar != "end" && bar != "End") {
		int fine = 0;
		while (!fine) {
			printf("Enter the barcode of the product: ");
			fine = 1;
			char ch;
			for (int i = 0; i < 4; i++) {
				bar[i] = getchar();
				if (bar[i] == '\n') {
					printf("The length of the barcode must be equal to 4!\n");
					fine = 0;
					break;
				}
			}
			if (!fine) continue;
			if ((ch = getchar()) != '\n' && ch != EOF) {
				printf("The length of the barcode must be equal to 4!\n");
				fine = 0;
				while ((ch = getchar()) != '\n' && ch != EOF);
				continue;
			}
			for (int i = 0; i < 4; i++) {
				if (!check(bar[i])) {
					fine = 0;
					printf("Characters in the barcode must be numbers from 0 to 9!\n");
					break;
				}
			}
		}

		int ind = -1;
		int found = 0;
		for (int i = 0; i < N; i++) {
			int eq = 1;
			for (int j = 0; j < 5; j++) {
				if (barcode_to_index[i][j] != bar[j]) {
					eq = 0;
				}
			}
			if (eq) {
				found = 1;
				ind = i;
				break;
			}
		}
		
		if (ind != -1) {
			printf("Product's barcode: %s, name of the product: %s, cost per unit: %i, discount: %g%%\n", barcode_to_index[ind], names[ind], cost[ind], discounts[ind] * 100);
			printf("-------------------------------------------------------------------------------------------\n");
			quantity[ind]++;
			empty = 0;
		}
		else {
			printf("There's no product matching this barcode.\n");
		}
		char cont = 'a', c = 'a';
		int check = 75;
		while ((cont != 'y' && cont != 'n' && cont != 'Y' && cont != 'N') || (check != 0)) {
			printf("Would you like to scan more barcodes? [y/n]: ");
			scanf_s("%c", &cont);
			check = 0;
			while (c = getchar() != '\n' && c != EOF) { check++; }
		}
		if (cont == 'n' || cont == 'N') {
			if (empty) {
				printf("The check cannot be empty! Enter at least 1 valid barcode.\n");
			}
			else break;
		}
	}

	// receipt output
	float ans = 0, totaldisc = 0;
	printf("\n\nHere's Your check:\n\n");
	for (int i = 0; i < N; i++) {
		if (quantity[i] != 0) {
			int teksum = quantity[i] * cost[i];
			printf("%s  -  %i rub/item  -  quantity: %i  -  total cost: %g (discount of %g rubles)\n", names[i], cost[i], quantity[i], ceil(teksum * (1 - discounts[i])), floor(teksum * discounts[i]));
			ans += teksum;
			totaldisc += floor(teksum * discounts[i]);
		}
	}
	printf("-------------------------------------------------------------------------------------------------------------\n");
	printf("Total cost (without discount): %g rub, total discount: %g rub, total cost (including discount): %g rub\n\n", ans, totaldisc, ans - totaldisc);
	system("pause");
	return 0;
}