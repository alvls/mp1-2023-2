#include "taylor_math.h"

#include <math.h>

#define PI 3.14159265358979323846

double taylor_exp(double x, unsigned int members_count, double accuracy) {
	double res;
	double member;
	unsigned int i;

	res = 0.0;
	member = 1.0;

	for (i = 1; i <= members_count; i++) {
		res += member;

		member *= (x / i);

		if (fabs(member) < accuracy) {
			break;
		}
	}

	return res;
}

double taylor_sin(double x, unsigned int members_count, double accuracy) {
	double res;
	double member;
	unsigned int i;

	res = 0.0;
	member = x;

	for (i = 1; i <= members_count; i++) {
		res += member;

		member *= -(x * x) / ((2*i) * (2*i + 1));

		if (fabs(member) < accuracy) {
			break;
		}
	}

	return res;
}

double taylor_cos(double x, unsigned int members_count, double accuracy) {
	double res;
	double member;
	unsigned int i;

	if (fabs(x) > 1.0) {
		return NAN;
	}

	res = 0.0;
	member = 1.0;

	for (i = 1; i <= members_count; i++) {
		res += member;

		member *= -(x * x) / ((2 * i) * (2 * i - 1));

		if (fabs(member) < accuracy) {
			break;
		}
	}

	return res;
}

double taylor_arcsin(double x, unsigned int members_count, double accuracy) {
	double res;
	double member;
	unsigned int i;

	if (fabs(x) > 1.0) {
		return NAN;
	}

	res = 0.0;
	member = x;

	for (i = 1; i <= members_count; i++) {
		res += member;

		member *= (x * x) * (i * i) / ((i + 1) * (i + 2));

		if (fabs(member) < accuracy) {
			break;
		}
	}

	return res;
}

double taylor_arccos(double x, unsigned int members_count, double accuracy) {
	return (PI * 0.5) - taylor_arcsin(x, members_count, accuracy);
}