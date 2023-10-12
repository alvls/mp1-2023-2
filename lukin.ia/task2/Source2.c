#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <locale.h>

int main()
{
	setlocale(LC_ALL, "rus");
	int vybor_r, chislo, ch1, ch1p, itog, att, ch2, ot, doo;
	char ocenka;
	printf("¬ыберите режим:\n1 - отгдадать число 1-999\n2 - загадать число 1-999\n");
	scanf("%i", &vybor_r);
	att = 0;
	itog = 0;
	if (vybor_r == 1)//режим отгадывани€
	{
		srand(time(NULL));
		ch1 = (1 + rand() % (1000));
		do
		{
			att++;
			printf("ѕопробуйте отгдать число\n");
			scanf("%i", &ch1p);
			if (ch1p == ch1)
			{
				printf("¬ы победили!\n");
				itog = 1;
			}
			else if (ch1p < ch1)
			{
				printf("¬аше число меньше загаданного, попробуйте еще!\n");
				itog = 0;
			}
			else if (ch1p > ch1)
			{
				printf("¬аше число больше загаданного, попробуйте еще!\n");
				itog = 0;
			}
		} while (itog != 1);
	}
	else if (vybor_r == 2)//режим загадывани€
	{
		ot = 1;
		doo = 999;
		printf("«агадайте число от 1 до 999, запомните его\n");
		do//тут другой подсчет att, т.к этот цикл почему-то выполн€етс€ дважды 
		{ 
			srand(time(NULL));
			ch2 = ot + rand() % (doo - ot);//от минимального значени€ до максимального
			printf("„исло %i больше, меньше или равно числу, что вы загадали?  ", ch2);//вот эта строка дважды выводитс€ по какой то причине
			scanf("%c", &ocenka);
			if (ocenka == '=')
			{
				printf("Ѕот угадал ваше число\n");
				itog = 1;
				att++;
			}
			else if (ocenka == '>')
			{
				doo = ch2 - 1;//чтобы само предельное число больше не попалось
				itog = 0;
				att++;
			}
			else if (ocenka == '<')//то же самое что в 60
			{
				ot = ch2 + 1;
				itog = 0;
				att++;
			}
		} while (itog != 1);
	}
	printf(" оличество попыток: %i\n", att);
	system("pause");
}