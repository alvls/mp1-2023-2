#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int cows(int* loc_mas, int* loc_guess, int len) {
	int res = 0;
	for (int it = 0; it < len; it++) {
		int el1 = loc_mas[it];
		for (int jt = 0; jt < len; jt++) {
			int el2 = loc_guess[jt];
			if (el2 == el1 && jt != it) {
				res++;
			}
		}
	}
	return res;
}

int bulls(int* loc_mas, int* loc_guess, int len) {
	int res = 0;
	for (int it = 0; it < len; it++)
		if (loc_mas[it] == loc_guess[it])
			res++;
	return res;
}

int main() { // outputs are in english because of "кодировка" problem.
	int n = 0;
	char pus = 'g';
	while (n < 2 || n > 5) {
		printf("Enter the number's length (from 2 to 5): ");
		scanf_s("%d", &n);
		if (pus = getchar() != '\n') {
			n = 6;
			while (pus = getchar() != '\n') {}
		}
	}

	srand(time(NULL));
	int mas[5] = { 0 };
	int check[10] = { 0 };
	int c = 0;

	while (c < n) { // number generation
		int el = rand() % 10;
		while (check[el] == 1 || (el == c && c == 0)) {
			el = rand() % 10;
		}
		check[el] = 1;
		mas[c] = el;
		c++;
	}
	/*
	for (int i = 0; i < n; i++) {
		printf("%d", mas[i]);
	}
	printf("\n");
	*/
	int* ans = malloc(n * sizeof(int));
	for (int i = 0; i < n; i++) {
		ans[i] = mas[i];
	}
	int surrender = 0;
	while (!surrender) {
		printf("\nEnter Your guess: ");
		int* guess = malloc(n * sizeof(int));
		int very_fine = 0; // flag for unique figures in number
		while (!very_fine) {
			very_fine = 1;
			int fine = 0; // flag for correct input
			while (!fine) {
				for (int i = 0; i < n; i++) { // clean "guess"
					guess[i] = 0;
				}
				char ch;
				int cou = 0;
				while (cou <= n) {
					ch = getchar();

					if (ch == '\n') {
						if (cou == n) {
							fine = 1;
							break;
						}
						else {
							break;
						}
					}
					guess[cou] = ch - '0';
					cou++;
				}
				if (!fine) {
					printf("Enter number of length %d: ", n);
					if (cou > n)
						while ((ch = getchar()) != '\n' && ch != EOF) {}
				}

			}
			for (int i = 0; i < n - 1; i++) {
				for (int j = i + 1; j < n; j++) {
					if (guess[i] == guess[j])
						very_fine = 0;
				}
			}
			if (!very_fine) {
				printf("Enter a number of length %d with non-repeating digits: ", n);
			}
		}

		printf("Number of cows: %d\n", cows(mas, guess, n));
		printf("Number of bulls: %d\n", bulls(mas, guess, n));
		if (bulls(mas, guess, n) == n) {
			printf("You've won!\n");
			break;
		}
		char c = '2';
		while (c != 'y' && c != 'n') {
			printf("Would you like to continue? [y/n]: ");
			scanf_s("%c", &c);
			while ((pus = getchar()) != '\n' && pus != EOF) {}
		}
		if (c == 'n') {
			printf("Are you sure you want to surrender? [y/n]: ");
			scanf_s("%c", &c);
			while (c != 'y' && c != 'n') {
				printf("Would you like to continue? [y/n]: ");
				scanf_s("%c", &c);
				while ((pus = getchar()) != '\n' && pus != EOF) {}
			}
			if (c == 'y')
				surrender = 1;
			else {
				pus = getchar();
			}
		}
	}
	system("pause");
	return 0;
}