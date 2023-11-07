#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <locale.h>
#include <time.h>
#include <time.h>

struct product
{
	char strih[4];
	char name[30];
	int cost;
	int count;
	int discount;
};

void main()
{
	setlocale(LC_ALL, "rus");
	srand(time(NULL));
	
	struct product pr[10];

	strcpy(pr[0].strih, "1234");
	strcpy(pr[0].name, "Бородинский хлеб в нарезке");
	pr[0].cost = 42;
	pr[0].discount =  5 * (rand() % 10 + 1);
	
	strcpy(pr[1].strih, "1207");
	strcpy(pr[1].name, "Подсолнечное масло");
	pr[1].cost = 112;
	pr[1].discount = 5 * (rand() % 10 + 1);

	strcpy(pr[2].strih, "3007");
	strcpy(pr[2].name, "Чипсы рифленые с лобстером");
	pr[2].cost = 119;
	pr[2].discount = 5 * (rand() % 10 + 1);

	strcpy(pr[3].strih, "4625");
	strcpy(pr[3].name, "Булочка с маком");
	pr[3].cost = 28;
	pr[3].discount = 5 * (rand() % 10 + 1);

	strcpy(pr[4].strih, "9999");
	strcpy(pr[4].name, "Пряник Тульский");
	pr[4].cost = 51;
	pr[4].discount = 5 * (rand() % 10 + 1);

	strcpy(pr[5].strih, "2678");
	strcpy(pr[5].name, "Вафли Артек");
	pr[5].cost = 65;
	pr[5].discount = 5 * (rand() % 10 + 1);

	strcpy(pr[6].strih, "5858");
	strcpy(pr[6].name, "Мука пшеничная");
	pr[6].cost = 38;
	pr[6].discount = 5 * (rand() % 10 + 1);

	strcpy(pr[7].strih, "3021");
	strcpy(pr[7].name, "Йогурт питьевой");
	pr[7].cost = 49;
	pr[7].discount = 5 * (rand() % 10 + 1);

	strcpy(pr[8].strih, "8057");
	strcpy(pr[8].name, "Лавровый лист");
	pr[8].cost = 15;
	pr[8].discount = 5 * (rand() % 10 + 1);

	strcpy(pr[9].strih, "7741");
	strcpy(pr[9].name, "Кетчуп шашлычный");
	pr[9].cost = 75;
	pr[9].discount = 5 * (rand() % 10 + 1);

	char strihcode[4];
	int fl1;
	int fl2;
	int end;
	char count[10] = {0};
	float total_discount = 0;
	int cost_of_goods = 0;

	printf("Здравствуйте, рады видеть вас в нашем магазине!\n");
	printf("Только у нас самые высокие скидки и самый качественный товар.\n");
	printf("Надеюсь вы останетесь довольны работой новейшего электронного кассового аппарата)\n");
	printf("\n");
	printf("Возможные для покупки продукты\n");
	printf("1234 - Бородинский хлеб в нарезке\n");
	printf("1207 - Подсолнечное масло\n");
	printf("3007 - Чипсы рифленые с лобстером\n");
	printf("4625 - Булочка с маком\n");
	printf("9999 - Пряник Тульский\n");
	printf("2678 - Вафли Артек\n");
	printf("5858 - Мука пшеничная\n");
	printf("3021 - Йогурт питьевой\n");
	printf("8057 - Лавровый лист\n");
	printf("7741 - Кетчуп шашлычный\n");
	printf("\n");
	while (1) {
		printf("Введите пожалуйста штрихкод товара \n");
		for (int i = 0; i < 4; i++) {
			scanf_s(" %c", &strihcode[i]);
		}
		fl1 = -1;
		for (int i = 0; i < 10; i++) {
			fl2 = 1;
			for (int j = 0; j < 4; j++) {
				if (pr[i].strih[j]!= strihcode[j]) {
					fl2 = 0;
					break;
				}
			}
			if (fl2 == 1)
				fl1 = i;
		}
		if (fl1 == -1) {
			printf("Товар не определен, проверьте подлинность штрихкода!\n");
		}
		else {
			printf("Наименование: %s, Стоимость за товар: %d руб., скидка: %d%% \n", pr[fl1].name, pr[fl1].cost, pr[fl1].discount);
			count[fl1]++;

			total_discount = total_discount + pr[fl1].cost * pr[fl1].discount * 0.01;
			cost_of_goods = cost_of_goods + pr[fl1].cost;
			printf("Если вы пробили все товары,которые хотели, введите 1, иначе введите другое число \n");
			scanf_s("%d", &end);
			if (end == 1) {
				break;
			}
		}
	}
	printf("\n");
	printf("Подождите, чек формируется...\n");
	printf("\n");
	printf("					!ЧЕК!\n");
	for (int i = 0; i < 10; i++) {
		if (count[i] != 0)
			printf("Наименование товара: %s, стоимость за единицу товара: %d руб., количесво: %d, общая стоимость: %d руб.\n", pr[i].name, pr[i].cost, count[i], pr[i].cost*count[i] - (int)(pr[i].cost*count[i] * pr[i].discount * 0.01));
	}
	printf("Общая стоимость товаров - %d руб.\n", cost_of_goods);
	printf("Общая скибка - %d руб.\n", (int)total_discount);
	printf("Итоговая сумма к оплате - %d руб.\n", cost_of_goods - ((int)total_discount));
	system("pause");
}
