#include "stdio.h"
#include "math.h"
#include <stdio.h>

// Task 1
// These fucntions are here just so I dont have to write same things all over again
void ClearKeyBuffer()
{
	int ch;
	while (ch = getchar() != '\n')
<<<<<<< HEAD
		;
=======
		;	
>>>>>>> d912c057eff5c167b5802db777b884ebf5ea1716
}

void IncorrectDataMessage(int Condition)
{
	if (Condition)
<<<<<<< HEAD
		printf("\nData is incorrect, please try again: \n \n");
=======
		printf("\nData is incorrect, please try again: \n \n");	
>>>>>>> d912c057eff5c167b5802db777b884ebf5ea1716
}


int main()
{
	int h, w, d = 0;

	// Densities
	double DSP_Dens = 750.f / 1000000.f;
	double DVP_Dens = 950.f / 1000000.f;
	double Wood_Dens = 700.f / 1000000.f;

	// Inputting Data
	int Inputing = 0;
<<<<<<< HEAD

=======
	
>>>>>>> d912c057eff5c167b5802db777b884ebf5ea1716
	// Input h
	do
	{
		printf("Input h (180 - 220): ");
		scanf("%i", &h);
		ClearKeyBuffer();
<<<<<<< HEAD

		Inputing = !((h >= 180) && (h <= 220));
		IncorrectDataMessage(Inputing);

=======
		
		Inputing = ! ((h >= 180) && (h <= 220));
		IncorrectDataMessage(Inputing);
			
>>>>>>> d912c057eff5c167b5802db777b884ebf5ea1716
	} while (Inputing);
	
	// input w
	do
	{
		printf("Input w (80 - 120): ");
		scanf("%i", &w);
		ClearKeyBuffer();
		
		Inputing = ! ((w >= 80) && (w <= 120));
		IncorrectDataMessage(Inputing);
			
	} while (Inputing);
	
	// input d
	do
	{
		printf("Input d (50 - 90): ");
		scanf("%i", &d);
		ClearKeyBuffer();
		
		Inputing = ! ((d >= 50) && (d <= 90));
		IncorrectDataMessage(Inputing);
			
	} while (Inputing);
	
	h = h * 10;
	w = w * 10;
	d = d * 10;

	// input w
	do
	{
		printf("Input w (80 - 120): ");
		scanf("%i", &w);
		ClearKeyBuffer();

		Inputing = !((w >= 80) && (w <= 120));
		IncorrectDataMessage(Inputing);

	} while (Inputing);

	// input d
	do
	{
		printf("Input d (50 - 90): ");
		scanf("%i", &d);
		ClearKeyBuffer();

		Inputing = !((d >= 50) && (d <= 90));
		IncorrectDataMessage(Inputing);

	} while (Inputing);

	h = h * 10;
	w = w * 10;
	d = d * 10;

	// Volume Calculation
	int DSP_Volume = 0;
	int DVP_Volume = 0;
	int Wood_Volume = 0;

	// Basic Volume
	DVP_Volume = h * w * 5;
	DSP_Volume = (2 * h * d * 15) + (2 * w * d * 15);
	Wood_Volume = h * w * 10;

	// Shelf Volume
	int Single_Shelf_Volume = (w - 30) * d * 15;

	int Shelf_Count = 0;
	int h_left = h;

	// Packing as much shelves as we can
	while (h_left >= 415)
	{
		Shelf_Count++;

		h_left -= 415;
	}

	// Finalizing volume calculation
	DSP_Volume = DSP_Volume + Shelf_Count * Single_Shelf_Volume;

	// Mass calculation
	double Mass = (DVP_Volume * DVP_Dens / 1000) + (DSP_Volume * DSP_Dens / 1000) + (Wood_Volume * Wood_Dens / 1000);

	// Answer print out
	printf("Mass: %lg \n", Mass);

	system("pause");

	return 0;
}



/* Task 0
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
*/
