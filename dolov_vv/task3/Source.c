#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <locale.h>
#include <time.h>
#include <math.h>


int digit_v_nomber(int rand_ch1, int ln_ch)
{
	int mass[10] = { 0 };
	int dig;
	int a = rand_ch1;
	while (a>0)
	{
		dig = a % 10;
		a /= 10;
		mass[dig]++;
	}
	int i;
	for (i = 1; i < 10; i++)
	{
		if (mass[i] > 1)
		{
			return 1;
			break;
		}
		return 0;
	}
}



void main()
{
	setlocale(LC_ALL, "rus");
	printf("Давайте сыграем в игру - 'Быки и Коровы' \n");
	int flag = 0;
	int ln_ch;
	srand(time(0));

	do
	{
		printf("Выберите длину загадывааемого числа (от 2 до 5) \n");
		scanf("%d", &ln_ch);
		if ((ln_ch < 2) || (ln_ch > 5))
		{
			printf("неправильно введена длина загадываемого числа \n");
			system("pause");
			flag = 1;
		}
		else
			flag = 0;
	} while (flag == 1);


	int rand_ch;
	do
	{
		rand_ch = rand() % ((int)(pow(10, ln_ch) - pow(10, ln_ch - 1))) + (int)pow(10, ln_ch - 1);
		if (digit_v_nomber(rand_ch, ln_ch))
			flag = 1;
		else
			flag = 0;
	} while (flag == 1);

	int a = 0;//вводимое пользователем число
	int k_cow = 0;
	int k_bool = 0;
	int mass_a[10] = { 0 };
	int mass_rand_ch[10] = { 0 };
	int last_number_a;
	int last_number_rand_ch;
	int r_ch, a1;

	r_ch = rand_ch;
	for (int i = 1; i <= ln_ch; i++)
	{
		last_number_rand_ch = r_ch % 10;
		mass_rand_ch[last_number_rand_ch]++;
		r_ch /= 10;
	}
	r_ch = rand_ch;
	for (int i = 1; i <= ln_ch; i++)
	{
		r_ch /= 10;
	}


	printf("Я загадал число, отгадывай \n");
	printf("Если хотите сдаться введите число -1, иначе \n");
	while (1)
	{
		k_cow = 0;
		k_bool = 0;
		for (int i = 0; i < 10; i++)
			mass_a[i] = 0;

		printf("Введите свой вариант - число с неповторяющимися цифрами \n");
		scanf("%d", &a);
		if (a == -1)
		{
			printf("Поражение \nКак жаль, что вы сдались; Я верил в вашу победу \nБуду ждать вашего возвращения \n");
			break;
		}
		if (a==rand_ch)
		{
			printf("Победа, вы угадали число! \n");
			break;
		}

		r_ch = rand_ch;
		a1 = a;
		for (int i = 1; i <= ln_ch; i++)
		{
			if (r_ch % 10 == a1 % 10)
				k_bool += 1;
			last_number_a = a1 % 10;
			mass_a[last_number_a]++;
			a1 /= 10;
			r_ch /= 10;
		}


		for (int i = 0; i < 10; i++)
		{
			if ((mass_rand_ch[i]>0) && (mass_a[i] > 0))
				k_cow=k_cow+ mass_a[i];
		}

		printf("Результат: %d", k_cow-k_bool);
		printf(" коров(ы)(а), %d", k_bool);
		printf(" бык(а)(ов) \n");
	}
	system("pause");
}
