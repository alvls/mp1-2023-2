#include <stdio.h>
#include <locale.h>

struct product {
	char name[30];
	int barcode[4];
	int price;
	float discount;
};

int main()
{
	setlocale(LC_ALL, "rus");

	struct product product_list[10] = { { "Хлеб", {1,2,3,4}, 40, 5.0 },
										{ "Молоко", {1,2,3,5}, 90, 15.0 },
										{ "Колбаса", {1,2,3,6}, 200, 10.0 },
										{ "Яйца", {1,2,3,7}, 100, 5.0},
										{ "Яблоки", {1,2,3,8}, 150, 25.0},
										{ "Йогурт", {1,2,3,9}, 120, 15.0},
										{ "Сметана", {1,2,3,0}, 65, 5.0},
										{ "Бананы", {1,2,4,1}, 110, 10.0},
										{ "Мука", {1,2,4,2}, 115, 20.0},
										{ "Сахар", {1,2,4,3}, 65, 5.0} };
	int count[10] = { 0 };
	int n = 10;
	char choice;

	printf("Отсканировать новый товар - 1 \n");
	printf("Закончить сканирование и вывести чек - 2 \n");

	for (;;) {
		choice = menu_select();
		int b;
		int code;
		switch (choice)
		{
		case 1:
			printf("======================");
			printf("\n Отсканируйте штрих-код: ");
			scanf_s("%d", &b);
			int fl = 0;
			for (int i = 0; i < n; i++) {
				code = product_list[i].barcode[0];
				for (int j = 1; j < 4; j++)
					code = code * 10 + product_list[i].barcode[j];
				if (b == code) {
					count[i] += 1;
					printf("Добавлено: %s - %d рублей \n", product_list[i], product_list[i].price);
					printf("======================");
					fl = 1;
					break;
				}
			}
			if (fl == 0) {
				printf("\n --Товара с таким штрих-кодом не существует-- \n");
				printf("======================");
			}
			break;
		case 2:
			system("cls");
			printf("-----------------------------------------------------------------------------\n");
			printf("Кассовый чек\n");
			float coef;
			float sum = 0;
			float dscnt = 0;
			printf("Наименование      Цена     Кол-во     Итого     Скидка  Итоговая стоимость \n");
			for (int i = 0; i < n; i++)
				if (count[i] != 0) {
					coef = product_list[i].discount / 100;
					sum += product_list[i].price * count[i];
					dscnt += product_list[i].price * count[i] * coef;
					printf("%10s   -- %5d    *%5d    = %5d   -  %5.2f --> %5.2f \n", product_list[i].name, product_list[i].price, count[i], product_list[i].price * count[i], product_list[i].price * count[i] * coef, product_list[i].price * count[i] * (1 - coef));
				}
			printf("Итого к оплате: %.2f    Скидка: %.2f    С учётом скидки: %.2f \n", sum, dscnt, sum - dscnt);
			printf("                       Спасибо за покупки!\n");
			printf("-----------------------------------------------------------------------------\n");
			exit(0);
		}
	}
}

int menu_select()
{
	int c;

	do {
		printf("\n Введите номер нужной операции: ");
		scanf_s(" %d", &c);
	} while (c < 0 || c > 3);

	return c;
}


