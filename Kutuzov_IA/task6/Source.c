#include <stdio.h>
#include <math.h>
#include <complex.h>
#include <tgmath.h>
#include "TaylorMathFunctions.h"

// Commnad type enumeration
typedef enum {C_Exit, C_SelectMode, C_Continue} CommandT;


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



int main()
{
	printf("TAYLOR SERIES\n\nPossible Commands:\n  C - Continue with current mode;\n  M - Choose an operation mode;\n  Q - Exit program\n\n");

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

	do
	{
		printf("Input Target Accuracy (Number of digits after dot: 1 - 6): ");
		scanf_s("%i", &TargetAccuracy);

		Inputing = !(TargetAccuracy > 0 && TargetAccuracy < 7);
		if (Inputing)
			printf("Invalid target accuracy!\n\n");

	} while (Inputing);

	do
	{
		printf("Input N - maximum number of series elements to calculate (1 - 1000): ");
		scanf_s("%i", &N);

		Inputing = !(N > 0 && N < 1001);
		if (Inputing)
			printf("Invalid N!\n\n");

	} while (Inputing);


	printf("\n");

	switch (Function)
	{
	case 0: 
		Result = Sin_T(x, TargetAccuracy, &N, 0);
		TargetValue = sin(x);
		break;

	case 1:
		Result = Cos_T(x, TargetAccuracy, &N, 0);
		TargetValue = cos(x);
		break;

	case 2:
		Result = Exp_T(x, TargetAccuracy, &N, 0);
		TargetValue = exp(x);
		break;

	case 3:
		Result = Cth_T(x, TargetAccuracy, &N, 0);
		TargetValue = 1 / tanh(x);
		break;

	case 4:
		Result = Sqrt_T(x, TargetAccuracy, &N, 0);
		TargetValue = sqrt(1 + x);
		break;

	case 5:
		Result = Ln_T(x, TargetAccuracy, &N, 0);
		TargetValue = log(1 + x);
		break;

	case 6:
		Result = Tan_T(x, TargetAccuracy, &N, 0);
		TargetValue = tan(x);
		break;

	case 7:
		Result = Cotan_T(x, TargetAccuracy, &N, 0);
		TargetValue = 1 / tan(x);
		break;

	case 8:
		Result = Arcsin_T(x, TargetAccuracy, &N, 0);
		TargetValue = asin(x);
		break;

	case 9:
		Result = Arccos_T(x, TargetAccuracy, &N, 0);
		TargetValue = acos(x);
		break;

	case 10:
		Result = Arctan_T(x, TargetAccuracy, &N, 0);
		TargetValue = atan(x);
		break;

	case 11:
		Result = Arccotan_T(x, TargetAccuracy, &N, 0);
		TargetValue = (PI / 2.f) - atan(x);
		break;

	case 12:
		Result = Sh_T(x, TargetAccuracy, &N, 0);
		TargetValue = sinh(x);
		break;

	case 13:
		Result = Ch_T(x, TargetAccuracy, &N, 0);
		TargetValue = cosh(x);
		break;

	case 14:
		Result = Th_T(x, TargetAccuracy, &N, 0);
		TargetValue = tanh(x);
		break;
	
	default:
		printf("!ERROR! Function executing failed!\n\n");
	}

	printf("Target Value: %lf\nCalculated Approximation: %lf\nError: %lf\nNumber of calculated elements: %i\n\n\n", TargetValue, Result, Result - TargetValue, N);
	ClearKeyboardBuffer();
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


	do
	{
		printf("Input NMax - maximum number of series elements to calculate (1 - 25): ");
		scanf_s("%i", &NMax);

		Inputing = !(NMax > 0 && NMax < 26);
		if (Inputing)
			printf("Invalid NMax!\n\n");

	} while (Inputing);


	printf("\n");

	switch (Function)
	{
	case 0:
		TargetValue = sin(x);
		break;

	case 1:
		TargetValue = cos(x);
		break;

	case 2:
		TargetValue = exp(x);
		break;

	case 3:
		TargetValue = 1 / tanh(x);
		break;

	case 4:
		TargetValue = sqrt(1 + x);
		break;

	case 5:
		TargetValue = log(1 + x);
		break;

	case 6:
		TargetValue = tan(x);
		break;

	case 7:
		TargetValue = 1 / tan(x);
		break;

	case 8:
		TargetValue = asin(x);
		break;

	case 9:
		TargetValue = acos(x);
		break;

	case 10:
		TargetValue = atan(x);
		break;

	case 11:
		TargetValue = (PI / 2.f) - atan(x);
		break;

	case 12:
		TargetValue = sinh(x);
		break;

	case 13:
		TargetValue = cosh(x);
		break;

	case 14:
		TargetValue = tanh(x);
		break;

	default:
		printf("!ERROR! Function executing failed!\n\n");
	}

	printf("Target Value = %lf\n\n\n", TargetValue);

	printf("N        Value         Error\n\n");

	for (int N = 0; N <= NMax; N++)
	{
		double Result = 0.f;
		
		int L_N = N;
		switch (Function)
		{
		case 0:
			Result = Sin_T(x, 0, &L_N, 1);
			break;

		case 1:
			Result = Cos_T(x, 0, &L_N, 1);
			break;

		case 2:
			Result = Exp_T(x, 0, &L_N, 1);
			break;

		case 3:
			Result = Cth_T(x, 0, &L_N, 1);
			break;

		case 4:
			Result = Sqrt_T(x, 0, &L_N, 1);
			break;

		case 5:
			Result = Ln_T(x, 0, &L_N, 1);
			break;

		case 6:
			Result = Tan_T(x, 0, &L_N, 1);
			break;

		case 7:
			Result = Cotan_T(x, 0, &L_N, 1);
			break;

		case 8:
			Result = Arcsin_T(x, 0, &L_N, 1);
			break;

		case 9:
			Result = Arccos_T(x, 0, &L_N, 1);
			break;

		case 10:
			Result = Arctan_T(x, 0, &L_N, 1);
			break;

		case 11:
			Result = Arccotan_T(x, 0, &L_N, 1);
			break;

		case 12:
			Result = Sh_T(x, 0, &L_N, 1);
			break;

		case 13:
			Result = Ch_T(x, 0, &L_N, 1);
			break;

		case 14:
			Result = Th_T(x, 0, &L_N, 1);
			break;

		default:
			printf("!ERROR! Function executing failed!\n\n");
		}

		printf("%-5i  %10.6lf  %10.6lf\n", N, Result, Result - TargetValue);
	}

	printf("\n\n");
	ClearKeyboardBuffer();
}


void SelectMode(int* ModeOut)
{
	int Inputing = 1;
	int NewMode = -1;

	do
	{
		printf("\nInput Operation Mode (0 - Single Calculation, 1 - Mass calculation experiment): ");
		scanf_s("%i", &NewMode);
		
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
	while (ch = getchar() != '\n')
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

		Inputing = !(Function >= 0 && Function <= 14);
		if (Inputing)
			printf("Invalid Function!\n\n");

	} while (Inputing);

	return Function;
}