#include <stdio.h>
#include <math.h>
#include <complex.h>
#include <tgmath.h>
#include "TaylorMathFunctions.h"

// Commnad type enumeration
typedef enum {C_Exit, C_SelectMode, C_Continue} CommandT;

// Function pointer types
typedef double (*MathFunc_T)(double, int, int*, int);
typedef double (*MathFunc_C)(double);


// Operation mode 1 function
void Mode_1();

// Operation mode 2 funciton
void Mode_2();

// Selecting a new operation mode
void SelectMode(int* ModeOut);

// Running the selected mode
void RunMode(int Mode);

// Receiving command input from the user
CommandT ReceiveCommandInput();

// Clearing keyboard buffer
void ClearKeyboardBuffer();

// Receives function input from the user
int ReceiveFunctionInput();


//Custom c functions
double cotanh(double x);
double sqrt_1(double x);
double log_1(double x);
double cotan(double x);
double acotan(double x);


// Math function arrays
MathFunc_T Taylor_Functions[15] = {
	&Sin_T, &Cos_T, &Exp_T, &Cth_T, &Sqrt_T, &Ln_T, &Tan_T, &Cotan_T, &Arcsin_T, &Arccos_T, &Arctan_T, &Arccotan_T, &Sh_T, &Ch_T, &Th_T
};

MathFunc_C C_Functions[15] = {
	&sin, &cos, &exp, &cotanh, &sqrt_1, &log_1, &tan, &cotan, &asin, &acos, &atan,&acotan, &sinh, &cosh, &tanh
};



int main()
{
	printf("TAYLOR SERIES\n\nPossible Commands:\n  C - Continue with current mode;\n  M - Choose an operation mode;\n  Q - Exit program\n\nNote that some functions only give correct results for small enough x, \npassing in values high enough can result in incorrect values!\n\n");

	int Running = 1;
	int CurrentMode = 0;

	SelectMode(&CurrentMode);

	while (Running)
	{
		CommandT Command = ReceiveCommandInput();

		switch (Command)
		{
		case C_Exit: 
			Running = 0;
			break;

		case C_SelectMode:
			SelectMode(&CurrentMode);
			break;

		case C_Continue:
			RunMode(CurrentMode);
			break;			
		}
	}

	return 0;
}



void Mode_1()
{
	printf("\n");
	int Inputing = 1;
	int Function = ReceiveFunctionInput();

	printf("\n");

	double x = 0.f;
	int TargetAccuracy = 0;
	int N = 0;

	double Result = 0.f;
	double TargetValue = 0.f;

	printf("Input x: ");
	scanf_s("%lf", &x);
	ClearKeyboardBuffer();

	do
	{
		printf("Input Target Accuracy (Number of digits after dot: 1 - 6): ");
		scanf_s("%i", &TargetAccuracy);
		ClearKeyboardBuffer();

		Inputing = !(TargetAccuracy > 0 && TargetAccuracy < 7);
		if (Inputing)
			printf("Invalid target accuracy!\n\n");

	} while (Inputing);

	do
	{
		printf("Input N - maximum number of series elements to calculate (1 - 1000): ");
		scanf_s("%i", &N);
		ClearKeyboardBuffer();

		Inputing = !(N > 0 && N < 1001);
		if (Inputing)
			printf("Invalid N!\n\n");

	} while (Inputing);


	printf("\n");

	
	Result = Taylor_Functions[Function](x, TargetAccuracy, &N, 0);
	TargetValue = C_Functions[Function](x);

	printf("Target Value: %lf\nCalculated Approximation: %lf\nError: %lf\nNumber of calculated elements: %i\n\n\n", TargetValue, Result, Result - TargetValue, N);
}


void Mode_2()
{
	printf("\n");

	int Inputing = 1;
	int Function = ReceiveFunctionInput();

	printf("\n");

	double x = 0.f;
	int NMax = 0;

	double TargetValue = 0.f;

	printf("Input x: ");
	scanf_s("%lf", &x);
	ClearKeyboardBuffer();

	do
	{
		printf("Input NMax - maximum number of series elements to calculate (1 - 25): ");
		scanf_s("%i", &NMax);
		ClearKeyboardBuffer();

		Inputing = !(NMax > 0 && NMax < 26);
		if (Inputing)
			printf("Invalid NMax!\n\n");

	} while (Inputing);

	printf("\n");

	TargetValue = C_Functions[Function](x);
	printf("Target Value = %lf\n\n\n", TargetValue);

	printf("N        Value         Error\n\n");
	for (int N = 0; N <= NMax; N++)
	{
		int L_N = N;
		double Result = Taylor_Functions[Function](x, 0, &L_N, 1);

		printf("%-5i  %10.6lf  %10.6lf\n", N, Result, Result - TargetValue);
	}

	printf("\n\n");
}


void SelectMode(int* ModeOut)
{
	int Inputing = 1;
	int NewMode = -1;

	do
	{
		printf("\nInput Operation Mode (0 - Single Calculation, 1 - Mass calculation experiment): ");
		scanf_s("%i", &NewMode);
		ClearKeyboardBuffer();
		
		Inputing = !(NewMode == 0 || NewMode == 1);
		if (Inputing)
			printf("Invalid Operation Mode!\n\n");

	} while (Inputing);


	(*ModeOut) = NewMode;
	RunMode(NewMode);
}


void RunMode(int Mode)
{
	switch (Mode)
	{
	case 0: return Mode_1();

	case 1: return Mode_2();

	default: 
		printf("\n!ERRROR! Invalid Mode!\n");
		return;
	}
}


CommandT ReceiveCommandInput()
{
	char CommandC = '0';

	do
	{
		printf("Input Command (C, M or Q): ");
		scanf_s("%c", &CommandC);
		ClearKeyboardBuffer();
		
		switch (CommandC)
		{
		case 'Q': return C_Exit;

		case 'M': return C_SelectMode;

		case 'C': return C_Continue;

		default:
			printf("Invalid Command!\n\n");
			break;
		}

	} while (1);
}


void ClearKeyboardBuffer()
{
	int ch;
	while ((ch = getchar() != '\n') && ch != EOF)
		;
}


int ReceiveFunctionInput()
{
	int Inputing = 1;
	int Function = -1;

	do
	{
		printf("\nInput function to calculate:\n  0 - sin(x);\n  1 - cos(x);\n  2 - exp(x);\n  3 - cth(x);\n  4 - sqrt(1 + x)\n  5 - ln(1 + x);\n  6 - tan(x);\n  7 - cotan(x);\n  8 - arcsin(x);\n  9 - arccos(x);\n  10 - arcttan(x);\n  11 - arccotan(x);\n  12 - sh(x);\n  13 - ch(x);\n  14 - th(x);\n\nYour Choice: ");
		scanf_s("%i", &Function);
		ClearKeyboardBuffer();

		Inputing = !(Function >= 0 && Function <= 14);
		if (Inputing)
			printf("Invalid Function!\n\n");

	} while (Inputing);

	return Function;
}


double cotanh(double x)
{
	return 1 / tanh(x);
}

double sqrt_1(double x)
{
	return sqrt(1 + x);
}

double log_1(double x)
{
	return log(1 + x);
}

double cotan(double x)
{
	return 1 / tan(x);
}

double acotan(double x)
{
	return (PI / 2.f) - atan(x);
}
