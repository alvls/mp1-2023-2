#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define MIN_LENGTH 2
#define MAX_LENGTH 5

#define STR_(X) #X
#define STR(X) STR_(X)

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
	printf("Добро пожаловать в игру быки и коровы.\n\
Вам предстоит угадать число, которое загадал компьютер.\n\
Компьютер будет говорить вам число быков (цифр, угаданных на верных позициях) и коров (цифр, угаданных на неверных позициях)\n");
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
	printf("Компьютер загадал число от %d до %d включительно. Попробуйте угадать:\n", min_choice, max_choice);
	while (1) {
		attempts++;
		user_choice = read_int("Ваш вариант: ", min_choice, max_choice);
		
		if (!all_digits_unique(user_choice)) {
			printf("Пожалуйста, введите число, в котором все цифры различны.\n");
			continue;
		}

		if (user_choice == number) {
			printf("Вы выиграли за %d попыток!\n", attempts);
			break;
		}
		else {
			get_bulls_and_cows(&bulls, &cows, user_choice, number);
			printf("Быков: %d\nКоров: %d\n", bulls, cows);
		}
	}

	system("pause");
}

int read_int(char* const question, int minValue, int maxValue) {
	int read_arguments;
	int value;

	while (1) {
		printf(question);
		read_arguments = scanf("%d", &value);
		while (getchar() != '\n');
		if (read_arguments == 1 && value >= minValue && value <= maxValue) {
			break;
		}
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
	int i, j, temp;

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