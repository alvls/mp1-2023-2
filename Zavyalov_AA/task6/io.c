#include "header.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void getmode(int* mode) { // TODO если сразу нажать ентер, то ничего не произойдет
	char foo;
	printf("Select the operating mode of the program by typing 1 or 2 where: \n1 stands for a single calculation of the function at a given point \n2 stands for serial experiment \nEnter the number: ");
	while (1) {
		foo = getchar();
		if (foo == '\n') {
			printf("Please enter a digit: ");
			continue;
		}
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
			else {
				if (argument > 10)
					printf("!!! WARNING !!!\nWith arguments very different from 0, the program may not work correctly (especially for trigonomical functions).\n");
				return argument;
			}
		}
		else {
			printf("An error occurred while getting the number. Please try again.\n");
			while (getchar() != '\n');
		}
		printf("Enter the argument: ");
	}
	
}

int getquantity() {
	int quantity;
	char buffer[100];

	printf("Enter the number of row elements (from 1 to 1000): ");
	while (1) {
		if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
			char* endptr;
			quantity = strtol(buffer, &endptr, 10);

			if (endptr == buffer || *endptr != '\n') {
				printf("Please enter integer number.\n");
			}
			else
			{
				if (quantity < 1 || quantity > 1000) {
					printf("Please enter a number only from 1 to 1000.\n");
				}
				else
				{
					return quantity;
				}
			}
		}
		printf("Enter the number of row elements: ");
	}
}

int getnmax() {
	int nmax;
	char buffer[100];

	printf("Enter the number of experiments (from 1 to 25): ");
	while (1) {
		if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
			char* endptr;
			nmax = strtol(buffer, &endptr, 10);

			if (endptr == buffer || *endptr != '\n') {
				printf("Please enter integer number.\n");
			}
			else
			{
				if (nmax < 1 || nmax > 25) {
					printf("Please enter a number only from 1 to 25.\n");
				}
				else
				{
					return nmax;
				}
			}
		}
		printf("Enter the number of experiments: ");
	}

}

void getfunc(func_ptr_t* target, standart_func_ptr_t* standart) {
	func_ptr_t func_ptr;
	func_ptr_t* ptrs[5] = {tey_sin, tey_cos, tey_exp, tey_sinh, tey_cosh};
	standart_func_ptr_t* standartptrs[5] = { sin, cos, exp, sinh, cosh};
	func_ptr_t a = ptrs[0];

	printf("Select the function by entering a number from 1 to 5, where:\n1 stands for sin(x)\n2 stands for cos(x)\n3 stands for exp(x)\n4 stands for sinh(x)\n5 stands for cosh(x)\n");
	while (1) {
		printf("Enter the number: ");
		char num = getchar();
		if (num == '\n') {
			printf("Please enter a digit.\n");
			continue;
		}
		char slashn = getchar();
		if (slashn != '\n') {
			printf("Please enter only one digit.\n");
			while ((slashn = getchar()) != '\n');
		}
		else if (num - '1' < 0 || num - '5' > 0) {
			printf("Please enter only a number from 1 to 5.\n");
		}
		else {
			*target = ptrs[num - '1'];
			*standart = standartptrs[num - '1'];
			return;
		}
	}
}

void mode1(func_ptr_t func, standart_func_ptr_t standartfunc) {
	double x = getargument(), precision = getprecision();
	int n = getquantity(), elemcount;
	double res = func(x, precision, n, &elemcount), reference = standartfunc(x);
	if (res == INFINITY) {
		printf("The number of calculations required to calculate the result is too large for computer to handle. \nPlease try reducing the number of elements in the row or increasing the precision value.\n");
		mode1(func, standartfunc);
	}
	else {
		printf("Reference value: %llf\nFunction value at this point is approximately %llf\nDifference between reference value and approximate value is %llf\nAmount of calculated elements is %i\n", reference, res, reference - res, elemcount);
	}
}

void mode2( func_ptr_t func, standart_func_ptr_t standartfunc) {
	double x = getargument();
	int nmax = getnmax(), foo, mxlen = 17;
	double reference = standartfunc(x);
	double* results = malloc(sizeof(double) * nmax);
	for (int i = 0; i < nmax; i++) {
		results[i] = func(x, 0, i + 1, &foo);
		char mystr[255];
		sprintf(mystr, "%f", results[i]);
		int len = strlen(mystr);
		if (len > mxlen)
			mxlen = len;
	}
	printf("Reference value: %llf\n", reference);
	if (mxlen == 17)
		printf("N  | Approximate value | Difference in values\n");
	else
	{
		printf("N  | Approximate value ");
		for (int i = 0; i < (mxlen - 17); i++) {
			printf(" ");
		}
		printf("| Difference in values\n");
	}
	for (int n = 1; n <= nmax; n++) {
		double res = results[n - 1];
		char mystr[255];
		sprintf(mystr, "%f", res);
		int len = strlen(mystr);
		if ((nmax >= 10 && n < 10) || (nmax < 10)) 
			printf("%i  | ", n);
		else 
			printf("%i | ", n);
		
		printf("%llf", res);
		for (int i = 0; (i < (mxlen - len) && mxlen == 17) || (i < (mxlen - len) + 1); i++) {
			printf(" ");
		}
		printf("| %llf\n", fabs(res - reference));
	}
}
