#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <locale.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>

char ProductName(int a)// a - номер нужного нам товара в массиве(от 0 до 9)
{
	char arr[][20] = { "GeForce RTX 3060", "GeForce GTX 1660", "GeForce RTX 4060", "GeForce GTX 1650", "AMD Radeon RX 6600",
		"GeForce RTX 3070 Ti", "GeForce RTX 4090", "GeForce RTX 4070 Ti", "AMD Radeon RX 6700", "GeForce RTX 4070" };
	return puts(arr[a]);

}

int ProductPrice(int b)// b номер нужной нам цены в массиве(от 0 до 9)
{
	int price[10] = { 34000, 26000, 40000, 16000, 27000, 62000, 184000, 96000, 45000, 78000 };
	return price[b];
}

float Discount()
{
	float skidka;
	int a;
	do
	{
		a = 5 + rand() % 46;
	} while (a % 5 != 0);
	skidka = 1 - a / 100.;
	return skidka;
}

void main()
{
	setlocale(LC_ALL, "rus");
	srand(time(NULL));
	int flag, choice, discount1, total_price_without_discount = 0, total_price_with_discount = 0, total_discount = 0, i = 0, barcodeint;
	float discount;
	int quantity[10] = { 0 };
	char barcode[4] = { 0 };
	char barcodestr[4] = "";
	printf("Добро пожаловать в магазин видеокарт! У нас есть на выбор 10 видеокарт с указанием их названий, цен в рублях и штрих-кодов"
		" соответсвенно:\n");
	printf("1.GeForce RTX 3060 - 34000 рублей/шт - 2735\n");
	printf("2.GeForce GTX 1660 - 26000 рублей/шт - 5962\n");
	printf("3.GeForce RTX 4060 - 40000 рублей/шт - 3933\n");
	printf("4.GeForce GTX 1650 - 16000 рублей/шт - 9087\n");
	printf("5.AMD Radeon RX 6600 - 27000 рублей/шт - 4352\n");
	printf("6.GeForce RTX 3070 Ti - 62000 рублей/шт - 4727\n");
	printf("7.GeForce RTX 4090 - 184000 рублей/шт - 2821\n");
	printf("8.GeForce RTX 4070 Ti - 96000 рублей/шт - 6327\n");
	printf("9.AMD Radeon RX 6700 - 45000 рублей/шт - 4341\n");
	printf("10.GeForce RTX 4070 - 78000 рублей/шт - 3520\n\n");
	printf("Вводите штрих-коды заинтересовавших Вас товаров и мы будем добавлять эти товары Вам в чек!\n");
	printf("Скидки устанавливаются на каждый товар независимо от 5 до 50 процентов.\n\n");
	do
	{
		printf("Введите штрих-код: ");
		scanf("%4s", barcodestr);
		for (i = 0; i < 4; i++)
			barcode[i] = barcodestr[i];
		barcodeint = strtol(barcodestr, NULL, 10);
		if (barcodeint == 2735)
		{
			quantity[0]++;
			printf("Вы отсканировали %d - GeForce RTX 3060 - %d рублей/шт\n", barcodeint, ProductPrice(0));
		}
		else if (barcodeint == 5962)
		{
			quantity[1]++;
			printf("Вы отсканировали %d - GeForce GTX 1660 - %d рублей/шт\n", barcodeint, ProductPrice(1));
		}
		else if (barcodeint == 3933)
		{
			quantity[2]++;
			printf("Вы отсканировали %d - GeForce RTX 4060 - %d рублей/шт\n", barcodeint, ProductPrice(2));
		}
		else if (barcodeint == 9087)
		{
			quantity[3]++;
			printf("Вы отсканировали %d - GeForce GTX 1650 - %d рублей/шт\n", barcodeint, ProductPrice(3));
		}
		else if (barcodeint == 4352)
		{
			quantity[4]++;
			printf("Вы отсканировали %d - AMD Radeon RX 6600 - %d рублей/шт\n", barcodeint, ProductPrice(4));
		}
		else if (barcodeint == 4727)
		{
			quantity[5]++;
			printf("Вы отсканировали %d - GeForce RTX 3070 Ti - %d рублей/шт\n", barcodeint, ProductPrice(5));
		}
		else if (barcodeint == 2821)
		{
			quantity[6]++;
			printf("Вы отсканировали %d - GeForce RTX 4090 - %d рублей/шт\n", barcodeint, ProductPrice(6));
		}
		else if (barcodeint == 6327)
		{
			quantity[7]++;
			printf("Вы отсканировали %d - GeForce RTX 4070 Ti - %d рублей/шт\n", barcodeint, ProductPrice(7));
		}
		else if (barcodeint == 4341)
		{
			quantity[8]++;
			printf("Вы отсканировали %d - AMD Radeon RX 6700 - %d рублей/шт\n", barcodeint, ProductPrice(8));
		}
		else if (barcodeint == 3520)
		{
			quantity[9]++;
			printf("Вы отсканировали %d - GeForce RTX 4070 - %d рублей/шт\n", barcodeint, ProductPrice(9));
		}
		do
		{
			flag = 0;
			printf("Введите 0, чтобы закончить покупки, или 1, чтобы продолжить покупки: ");
			scanf("%d", &choice);
			while (getchar() != '\n');
			if (choice != 0 && choice != 1)
				flag = 1;
		} while (flag);
	} while (choice);
	printf("Покупки завершены!\n\n");
	i = 0;
	do
	{
		if (quantity[i] != 0)
		{
			discount = Discount();
			discount1 = discount * 100;
			discount1 = 100 - discount1;
			ProductName(i);
			printf("Цена: %d\n", ProductPrice(i));
			printf("Количество: %d\n", quantity[i]);
			printf("Общая стоимость за товар без скидки: %d\n", quantity[i] * ProductPrice(i));
			printf("Общая стоимость за товар с учётом скидки %d процентов: %.0f\n\n", discount1, (quantity[i] * ProductPrice(i) * discount));
			total_price_without_discount += quantity[i] * ProductPrice(i);
			total_price_with_discount += quantity[i] * ProductPrice(i) * discount;
			total_discount += discount1 * quantity[i] * ProductPrice(i) / 100;
		}
		i++;
	} while (i < 10);
	printf("Общая стоимость за товары без скидки: %d\n", total_price_without_discount);
	printf("Суммарная скидка за все товары: %d\n", total_discount);
	printf("Итоговая сумма к оплате: %d\n", total_price_with_discount);
	system("pause");
}