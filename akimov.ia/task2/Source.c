#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

void main()
{
	setlocale(LC_ALL, "rus");
	int choice, number_1, flag, ch, guess,count, number_2, guess_computer, max = 999, min = 1;
	char sigh, restart;
	srand(time(NULL));
	do
	{
		system("cls");
		do
		{
			printf("Выберите режим 1 или 2: ");
			scanf("%d", &choice);
			while (ch = getchar() != '\n');
			flag = 0;
			if ((choice != 1) && (choice != 2))
				flag = 1;
		} while (flag);
		if (choice == 1)
		{
			number_1 = 1 + rand() % 999;
			flag = 1;
			count = 0;
			printf("Введите отгадку: ");
			while (flag)
			{
				scanf("%d", &guess);
				count++;
				while (ch = getchar() != '\n');
				if (guess == number_1)
				{
					printf("Угадали, количество попыток: %d\n", count);
					flag = 0;
				}
				else if (guess < number_1)
					printf("Загаданное число больше: ");
				else
					printf("Загаданное число меньше: ");
			}
		}
		else if (choice == 2)
		{
			do
			{
				printf("Загадайте число из диапазона [1, 1000): ");
				scanf("%d", &number_2);
				while (ch = getchar() != '\n');
				flag = 1;
				if (number_2 >= 1 && number_2 < 1000)
					flag = 0;
			} while (flag);
			flag = 1;
			count = 0;
			guess_computer = 1 + rand() % 999;
			while (flag)
			{
				count++;
				printf("Число %d больше(>), меньше(<) или равно(=) загаданному? ", guess_computer);
				scanf("%s", &sigh);
				if (sigh == '=')
				{
					printf("Компьютер отгадал число, количество попыток: %d\n", count);
					flag = 0;
				}
				else if (sigh == '>')
				{
					max = guess_computer - 1;
					guess_computer = min + rand() % (max - min + 1);
				}
				else if (sigh == '<')
				{
					min = guess_computer + 1;
					guess_computer = min + rand() % (max - min + 1);
				}
			}
		}
		printf("Хотите перезапустить программу? Y = да: ");
		scanf("%s", &restart);
	} while (restart == 'y' || restart == 'Y');
	system("pause");
}