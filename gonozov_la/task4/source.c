#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
struct p2354 { //наименование, стоимость за единицу товара, скидка
	char name[100];
	int price;
	double discount;
};
struct p3576 { //наименование, стоимость за единицу товара, скидка
	char name[100];
	int price;
	double discount;
};
struct p8903 { //наименование, стоимость за единицу товара, скидка
	char name[100];
	int price;
	double discount;
};
void main() {
	struct p2354 t2354 = { "Молоко,1л", 70, 0.15 }; int c2354 = 0;
	struct p3576 t3576 = { "Рис, 500г", 120, 0.2 }; int c3576 = 0;
	struct p8903 t8903 = { "Зелёный чай \"Счастье художника\"", 100, 0.1 }; int c8903 = 0;
	setlocale(LC_ALL, "rus");
	int action;
	int barcode[5] = { -1, -1, -1, -1 };
	int number;
	int total_cost = 0;
	double total_disc = 0;
	printf("Добро пожаловать в программу «Электронная касса»\nДля вас доступны следующие действия:\n1. «сканировать» товар\n2. вывести описание отсканированного товара\n3. добавить данные о товаре в чек\n4. сформировать чек за покупку\n5. рассчитать итоговую сумму к оплате\n6. закрыть кассу, - для выбора любого из этих действий нажимайте цифру, которая ему соответствует");
	scanf("%d", &action);
	while (!(1 <= action && action <= 6)) {
		printf("Некорректный ввод, введите число в промежутке от 1 до 6 включительно: ");
		int а;
		scanf("%d", &action);
		while ((а = getchar()) != '\n' && а != EOF) {}
	}
	while (action != 6) {
		if (action == 1) {
			printf("Программа готова принимать штрихкод. Введите 4 цифры, разделённые пробелом: ");
			for (int i = 0; i < 4; i++) {
				int а;
				scanf("%d", &barcode[i]);
				while (!(0 <= barcode[i] && barcode[i] <= 9)) {
					printf("Некорректный ввод, введите число в промежутке от 0 до 9 включительно: ");
					scanf("%d", &barcode[i]);
					while ((а = getchar()) != '\n' && а != EOF) {}
				}
			}
			number = barcode[0] * 1000 + barcode[1] * 100 + barcode[2] * 10 + barcode[3];
			if (number == 2354) {
				printf("Штрихкод отсканирован");
			}
			else if (number == 3576) {
				printf("Штрихкод отсканирован");
			}
			else if (number == 8903) {
				printf("Штрихкод отсканирован");
			}
			else {
				printf("Товар с таким штрихкодом отсутствует");
				barcode[0] = -1;
			}
		}
		if (action == 2) {
			if (barcode[0] == -1) {
				printf("Сначала вы должны отсканировать товар");
			}
			else if (number == 2354) {
				printf("%s, Стоимость: %d руб, Скидка: %.0lf%%", t2354.name, t2354.price, t2354.discount*100);
			}
			else if (number == 3576) {
				printf("%s, Стоимость: %d руб, Скидка: %.0lf%%", t3576.name, t3576.price, t3576.discount * 100);
			}
			else if (number == 8903) {
				printf("%s, Стоимость: %d руб, Скидка: %.0lf%%", t8903.name, t8903.price, t8903.discount * 100);
			}
		}
		if (action == 3) {
			if (barcode[0] == -1) {
				printf("Сначала вы должны отсканировать товар");
			}
			else if (number == 2354) {
				c2354++;
				printf("Товар добавлен в чек");
				total_cost += t2354.price;
				total_disc += t2354.price * t2354.discount;
			}
			else if (number == 3576) {
				c3576++;
				printf("Товар добавлен в чек");
				total_cost += t3576.price;
				total_disc += t3576.price * t3576.discount;
			}
			else if (number == 8903) {
				c8903++;
				printf("Товар добавлен в чек");
				total_cost += t8903.price;
				total_disc += t8903.price * t8903.discount;

			}
		}
		if (action == 4) {
			if (total_cost != 0) {
				printf("Ваш чек:");
				if (c2354 != 0) {
					printf("%s, Стоимость за единицу: %d, Количество: %d,\nОбщая стоимость за товар: %lf\n", t2354.name, t2354.price, c2354, (double)c2354 * ((double)t2354.price - (double)t2354.price * t2354.discount));
				}
				if (c3576 != 0) {
					printf("%s, Стоимость за единицу: %d, Количество: %d,\nОбщая стоимость за товар: %lf\n", t3576.name, t3576.price, c3576, (double)c3576 * ((double)t3576.price - (double)t3576.price * t3576.discount));
				}
				if (c8903 != 0) {
					printf("%s, Стоимость за единицу: %d, Количество: %d,\nОбщая стоимость за товар: %lf\n", t8903.name, t8903.price, c8903, (double)c8903 * ((double)t8903.price - (double)t8903.price * t8903.discount));
				}
				printf("Общая стоимость товаров в покупке: %d, Cуммарная скидка: %lf, Итоговая сумма к оплате: %lf", total_cost, total_disc, (double)total_cost - total_disc);
			}
			else {
				printf("Чек не может быть сформирован, так как отсутствуют товары");
			}

		}
		if (action == 5)
			if (total_cost != 0)
				printf("Итоговая сумма к оплате: %.0lf", (float)total_cost - total_disc);
			else
				printf("Вы ещё не добавили ни одного товара");

		scanf("%d", &action);
		while (!(1 <= action && action <= 6)) {
			printf("Некорректный ввод, введите число в промежутке от 1 до 6 включительно: ");
			int а;
			scanf("%d", &action);
			while ((а = getchar()) != '\n' && а != EOF) {}
		}
	}
	printf("До свидания, хорошего вам дня!\nСпасибо, что использовали нашу кассу!");
}