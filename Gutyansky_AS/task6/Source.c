#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <math.h>
#include "taylor_math.h"

#define FUNCTIONS_COUNT 5
#define MIN_ACCURACY 0.000001

#define STR_(X) #X
#define STR(X) STR_(X)

typedef double (*StdFunction)(double);
typedef double (*MathFunction)(double, unsigned int, double);

typedef struct {
	int mode;
	int function_index;
	double val;
	union {
		struct {
			double accuracy;
			unsigned int members_count;
		};
		unsigned int n_max;
	};
} CalculationInfo;

const MathFunction taylor_functions[FUNCTIONS_COUNT] = {
	taylor_exp,
	taylor_sin,
	taylor_cos,
	taylor_arcsin,
	taylor_arccos
};

const StdFunction std_functions[FUNCTIONS_COUNT] = {
	exp,
	sin,
	cos,
	asin,
	acos
};

void user_loop(void);
void function_menu(CalculationInfo* calc_info);
void number_menu(CalculationInfo* calc_info);
void accuracy_menu(CalculationInfo* calc_info);
void mode_menu(CalculationInfo* calc_info);
void members_count_menu(CalculationInfo* calc_info);
void experiment_count_menu(CalculationInfo* calc_info);
void single_calculation(CalculationInfo* calc_info);
void experiment_calculation(CalculationInfo* calc_info);
int try_read_int(int* result, int min_value, int max_value);

int main() {
	setlocale(LC_ALL, "rus");

	user_loop();

	return 0;
}

void user_loop(void) {
	int menu_choice;

	while (1) {
		do {
			printf("����:\n");
			printf("1 - ������� �������\n");
			printf("2 - �����\n");
			printf(">>> ");
		} while (!try_read_int(&menu_choice, 1, 2));

		if (menu_choice == 2) {
			break;
		}
		else {
			CalculationInfo info;
			
			function_menu(&info);
			number_menu(&info);
			mode_menu(&info);
			if (info.mode == 1) {
				accuracy_menu(&info);
				members_count_menu(&info);
				single_calculation(&info);
			}
			else {
				experiment_count_menu(&info);
				experiment_calculation(&info);
			}
		}
	}
}

void function_menu(CalculationInfo* calc_info) {
	int menu_choice;

	do {
		printf("�������� �������:\n");
		printf("1 - e^x\n");
		printf("2 - sin(x)\n");
		printf("3 - cos(x)\n");
		printf("4 - arcsin(x)\n");
		printf("5 - arccos(x)\n");
		printf(">>> ");
	} while (!try_read_int(&menu_choice, 1, FUNCTIONS_COUNT));

	calc_info->function_index = menu_choice - 1;
}

void number_menu(CalculationInfo* calc_info) {
	int read_arguments;
	double val;

	do {
		read_arguments = 0;
		printf("�������� �����, �� �������� ����� ��������� �������:\n");
		printf(">>> ");
		read_arguments = scanf("%lf", &val);
		while (getchar() != '\n');
	} while (read_arguments != 1);

	calc_info->val = val;
}

void mode_menu(CalculationInfo* calc_info) {
	int menu_choice;

	do {
		printf("�������� �����:\n");
		printf("1 - ����������� ������\n");
		printf("2 - �������� �����������\n");
		printf(">>> ");
	} while (!try_read_int(&menu_choice, 1, 2));

	calc_info->mode = menu_choice;
}

void accuracy_menu(CalculationInfo* calc_info) {
	int read_arguments;
	double val;

	do {
		read_arguments = 0;
		printf("�������� �������� �������� ������� (>=" STR(MIN_ACCURACY) ")\n");
		printf(">>> ");
		read_arguments = scanf("%lf", &val);
		while (getchar() != '\n');
	} while (read_arguments != 1 || val < MIN_ACCURACY);

	calc_info->accuracy = val;
}

void members_count_menu(CalculationInfo* calc_info) {
	int members_count;

	do {
		printf("�������� ����� ��������� ���� (�� 1 �� 1000):\n");
		printf(">>> ");
	} while (!try_read_int(&members_count, 1, 1000));

	calc_info->members_count = members_count;
}

void experiment_count_menu(CalculationInfo* calc_info) {
	int count;

	do {
		printf("�������� ���������� ������������� (�� 1 �� 25):\n");
		printf(">>> ");
	} while (!try_read_int(&count, 1, 25));

	calc_info->n_max = count;
}

void single_calculation(CalculationInfo* calc_info) {
	double res;

	res = taylor_functions[calc_info->function_index](calc_info->val, calc_info->members_count, calc_info->accuracy);

	printf("��������� ����������: %lf\n", res);
}

void experiment_calculation(CalculationInfo* calc_info) {
	int i;
	double res_taylor;
	double res_mathlib;
	double error;

	printf("���-�� ��������� ������          ��������� ����. ���. ������\n");
	printf("---------------- --------------- --------------- ---------------\n");
	for (i = 1; i <= calc_info->n_max; i++) {
		res_taylor = taylor_functions[calc_info->function_index](calc_info->val, i, 0);
		res_mathlib = std_functions[calc_info->function_index](calc_info->val);
		error = fabs(res_mathlib - res_taylor);
		printf("%16d %-15lf %-15lf %-15lf\n", i, res_taylor, res_mathlib, error);
	}
}

int try_read_int(int* result, int min_value, int max_value) {
	int read_arguments;

	read_arguments = scanf_s("%d", result);
	while (getchar() != '\n');
	if (read_arguments == 1 && *result >= min_value && *result <= max_value) {
		return 1;
	}

	return 0;
}