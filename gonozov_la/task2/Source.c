#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <locale.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include < string.h > 

void game1();
void game2();

void main()
{	
	int k; //выбор режима игры
	setlocale(LC_ALL, "rus");
	printf("Добро пожаловать в программу \"Угадай число\"\nВ какой режим игры вы хотите сыграть ?\nВведите 1, если в первый, или 2, если во второй ");
	scanf("%d", &k);
	switch (k) {
	case 1:
		game1();
		break;
	case 2:
		game2();
		break;
	default:
		do {
			printf("Пожалуйста, введите 1 или 2 ");
			scanf("%d", &k);
		} while ((k != 1) && (k != 2));
		switch (k) {
		case 1:
			game1();
			break;
		case 2:
			game2();
			break;
		}
	}
	system("pause");
}
void game1() {
	srand(time(0));
	int num = (rand() % 999) + 1; //загаданное программой число
	int s; //отгадываемое пользователем число
	int count = 0; //количество попыток
	printf("Сделайте догадку, введя число из диапазона от 1 до 999 включительно: ");
	scanf("%d", &s);
	while (!(0 < s && s < 1000)) {
		printf("Вы ввели число не из диапазона от 1 до 999 включительно, введите ещё раз: ");
		scanf("%d", &s);
	}
	count++;
	while (s != num)
		if (s > num)
		{
			printf("Введённое число больше загаданного\nПопытайтесь ещё раз: ");
			scanf("%d", &s);
			count++;
		}
		else if (s < num)
		{
			printf("Введённое число меньше загаданного\nПопытайтесь ещё раз: ");
			scanf("%d", &s);
			count++;
		}
	printf("Угадали! Количество затраченных попыток: %d ", count);
}
void game2() {
	int s; //отгадываемое программой число
	srand(time(NULL));
	int num; //догадки программы
	char c; //символы вводимые пользователем
	int count = 0; //количество попыток
	int vg = 1000; // верхняя граница
	int ng = 0; //нижняя граница
	printf("Введите число из диапазона от 1 до 999 включительно, которое должна отгадать программа: ");
	scanf("%d", &s);
	while (!(0 < s && s < 1000)) {
		printf("Вы неправильно ввели угадываемое программой число, введите ещё раз: ");
		scanf("%d", &s);
	}
	printf("Программа будет высказывать догадки,\nесли загаданное число больше догадки программы, пишите \">\",\nесли меньше - \"<\", если равно - \"=\"\n");
	do {
		num = (rand()) % (vg - ng - 1) + ng + 1;
		int а;
		while ((а = getchar()) != '\n' && а != EOF) {}
		printf("Загаданное число равно %d?\nВведите ответ на догадку: ", num);
		scanf_s("%c", &c);
		while ((c != '>') && (c != '<') && (c != '=')) {
			while ((а = getchar()) != '\n' && а != EOF) {}
			printf("Вы неправильно ввели ответ на догадку, введите ещё раз \">\", \"<\" или \"=\": ");
			scanf("%c", &c);
		}
		count++;
		if (c == '>')
		{
			ng = num;
		}
		else if (c == '<')
		{
			vg = num;
		}
	} while (c != '=');
	printf("Программа угадала число, причём количество попыток равно %d ", count);
}