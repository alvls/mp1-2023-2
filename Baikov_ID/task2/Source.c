#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <math.h>

int main()
{
	setlocale(LC_ALL, "Rus");

	int at_num, r_num, user_num, type, guesses_num, x, y = 1, z= 100;
	char operat;
	//at_num - число которое ввел пользователь
	//guesses_num - количество попыток
	// y - левая граница случайного набора чисел (1)
	// z - правая граница случайного набора чисел (1000)
	guesses_num = 0;
	printf("Введите 1 (Игрок отгадывает число) или 2 (игрок загадывает число) ");
	scanf_s("%d", &type);

	if (type == 1) 
	{
		r_num = rand() % 1001;
		printf("Угадайте число, загаданное программой ");
		while (1) 
		{
			scanf_s("%d", &at_num);
			
			if (at_num > r_num) 
			{
				printf("Введите число поменьше ");
			}
			else if (at_num < r_num)
			{
				printf("Введите число побольше ");
			}
			else 
			{
				printf("Вы угадали! ");
				break;
			}
			guesses_num++;
		}
		printf("Количество попыток: %d ", guesses_num);
	}

	else if (type == 2) 
	{
		printf("Загадайте число от 1 до 1000, которое должна отгадать программа \n");
		printf("Если ваше число больше, то введите знак '>', если ваше число меньше, то введите знак '<', а если ваше число равно данному, то введите знак '=' ");
		scanf_s(" %d", &user_num);
		if (user_num > 0 && user_num < 1001) 
		{
			printf("Число 500? ");
			scanf_s(" %c", &operat, 1);
			x = 500; //Первое число которое предполагает программа
			while (operat != '=') 
			{
				if (operat == '>') 
				{
					y = x;
					x = (((z - x) / 2) + x);
				}
				else if (operat == '<')
				{
					z = x;
					x = (((x - y) / 2) + y);
				}
				else
				{
					printf("Неверная команда ");
					guesses_num--;
				}
				guesses_num++;
				printf("Это число %d ", x);
				scanf_s(" %c", &operat, 1);
			}
			printf("Число угадано! ");
			printf("Количество попыток: %d ", guesses_num);
		}
		else {
			printf("Число должно быть в промежутке от 1 до 1000");
		}
	}
	else 
	{
		printf("Такого режима нет ");
	}
	system("pause");
}
