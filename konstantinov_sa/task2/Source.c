#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<locale.h>
#include<time.h>

int main() {
	setlocale(LC_ALL, "");
	srand(time(NULL));

	printf("Игра: угадай число от 1 до 999\nВведите номер одного из режимов:\n1) Вы угадываете загаданное компьютером число\n2) Вы загадываете число, подсказывая компьютеру с помощью символов < > =\n  (Компьютер угадывает по эффективному алгоритму)\n3)Бонусный режим: второй режим, но в алгоритм угадывания добавлена случайность\n\nРежим: ");
	int mode = -1;
	while (mode > 3 || mode < 0)
		scanf("%d", &mode);

	if (mode == 1) {
		int tries = 0;
		int r = (int)(rand() * 998.0f / RAND_MAX + 1.0f);
		printf("Угадывайте\n");
		int g = -1;
		while (g != r) {
			if (scanf("%d", &g)) {

				tries += 1;
				if (g > r)
					printf("< Загадонное число меньше\n");
				else if (g < r)
					printf("> Загадонное число больше\n");
			}
			else {

				while (getchar() != '\n');
			}
		}
		printf("Вы угадали, затратив %d попыток\n", tries);
	}

	else if (mode == 2 || mode == 3) {
		int tries = 0;
		printf("Введите загаданное число (от 1 до 999)\n");
		int u = -1;
		while (!(u > 0 && u < 1000))
			if (!scanf("%d", &u))
				while (getchar() != '\n');

		int g = 500;
		if (mode == 3)
			g += rand() % 500 - 250;
		int l = 0;
		int r = 1000;
		char a = 'a';
		int flag = 0;

		while (a != '=') {

			tries += 1;
			//printf("%d   l %d   r%d", g, l, r);
			printf("%d ", g); //ПОПЫТКА УГАДАТЬ

			if (flag == 1) {
				printf(">:| ");
				tries -= 1;
			}
			if (g == u)
			{
				printf("!");
				flag = 1;
			}
			else {
				printf("?");
			}
			printf("\n");

			scanf("\n%c", &a);              //ВВОД
			if (a == '<') {
				r = g;
				g = (int)((l + r) / 2.0f);
			}
			else if (a == '>') {
				l = g;
				g = (int)((l + r) / 2.0f);
			}
			else if (a != '=') {
				printf("Не распознан %c под номером %u\n", a, a);
				tries -= 1;
			}
			if (mode == 3 && (r - l > 4)) {
				int dia = r - l - 2;
				int mistake = rand() % dia;
				//printf("m %d (%d %d)\n", mistake - dia / 2, g - dia /2, g+ dia /2);
				g += mistake - dia / 2;

			}


		}
		if (!flag) {
			printf("Не ");
		}
		printf("угадано за %d попыток\n", tries);
	}

	system("pause");
}