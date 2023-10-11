#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <time.h>

#define MIN_CHOICE 1
#define MAX_CHOICE 999
#define RANDOM_MOD (MAX_CHOICE - MIN_CHOICE + 1) + MIN_CHOICE
#define STR_(X) #X
#define STR(X) STR_(X)

int read_int(char* const question, int minValue, int maxValue);
char read_char(char* const question, char* const validChars, int n);
void human_mode();
void computer_mode();

void main() {
	int mode;

	setlocale(LC_ALL, "rus");
	mode = read_int("������� ����� ������:\n\
1. ��������� �������\n\
2. ��������� ���������\n\
�����: ", 1, 2);

	
	if (mode == 1) {
		human_mode();
	}
	else {
		computer_mode();
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

char read_char(char* const question, char* const validChars, int n) {
	int read_arguments;
	int i;
	char value;

	while (1) {
		printf(question);
		read_arguments = scanf("%c", &value);
		while (getchar() != '\n');
		if (read_arguments == 1) {
			for (i = 0; i < n; i++) {
				if (value == validChars[i]) {
					break;
				}
			}

			if (i < n) {
				break;
			}
		}
	}

	return value;
}

void human_mode() {
	int number;
	int human_choice;
	int attempts;

	srand(time(NULL));
	number = rand() % RANDOM_MOD + MIN_CHOICE;
	
	printf("��������� ������� �����-�� �����. ���������� �������.\n");

	attempts = 0;
	while (1) {
		human_choice = read_int("������� ��� ����� (����� �� " STR(MIN_CHOICE) " �� " STR(MAX_CHOICE) " ������������): ", MIN_CHOICE, MAX_CHOICE);
		attempts++;
		if (human_choice > number) {
			printf("���������� ����� ������.\n");
		}
		else if (human_choice < number) {
			printf("���������� ����� ������.\n");
		}
		else {
			printf("�� ������� �� %d �������.\n", attempts);
			break;
		}
	}
}

void computer_mode() {
	int number;
	int l, r;
	int computer_choice;
	int attempts;
	char user_input;

	number = read_int("�� ����������� ����� (�� " STR(MIN_CHOICE) " �� " STR(MAX_CHOICE) " ������������): ", MIN_CHOICE, MAX_CHOICE);
	printf("������ ��������� ���������� ��� ���������.\n");

	attempts = 0;
	l = MIN_CHOICE; r = MAX_CHOICE;
	while (l <= r) {
		computer_choice = (l + r) / 2;
		attempts++;

		printf("�� �������� ����� %d?\n", computer_choice);
		user_input = read_char("����� (<, >, =): ", "<>=", 3);

		if (user_input == '<') {
			r = computer_choice - 1;
		}
		else if (user_input == '>') {
			l = computer_choice + 1;
		}
		else {
			printf("��������� ������ ���� ����� �� %d �������.\n", attempts);
			return;
		}
	}

	printf("��, ������ �� ������ �����������!\n");
}