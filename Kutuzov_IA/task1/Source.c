#include "stdio.h"
#include "math.h"

// Define Min and Max functions
float Min(float a, float b)
{
	if (a > b)
	{
		return b;
	}

	return a;
}

float Max(float a, float b)
{
	if (a > b)
	{
		return a;
	}

	return b;
}

/////////////////////////////////////////

int main()
{
	float X1 = 0.f;
	float Y1 = 0.f;
	float R1 = 0.f;

	float X2 = 0.f;
	float Y2 = 0.f;
	float R2 = 0.f;


	printf("Input first circle data: X1 Y1 R1: ");
	scanf_s("%f %f %f", &X1, &Y1, &R1);

	printf("Input second circle data: X2 Y2 R2: ");
	scanf_s("%f %f %f", &X2, &Y2, &R2);

	// Distance calculation
	float dX = X2 - X1;
	float dY = Y2 - Y1;;

	float Distance = sqrt(dX * dX + dY * dY);

	// 1
	if (X1 == X2 && Y1 == Y2 && R1 == R2)
	{
		printf("Equal \n");
	}

	// 2
	else if (X1 == X2 && Y1 == Y2)
	{
		printf("Same Origin \n");
	}

	//3
	else if (R1 + R2 == Distance)
	{
		printf("Touching Outside \n");
	}

	//4
	else if (Distance + Min(R1, R2) == Max(R1, R2))
	{
		printf("Touching Inside \n");
	}

	//5
	else if (Distance + Min(R1, R2) < Max(R1, R2))
	{
		printf("One inside of the other \n");
	}

	//6
	else if (R1 + R2 < Distance)
	{
		printf("Do not interact \n");
	}

	//7
	else if (R1 + R2 > Distance)
	{
		printf("Intersection \n");
	}
	
	// If something unpredicted happens, print out an error	
	else
	{
		printf("Error, Help me please, its bad \n");
	}

	system("pause");
	return 0;
}