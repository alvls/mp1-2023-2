#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <locale.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>

void RandomNumber(int n, int numbers[])
{
	numbers[0] = 1 + rand() % 9;
	for (int i = 1; i < n; i++)
	{
		int digit, count = 0;
		do
		{
			count = 0;
			digit = rand() % 10;
			for (int j = 0; j < i; j++)
			{
				if (digit != numbers[j])
					count++;
			}
		} while (count != i);
		numbers[i] = digit;
	}
}

int NonRepeating(int n, int tr)
{
	int arr[5] = { 0 };
	for (int i = n-1; i >= 0; i--)
	{
		arr[i] = tr % 10;
		tr = floor(tr / 10);
	}
	for (int i = 1; i < n; i++)
	{
		for (int j = 0; j < i; j++)
		{
			if (arr[i] == arr[j])
				return 0;
		}
	}
	return 1;
}

int CountCows(int n, int random[], int tr)
{
	int arr[5] = { 0 };
	int bulls = 0, cows = 0;
	for (int i = n - 1; i >= 0; i--)
	{
		arr[i] = tr % 10;
		tr = floor(tr / 10);
	}
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
		{
			if (i != j)
				if (arr[i] == random[j])
				{
					cows++;
					break;
				}
		}
	return cows;
}

int CountBulls(int n, int random[], int tr)
{
	int arr[5] = { 0 };
	int bulls = 0, cows = 0;
	for (int i = n - 1; i >= 0; i--)
	{
		arr[i] = tr % 10;
		tr = floor(tr / 10);
	}
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
		{
			if (i == j)
				if (arr[i] == random[j])
				{
					bulls++;
					break;
				}
		}
	return bulls;
}

int len(int n)
{
	int l = 0;
	while (n != 0)
	{
		n /= 10;
		l++;
	}
	return l;
}

void main()
{
	setlocale(LC_ALL, "rus");
	srand(time(NULL));
	int n, ch, flag, bulls = 0, cows = 0, try;
	int ComputerNumber[5] = { 0 };
	do
	{
		printf("Выберите длину n загадаемого числа(от 2 до 5): ");
		scanf("%d", &n);
		while (ch = getchar() != '\n');
		flag = 1;
		if (n >= 2 && n <= 5)
			flag = 0;
	} while (flag);
	RandomNumber(n, ComputerNumber);
	printf("Введите 0, чтобы сдаться.\n");
	do
	{
		do
		{
			printf("Введите n-значное число с неповторяющимися цифрами: ");
			scanf("%d", &try);
			while (ch = getchar() != '\n');
			flag = 1;
			if (try == 0 || (len(try) == n && NonRepeating(n, try)))
				flag = 0;
		} while (flag);
		cows = CountCows(n, ComputerNumber, try);
		bulls = CountBulls(n, ComputerNumber, try);
		if (try == 0)
			printf("Вы проиграли\n");
		else
		{
			printf("Количество коров: %d\n", cows);
			printf("Количество быков: %d\n", bulls);
		}
	} while (try != 0 && bulls != n);
	if (try != 0)
		printf("Вы победили\n");
	system("pause");
}