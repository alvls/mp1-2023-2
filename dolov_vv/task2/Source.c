#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <locale.h>
#include <time.h>

int res_1()
{
	int a = 0;//вводимое пользователем число
	int count = 0;
	srand(time(0));
	int rand_ch = rand() % 1000;
	printf("Игра началась, угадывай число от 1 до 1000 \n");
	while (1)
	{
		printf("введите число\n");
		scanf("%d", &a);
		if (a < rand_ch)
		{
			printf("загаданное число больше \n");
			count += 1;
		}
		else if (a > rand_ch)
		{
			printf("загаданное число меньше \n");
			count += 1;
		}
		else
		{
			printf("угадали \n");
			count += 1;
			printf("Число ваших попыток  %d \n", count);
			system("pause");
			break;
		}
	}

}

int res_2()
{
	int a = 0;
	int count = 0;
	char zn;
	printf("Введите знак > если ваше число больше моего \n");
	printf("Введите знак < если ваше число меньше моего \n");
	printf("Введите знак = если я угадала ваше число \n");
	printf("Загадывайте число \n");
	scanf("%d", &a);
	srand(time(0));
	int rand_ch1 = rand() % 1000;
	int mx_gr = 1000;
	int mn_gr = 0;
	int cash;
	while (1)
	{
		printf("Мое число %d\n", rand_ch1);
		cash = rand_ch1;
		printf("Введите знак > или < или = : \n");
		scanf(" %c", &zn);
		if (zn == '>')
		{
			rand_ch1 = rand() % (mx_gr - rand_ch1-1) + rand_ch1 + 1;
			mn_gr = cash;
			count += 1;
		}
		else if (zn == '<')
		{
			rand_ch1 = rand() % (rand_ch1 - mn_gr-1) + mn_gr + 1;
			mx_gr = cash;
			count += 1;
		}
		else if (zn == '=')
		{
			printf("я угадала \n");
			count += 1;
			printf("Число моих попыток  %d \n", count);
			system("pause");
			break;
		}
	}
}




int main()
{
	setlocale(LC_ALL, "rus");
	printf("Давайте сыграем в игру) \n");
	int ch_res;
	int flag = 0;

	do
	{
		printf("введите цифру 1 если хотите сыграть в первый режим \n");
		printf("введите цифру 2 если хотите сыграть во второй режим \n");
		scanf("%d", &ch_res);
		if (ch_res==1)
		{
			flag = 0;
			res_1();
		}
		else if (ch_res == 2)
		{
			flag = 0;
			res_2();
		}
		else
		{
			printf("введена невозможная цифра, введите 1 или 2 \n");
			system("pause");
			flag = 1;
		}
	} while (flag == 1);
}