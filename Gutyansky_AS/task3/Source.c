#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "console_utils.h"

#define MIN_LENGTH 2
#define MAX_LENGTH 5
#define INTERFACE_OFFSET_X 20
#define INTERFACE_OFFSET_Y 10

#define STR_(X) #X
#define STR(X) STR_(X)

void welcome_screen();
void win_screen(int attempts);
void get_bulls_and_cows(int* bulls, int* cows, int choice, int number);
int all_digits_unique(int n);
int generate_number(int length);
int read_int(char* const question, int minValue, int maxValue);
void shuffle(int* arr, int n);
void swap(int* a, int* b);

void main() {
	int length;
	int number;
	int min_choice;
	int max_choice;
	int i;
	int user_choice;
	int bulls;
	int cows;
	int attempts;

	srand(time(NULL));
	setlocale(LC_ALL, "rus");
	welcome_screen();

	clear_screen();
	length = read_int("Введите длину числа, которое будете угадывать (" STR(MIN_LENGTH) " <= n <= " STR(MAX_LENGTH) ") : ", MIN_LENGTH, MAX_LENGTH);

	number = generate_number(length);

	min_choice = 1;
	max_choice = 10;
	for (i = 1; i < length; i++) {
		min_choice *= 10;
		max_choice *= 10;
	}
	max_choice--;

	attempts = 0;
	print_at("Компьютер загадал число от %d до %d включительно. Попробуйте угадать!",
		INTERFACE_OFFSET_X, INTERFACE_OFFSET_Y - 1, true, min_choice, max_choice);
	while (1) {
		attempts++;
		user_choice = read_int("Ваш вариант: ", min_choice, max_choice);
		
		if (!all_digits_unique(user_choice)) {
			print_at("Пожалуйста, введите число, в котором все цифры различны.", 
				INTERFACE_OFFSET_X, INTERFACE_OFFSET_Y - 1, true);
			continue;
		}

		if (user_choice == number) {
			win_screen(attempts);
			break;
		}
		else {
			get_bulls_and_cows(&bulls, &cows, user_choice, number);
			print_at("Ваш вариант: %d\tБыков: %d\tКоров: %d",
				INTERFACE_OFFSET_X, INTERFACE_OFFSET_Y - 1, true, user_choice, bulls, cows);
		}
	}
}

void win_screen(int attempts) {
	clear_screen();
	set_cursor_visible(0);
	set_window_wh(120, 40);

	set_cursor_at(INTERFACE_OFFSET_X, INTERFACE_OFFSET_Y);
	text_background(BLUE);
	text_color(WHITE);
	printf("ВЫ ПОБЕДИЛИ");

	set_cursor_at(INTERFACE_OFFSET_X, INTERFACE_OFFSET_Y + 2);
	text_background(BLACK);
	printf("Вы смогли угадать загаданное компьютером число.");
	set_cursor_at(INTERFACE_OFFSET_X, INTERFACE_OFFSET_Y + 3);
	printf("Использовано попыток: %d", attempts);
	set_cursor_at(INTERFACE_OFFSET_X, INTERFACE_OFFSET_Y + 4);
	printf("Спасибо за игру:)");

	set_cursor_at(INTERFACE_OFFSET_X, INTERFACE_OFFSET_Y + 10);
	text_color(DARKGRAY);
	printf("Нажмите Enter, чтобы выйти...");
	while (getchar() != '\n');

	text_color(WHITE);
	set_cursor_visible(1);
}

void welcome_screen() {
	clear_screen();
	set_cursor_visible(0);
	set_window_wh(120, 40);

	set_cursor_at(INTERFACE_OFFSET_X, INTERFACE_OFFSET_Y);
	text_background(BLUE);
	text_color(WHITE);
	printf("БЫКИ И КОРОВЫ");

	set_cursor_at(INTERFACE_OFFSET_X, INTERFACE_OFFSET_Y + 2);
	text_background(BLACK);
	printf("Добро пожаловать в игру \"Быки и коровы\".");
	set_cursor_at(INTERFACE_OFFSET_X, INTERFACE_OFFSET_Y + 3);
	printf("Вам предстоит угадать число, которое загадал компьютер.");
	set_cursor_at(INTERFACE_OFFSET_X, INTERFACE_OFFSET_Y + 4);
	printf("Компьютер будет говорить вам число быков(цифр, угаданных на верных позициях)");
	set_cursor_at(INTERFACE_OFFSET_X, INTERFACE_OFFSET_Y + 5);
	printf("и коров(цифр, угаданных на неверных позициях)");

	set_cursor_at(INTERFACE_OFFSET_X, INTERFACE_OFFSET_Y + 10);
	text_color(DARKGRAY);
	printf("Нажмите Enter для продолжения...");
	while (getchar() != '\n');

	text_color(WHITE);
	set_cursor_visible(1);
}

int read_int(char* const question, int minValue, int maxValue) {
	int read_arguments;
	int value;

	while (1) {
		print_at(question, INTERFACE_OFFSET_X, INTERFACE_OFFSET_Y, false);
		print_at(">>> ", INTERFACE_OFFSET_X, INTERFACE_OFFSET_Y + 3, false);

		read_arguments = scanf("%d", &value);
		while (getchar() != '\n');
		if (read_arguments == 1 && value >= minValue && value <= maxValue) {
			break;
		}

		clear_screen();
	}

	return value;
}

int generate_number(int length) {
	int i;
	int digits[10];
	int number;

	for (i = 0; i < 10; i++) {
		digits[i] = i;
	}

	shuffle(digits, 10);

	if (digits[0] == 0) {
		swap(&digits[0], &digits[1]);
	}

	number = 0;
	for (i = 0; i < length; i++) {
		number = number * 10 + digits[i];
	}

	return number;
}

void shuffle(int* arr, int n) {
	int i, j;

	for (i = n - 1; i >= 1; i--) {
		j = rand() % (i + 1);

		swap(&arr[i], &arr[j]);
	}
}

void swap(int* a, int* b) {
	int temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

int all_digits_unique(int n) {
	int digit_mask[10];
	int digit;
	int i;

	for (i = 0; i < 10; i++) {
		digit_mask[i] = 0;
	}

	while (n > 0) {
		digit = n % 10;
		if (digit_mask[digit] == 1) {
			return 0;
		}

		digit_mask[digit] = 1;
		n /= 10;
	}

	return 1;
}

void get_bulls_and_cows(int* bulls, int* cows, int choice, int number) {
	int digit_mask[10];
	int number_decomp;
	int number_digit;
	int choice_digit;
	int i;

	for (i = 0; i < 10; i++) {
		digit_mask[i] = 0;
	}

	number_decomp = number;
	while (number_decomp > 0) {
		number_digit = number_decomp % 10;
		digit_mask[number_digit] = 1;
		number_decomp /= 10;
	}
	

	*bulls = *cows = 0;

	while (number > 0) {
		number_digit = number % 10;
		choice_digit = choice % 10;

		if (number_digit == choice_digit) {
			(*bulls)++;
		}
		else if (digit_mask[choice_digit] == 1) {
			(*cows)++;
		}

		number /= 10;
		choice /= 10;
	}
}