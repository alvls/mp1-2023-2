#include "header.h"
#include <stdio.h>

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

void mode1() {
	
}

void mode2() {}
