#include "TaylorMathFunctions.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>



double Sin_T(double x, int TargetAccuracy, int* N, int IgnoreAccuracy)
{
	double X_Eqv = x - (int)(x / 6.283185f) * 6.283185f;

	double Result = 0.f;

	int L_N = (*N);
	(*N) = 0;

	for (int n = 0; n < L_N; n++)
	{
		double Addition = (pow(-1, n) * pow(X_Eqv, 2 * n + 1)) / Factorial(2 * n + 1, 1);

		if (fabs(Addition) < pow(0.1f, TargetAccuracy) && !IgnoreAccuracy)
			break;

		Result += Addition;
		(*N)++;
	}

	return Result;
}


double Cos_T(double x, int TargetAccuracy, int* N, int IgnoreAccuracy)
{
	double X_Eqv = x - (int)(x / 6.283185f) * 6.283185f;

	double Result = 0.f;

	int L_N = (*N);
	(*N) = 0;

	for (int n = 0; n < L_N; n++)
	{
		double Addition = (pow(-1, n) * pow(X_Eqv, 2 * n)) / Factorial(2 * n, 1);

		if (fabs(Addition) < pow(0.1f, TargetAccuracy) && !IgnoreAccuracy)
			break;

		Result += Addition;
		(*N)++;
	}

	return Result;
}


double Exp_T(double x, int TargetAccuracy, int* N, int IgnoreAccuracy)
{
	double Result = 0.f;

	int L_N = (*N);
	(*N) = 0;

	for (int n = 0; n < L_N; n++)
	{
		double Addition = pow(x, n) / Factorial(n, 1);

		//printf("%lf\n", Addition);

		if (fabs(Addition) < pow(0.1f, TargetAccuracy) && !IgnoreAccuracy)
			break;

		Result += Addition;
		(*N)++;
	}

	return Result;
}


double Cth_T(double x, int TargetAccuracy, int* N, int IgnoreAccuracy)
{
	double Result = 1 / Th_T(x, TargetAccuracy, N, IgnoreAccuracy);

	return Result;

	/* COOL SOLUTION, BUT DOES NOT WORK!!!!
	double* B = (double*)malloc((*N + 1) * 2 * sizeof(double));
	for (int i = 0; i < (*N) * 2; i++)
		B[i] = 0.f;

	B[0] = 1.f;
	B[1] = 0.5f;

	double Result = 0.f;

	int L_N = (*N);
	(*N) = 0;

	for (int n = 0; n < L_N; n++)
	{
		double F = Factorial(2 * n, 1);
		if (F == INFINITY)
		{
			printf("\n!Infinity Break!\n\n");
			break;
		}

		double Addition = pow(2, 2 * n) * Bernoulli(2 * n, B) * pow(x, (2 * n) - 1) / F;

		if (fabs(Addition) < pow(0.1f, TargetAccuracy) && !IgnoreAccuracy)
			break;

		Result += Addition;
		(*N)++;
	}

	free(B);
	return Result;
	*/
}


double Sqrt_T(double x, int TargetAccuracy, int* N, int IgnoreAccuracy)
{
	double Result = 0.f;

	int L_N = (*N);
	(*N) = 0;

	for (int n = 0; n < L_N; n++)
	{
		double Addition = pow(-1, n - 1) * Factorial(2*n + 1, 2) / (Factorial(2 * n, 2) * (2 * n + 1) * (2 * n - 1)) * pow(x, n);

		if (fabs(Addition) < pow(0.1f, TargetAccuracy) && !IgnoreAccuracy)
			break;

		Result += Addition;
		(*N)++;
	}

	return Result;
}


double Ln_T(double x, int TargetAccuracy, int* N, int IgnoreAccuracy)
{
	double Result = 0.f;

	int L_N = (*N);
	(*N) = 0;

	for (int n = 1; n < L_N; n++)
	{
		double Addition = pow(-1, n - 1) * pow(x, n) / n;

		if (fabs(Addition) < pow(0.1f, TargetAccuracy) && !IgnoreAccuracy)
			break;

		Result += Addition;
		(*N)++;
	}

	return Result;
}


double Tan_T(double x, int TargetAccuracy, int* N, int IgnoreAccuracy)
{
	int L_N_1 = (*N);
	int L_N_2 = (*N);
	
	double Sin = Sin_T(x, TargetAccuracy, &L_N_1, IgnoreAccuracy);
	double Cos = Cos_T(x, TargetAccuracy, &L_N_1, IgnoreAccuracy);

	double Result = Sin / Cos;
	(*N) = L_N_1 + L_N_2;
	
	return Result;
}


double Cotan_T(double x, int TargetAccuracy, int* N, int IgnoreAccuracy)
{
	double Result = 1 / Tan_T(x, TargetAccuracy, N, IgnoreAccuracy);

	return Result;
}


double Arcsin_T(double x, int TargetAccuracy, int* N, int IgnoreAccuracy)
{
	double Result = 0.f;

	int L_N = (*N);
	(*N) = 0;

	for (int n = 0; n < L_N; n++)
	{
		double Addition = Factorial(2 * n, 1) * pow(x, 2*n + 1) / (pow(2, 2 * n) * pow(Factorial(n, 1), 2) * (2 * n + 1));

		if (fabs(Addition) < pow(0.1f, TargetAccuracy) && !IgnoreAccuracy)
			break;

		Result += Addition;
		(*N)++;
	}

	return Result;
}


double Arccos_T(double x, int TargetAccuracy, int* N, int IgnoreAccuracy)
{
	double Result = (PI / 2.f) - Arcsin_T(x, TargetAccuracy, N, IgnoreAccuracy);

	return Result;
}


double Arctan_T(double x, int TargetAccuracy, int* N, int IgnoreAccuracy)
{
	double Result = 0.f;

	int L_N = (*N);
	(*N) = 0;

	for (int n = 1; n < L_N; n++)
	{
		double Addition = pow(-1, n - 1) * pow(x, 2*n - 1) / (2 * n - 1);

		if (fabs(Addition) < pow(0.1f, TargetAccuracy) && !IgnoreAccuracy)
			break;

		Result += Addition;
		(*N)++;
	}

	return Result;
}


double Arccotan_T(double x, int TargetAccuracy, int* N, int IgnoreAccuracy)
{
	double Result = (PI / 2.f) - Arctan_T(x, TargetAccuracy, N, IgnoreAccuracy);

	return Result;
}


double Sh_T(double x, int TargetAccuracy, int* N, int IgnoreAccuracy)
{
	double Result = 0.f;

	int L_N = (*N);
	(*N) = 0;

	for (int n = 0; n < L_N; n++)
	{
		double Addition = pow(x, 2*n + 1) / Factorial(2*n + 1, 1);

		if (fabs(Addition) < pow(0.1f, TargetAccuracy) && !IgnoreAccuracy)
			break;

		Result += Addition;
		(*N)++;
	}

	return Result;
}


double Ch_T(double x, int TargetAccuracy, int* N, int IgnoreAccuracy)
{
	double Result = 0.f;

	int L_N = (*N);
	(*N) = 0;

	for (int n = 0; n < L_N; n++)
	{
		double Addition = pow(x, 2 * n) / Factorial(2 * n, 1);

		if (fabs(Addition) < pow(0.1f, TargetAccuracy) && !IgnoreAccuracy)
			break;

		Result += Addition;
		(*N)++;
	}

	return Result;
}


double Th_T(double x, int TargetAccuracy, int* N, int IgnoreAccuracy)
{
	int L_N_1 = (*N);
	int L_N_2 = (*N);

	double Sh = Sh_T(x, TargetAccuracy, &L_N_1, IgnoreAccuracy);
	double Ch = Ch_T(x, TargetAccuracy, &L_N_1, IgnoreAccuracy);

	double Result = Sh / Ch;
	(*N) = L_N_1 + L_N_2;

	return Result;
}


double Factorial(int x, int order)
{
	double Result = order;
	for (int i = 1; i <= x; i += order)
		Result *= i;

	return Result;
}


double Bernoulli(int n, double* Bs)
{
	if (n == 0)
		return 1.f;

	if (Bs[n - 1] == 0.f)
		Bernoulli(n - 1, Bs);

	double Result = 1.f;

	for (int k = 0; k < n; k++)
		Result -= Binominal(n, k) * Bs[k] / (n - k + 1);
	
	Bs[n] = Result;

	return Result;
}

double Binominal(int n, int k)
{
	return Factorial(n, 1) / (Factorial(k, 1) * Factorial(n - k, 1));
}