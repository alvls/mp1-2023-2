#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

// Function for clearing keyboard buffer
void ClearKeyBuffer()
{
	int ch;
	while (ch = getchar() != '\n')
		;
}


// Mode 1 Implementation
void Mode_1()
{
	printf("\n \nI have generated a random number (0 - 1000), try guessing what it is! \n");
	// This was a lie, because random number generation comes after this message

	// Generating random number (0 - 1000)
	srand(time(0));
	float NumberPercent = (float)rand() / (float)RAND_MAX;
	int Number = NumberPercent * 1000.f;

	int Attempts = 0;

	// Game cycle
	while (1)
	{
		int Guess = 0;

		// Gettting input from player
		printf("Input your guess: ");
		scanf_s("%i", &Guess);
		ClearKeyBuffer();

		Attempts += 1;

		// Win condition
		if (Guess == Number)
		{
			if (Attempts == 1)
				printf("\nCorrect! First try!");

			else
				printf(" \nCorrect! It took you %i attempts!", Attempts);

			return;
		}

		// Lower / Higher condition
		if (Guess > Number)
			printf("Lower \n \n");

		if (Guess < Number)
			printf("Higher \n \n");
	}
}


// Mode 2 Implementation

//Check function used to get response from the player
int CheckMode_2(int a)
{
	// Getting input
	char Response = 0;
	printf("\nMy guess is: %i \n Please, respond with >, <, =: 	", a);
	scanf_s("%c", &Response);
	ClearKeyBuffer();

	// Returning codes assigned to possible player responses
	if (Response == '=')
		return 0; // 0 is the winning codition

	if (Response == '<')
		return 1; // 1 tells the program that it should try a smaller number

	if (Response == '>')
		return 2; // 2 tells it to try a bigger number

	// If the response isn`t valid it returns -1
	return -1;
}


// Searching algorithms (Extracted into function for easy replacement)
// Returns a new a value
int Acceleration_Search(int a, int Response, int* LastResponse, int* Count_LastResponse)
{
	// Calculating next offset
		// The program starts to offset numbers faster the more identical responses you give to it
	int Offset = 1;

	// If current response is the same as the previous one
	if (Response == (*LastResponse))
	{
		// Making sure that first few offsets are 1
		int Count = (*Count_LastResponse) - 2;
		if (Count < 0)
		{
			Count = 0;
		}

		// Offset has exponential acceleration to make it more efficient
		Offset *= (int)powf(Count + 1, 2.f);

		(*Count_LastResponse) ++;
	}

	// In case the response is different from the previous one we reset the counter and update last response
	else
	{
		(*Count_LastResponse) = 0;
		(*LastResponse) = Response;
	}

	// Offsetting "a" based on player's response
	if (Response == 1)
		return a - Offset;

	return a + Offset;
}


// Binary Search Algorithm
int BinarySearch(int a, int Response, int* BottomValue, int* TopValue)
{
	if (Response == 1 && a < (*TopValue)) // Updates top border if necessary
		(*TopValue) = a;

	else if (Response == 2 && a > (*BottomValue)) // Updates bottom border if necessary
		(*BottomValue) = a;

	return ((*BottomValue) + (*TopValue)) / 2; // Restuns the middle value
}


// Actual processing of Mode 2
void Mode_2()
{
	printf("\n \nThink of a number from 0 to 999 and tell the program if it's guesses are correct \n \n");

	int SearchALG = 1; // 0 - Acceleration; 1 - Binary
	int Number, Inp = 0;

	do
	{
		printf("Input desired search algoritm (0 - Acceleration Search, 1 - Binary Search): ");
		scanf_s("%i", &SearchALG);
		ClearKeyBuffer();

		Inp = !(SearchALG == 0 || SearchALG == 1);
		if (Inp)
			printf("\nIncorrect Search Algoritm! \n \n");

	} while (Inp);

	// Getting player's number (don't really know why, but its required in the task)
	do
	{
		printf("\nInput your number here (security purposes): ");
		scanf_s("%i", &Number);
		ClearKeyBuffer();

		Inp = !(Number >= 0 && Number < 1000);
		if (Inp)
			printf("Your number is incorrect, try a different one! \n \n");

	} while (Inp);

	int a = 500;
	int Attempts = 0;

	// Acceleration search values
	int LastResponse = 0;
	int Count_LastResponse = 0;

	// Binary search values
	int BottomValue = 0;
	int TopValue = 1000;

	// Game cycle
	while (1)
	{
		// Getting player response from current a (initially - 500)
		int Response = CheckMode_2(a);

		// Invalid response handling
		if (Response == -1)
			continue;

		Attempts++;

		// Win condition
		if (Response == 0 || a == Number)
		{
			if (a == Number)
			{
				if (Response != 0)
					printf("\nDon't lie to me! I know its the right number! It took me %i attempts", Attempts);

				else
					printf(" \nFinally! It took me %i attempts!", Attempts);

				return;
			}

			else
			{
				printf("\nI have a feeling that its not the right number...");
				Attempts--;
				continue;
			}
		}

		// Running search algorithm

		// Acceleration Search (My algorithm)
		if (SearchALG == 0)
			a = Acceleration_Search(a, Response, &LastResponse, &Count_LastResponse);

		// Binary Search
		else if (SearchALG == 1)
			a = BinarySearch(a, Response, &BottomValue, &TopValue);

		// Space reserved for other search algorithms


		// Limiting range to (0 - 999)
		// Though it can work very well with bigger numbers (or even negative ones)
		if (a < 0)
			a = 0;

		else if (a > 999)
			a = 999;
	}
}


// Main logic
int main()
{
	int Mode = 0;

	int Inputing = 0;

	// Getting mode from the player
	do
	{
		printf("Input Mode (1 or 2): ");
		scanf_s("%i", &Mode);
		ClearKeyBuffer();

		Inputing = !(Mode == 1 || Mode == 2);
		if (Inputing)
			printf("Incorrect mode \n \n");

	} while (Inputing);


	// Switching to the chosen mode

	if (Mode == 1)
		Mode_1();

	else
		Mode_2();

	printf("\n \nProgram finished, to continue playing please restart \n \n");
	system("pause");

	return 0;
}
