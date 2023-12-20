#include "taylor.h"
#include <stdio.h>
#include <math.h>


double sinTaylor(double x, double acc, int N, int* el) {
	double currentSum = x, prevSum = 0.0, term = x;
	int iteration = 0, signFactor = 1, fact_counter = 1;
	while (fabs(currentSum - prevSum) > acc && iteration < N) {
		prevSum = currentSum;
		fact_counter += 2;
		if (acc == -1)
			printf("%9d | %18f | %7f\n", iteration + 1, currentSum, fabs(currentSum - sinl(x)));
		term *= (-1) * x * x / (fact_counter * (fact_counter - 1));
		currentSum += term;
		iteration++;
	}
	*el = iteration+1;
	return currentSum;
}

double cosTaylor(double x, double acc, int N, int* el) {
	double currentSum = 1.0, prevSum = 0.0, term = 1.0;
	int termSign = 1, iteration = 0, fact_counter = 0;
	while ((fabs(currentSum - prevSum) > acc) && (iteration < N)) {
		prevSum = currentSum;
		if (acc == -1)
			printf("%9d | %18f | %7f\n", iteration + 1, currentSum, fabs(currentSum - cosl(x)));
		term *= -x * x / ((fact_counter + 1) * (fact_counter + 2));
		currentSum += term;
		fact_counter += 2;
		iteration++;
	}
	*el = iteration+1;
	return currentSum;
}

double expTaylor(double x, double acc, int N, int* el) {
	double currentSum = 1.0, prevSum = 0.0, term = 1.0;
	int iteration = 0, fact_counter = 1;
	while ((iteration < N) && (fabs(currentSum - prevSum) > acc)) {
		prevSum = currentSum;
		if (acc == -1)
			printf("%9d | %18f | %7f\n", iteration + 1, currentSum, fabs(currentSum - expl(x)));
		term *= x / fact_counter;
		currentSum += term;
		fact_counter += 1;
		iteration++;
	}
	*el = iteration+1;
	return currentSum;
}

double arctgTaylor(double x, double acc, int N, int* el) {
	double currentSum =x, prevSum = 0.0, term = x;
	int iteration = 0;
	int fact_counter = 1;
	int count = 0;
	while ((fabs(currentSum - prevSum) > acc) && (iteration < N)) {
		prevSum = currentSum;
		if (acc == -1)
			printf("%9d | %18f | %7f\n", iteration+1, currentSum, fabs(currentSum - atanl(x)));
		iteration++;
		count = fact_counter;
		fact_counter += 2;
		term = -term * count * x * x / (fact_counter);
		currentSum += term;
	}
	*el = iteration+1;
	return currentSum;
}
