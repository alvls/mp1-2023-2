#include "header.h"
#include <stdio.h>
#include <stdlib.h>

void getmode(int* mode) {
	char foo;
	printf("Select the operating mode of the program by typing 1 or 2 where 1 stands for a single calculation of the function at a given point and 2 stands for serial experiment: ");
	while (1) {
		foo = getchar();
		char slashn = getchar();
		if (slashn != '\n') {
			printf("Please enter only 1 digit [1/2]: ");
			while ((slashn = getchar()) != '\n');
		}
		else if (foo != '1' && foo != '2') {
			printf("Please enter only 1 or 2: ");
		}
		else
		{
			break;
		}
	}
	*mode = (int)(foo - '0');
}

double getprecision() {
	double precision;
	char buffer[100];
	printf("Enter the precision (precision must be >= 0.000001): ");
	while (1) {
		if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
			char* endptr;
			precision = strtod(buffer, &endptr);

			if (endptr == buffer || *endptr != '\n') {
				printf("Please enter real number.\n");
				//if (*endptr != '\n') while (getchar() != '\n');
			}
			else if (precision >= 0.000001)
				return precision;
			else {
				printf("Precision must be >= 0.000001. Please try different precision.\n");
			}
		}
		else {
			printf("An error occurred while getting the number. Please try again.\n");
			while (getchar() != '\n');
		}
		printf("Enter the precision: ");
	}
}

double getargument() {
	double argument;
	char buffer[100];
	printf("Enter the argument: ");
	while (1) {
		if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
			char* endptr;
			argument = strtod(buffer, &endptr);

			if (endptr == buffer || *endptr != '\n') {
				printf("Please enter real number.\n");
				//if (*endptr != '\n') while (getchar() != '\n');
			}
			else 
				return argument;
		}
		else {
			printf("An error occurred while getting the number. Please try again.\n");
			while (getchar() != '\n');
		}
		printf("Enter the argument: ");
	}
}

func_ptr_t getfunc() {
	func_ptr_t func_ptr;
	func_ptr_t* ptrs[4] = {tey_sin, tey_cos, tey_exp, tey_sinh};
	printf("Select the function by entering a number from 1 to 4, where:\n1 stands for sin(x)\n2 stands for cos(x)\n3 stands for exp(x)\n4 stands for sinh(x)\n");
	while (1) {
		printf("Enter the number: ");
		char num = getchar(), slashn = getchar();
		if (slashn != '\n') {
			printf("Please enter only one digit.\n");
			while ((slashn = getchar()) != '\n');
		}
		else if (num - '1' < 0 || num - '4' > 0) {
			printf("Please enter only a number from 1 to 4.\n");
		}
		else {
			return ptrs[num - '1'];
		}
	}
}

void mode1(func_ptr_t func, int n) {
	double precision = getprecision(), x = getargument();
}

void mode2() {}
