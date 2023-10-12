#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <locale.h>
#include <time.h>


int main()
{
	srand(time(0));

	int num = rand() % 1000;
	int robot_num;
	int flag;
	int user_num = -1;
	int attempts = 0;
	char user_char, b;
	int min = 1, max = 999;

	setlocale(LC_ALL, "rus");

	do
	{
		printf("Выберите режим игры (1 - программа загадывает число, 2 - Вы загадываете число): ");
		scanf("%d", &flag);
	} while (!(flag == 1 || flag == 2));
	
	// Первый режим
	if (flag == 1)
	{
		printf("Вы выбрали первый режим! Программа загадала число от 1 до 999. Попытайтесь угадать его!\n\n");

		while (num != user_num)
		{
			scanf("%d", &user_num);
			attempts += 1;

			if (user_num == num)
			{
				printf("Загаданное число: %d. Поздравляем!\n", num);
				break;
			}

			if (user_num < num)
				printf("Загаданное число больше.\n\n");

			if (user_num > num)
				printf("Загаданное число меньше.\n\n");
		}
	
	}

	// Второй режим
	else
	{
		printf("Вы выбрали второй режим! Введите число от 1 до 999, и программа угадает его!\n");

		do
		{	
			printf("Ваше число: ");
			scanf("%d", &user_num);
		} while ((user_num < 1) || (user_num > 999));

		printf("После предположения программы, введите символ \'<\', \'>\' или \'=\'\n");
		
		do
		{
			robot_num = (min + max) / 2;

			if (min == 998)
				robot_num = 999;

			printf("\n%d?\n", robot_num);
			attempts += 1;

			scanf("%c", &b);
			scanf("%c", &user_char);

			if (user_char == '<' && user_num > robot_num)
				printf("Мне кажется, Вы меня обманываете...\n");
			else if (user_char == '<')
				max = robot_num;

			if (user_char == '>' && user_num < robot_num)
				printf("Мне кажется, Вы меня обманываете...\n");
			else if (user_char == '>')
				min = robot_num;

			if (user_char == '=' && user_num != robot_num)
				printf("Мне кажется, Вы меня обманываете...\n");

			if ((user_char == '<' || user_char == '>') && (user_num == robot_num))
				do
				{
					printf("Мне кажется, Вы меня обманываете...\n");
					scanf("%c", &b);
					scanf("%c", &user_char);
				} while (user_char != '=');

		} while (robot_num != user_num);
		
		printf("\nЯ угадал Ваше число! Это %d!\n", robot_num);
	}

	printf("Количество попыток: %d\n\n", attempts);

	system("pause");
	return 0;
}