#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <locale.h>
#include <time.h>
#include <stdlib.h>

int main() {

	setlocale(LC_ALL, "rus");
	int num[5] = { 0 };
	int g[] = { 0 };
	int len, guess, bulls = 0, cows = 0;
	
	printf("Какой длины должно быть число? (от 2 до 5)\n");
	
	scanf("%d", &len);
	

	srand(time(NULL));
	if (len == 4 || len == 5) {
		do
		{
			num[0] = 1 + rand() % 9;

			for (int i = 1; i < len; i++) {
				num[i] = rand() % 10;
			}
		} while (num[0] == num[1] || num[0] == num[2] || num[0] == num[3] ||
			num[0] == num[4] || num[1] == num[2] || num[1] == num[3] ||
			num[1] == num[4] || num[2] == num[3] || num[2] == num[4] ||
			num[3] == num[4]);
	}
	else if (len == 2){
		do
		{
			num[0] = 1 + rand() % 9;
			num[1] = rand() % 10;
			
		} while (num[0] == num[1]);
	}
	else if (len == 3) {
		do
		{
			num[0] = 1 + rand() % 9;
			num[1] = rand() % 10;
			num[2] = rand() % 10;


		} while (num[0] == num[1] || num[0] == num[2] || num[1] == num[2]);
	}
	else {
		printf("Неверное число");
	}
	
	//the number has been got
	
	do
	{
		printf("\nПостарайтесь угадать число из %d цифр\n", len);
		scanf("%d", &guess);

		cows = 0;
		bulls = 0;

		for (int i = len - 1; i > -1; i--) {

			g[i] = guess % 10;
			guess /= 10;
		}

		for (int i = 0; i < len; i++) {

			if (g[i] == num[i]) {
				bulls++;
			}

			for (int j = 0; j < len; j++) {

				if (g[i] == num[j]) {
					cows++;
				}
			}
		}

		printf("Коров: %d\n", cows);
		printf("Быков: %d\n", bulls);

	} while (bulls != len);
	printf("Молодец, отгадал!");

	system("pause");
}
