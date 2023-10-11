#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <time.h>

void main()
{
	setlocale(LC_ALL, "Rus");
	srand(time(0));

	int option; // выбор режима
	int answer; // ответ пользователя -- число
	int correct; // загаданное число
	int attemts; // кол-во попыток угадать число
	int sup; // граница
	int interval; // интервал уменьшения/увеличения числа
	int chislo; // первая попытка робота угадать число (50/50)
	char new_ans; // ответ пользователя роботу -- <, > или =

	sup = 1000;
	chislo = interval = sup / 2;
	attemts = 1;
	correct = rand() % 999 + 1;

	printf("Привет, пользователь! Это игра 'Угадай число'.\n"
		"У игры есть два режима.\n"
		"1) Компьютер загадывает число.\n"
		"2) Ты загадываешь число.\n");
	do
	{
		printf("Введи номер режима, для начала игры: ");
		scanf_s("%d", &option);
	} while (option > 2 || option < 1);
	if (option == 1) 
	{
		printf("Компьютер загадал число [1,1000). Введи возможное число: ");
		do 
		{
			scanf_s("%d", &answer);
			if (answer < 1 || answer > 999)
			{
				printf("Вне диапозона. Попробуй снова: ");
			}
			if (answer > correct && answer < 1000)
			{
				printf("Загаданное число меньше. Попробуй снова: ");
				attemts += 1;
			}
			if (answer < correct && answer > 0)
			{
				printf("Загаданное число больше. Попробуй снова: ");
				attemts += 1;
			}
			if (answer == correct)
			{
				printf("Угадал! Вот итоговое количество попыток - %d\n", attemts);
			}
		} while (answer != correct);
	}
	else
	{
		do
		{
			printf("Введи число [1,1000), а компьютер попробует его угадать: ");
			scanf_s("%d", &correct);
		} while (correct < 1 || correct > 999);
		printf("Загаданное число - %d ? ", chislo);
		do
		{
			scanf_s("%c", &new_ans);
			if (new_ans == 60)
			{
				printf("Значит загаданное число меньше.");
				attemts += 1;
				interval = interval / 2 + interval % 2;
				chislo -= interval;
				printf("Загаданное число - %d ? ", chislo);
			}
			if (new_ans == 62)
			{
				printf("Значит загаданное число больше.");
				attemts += 1;
				interval = interval / 2 + interval % 2;
				chislo += interval;
				printf("Загаданное число - %d ? ", chislo);
			}
			if (new_ans == 61)
			{
				printf("Угадал! Вот итоговое количество попыток - %d\n", attemts);
			}
		} while (new_ans != 61);
	}
	system("pause");
}