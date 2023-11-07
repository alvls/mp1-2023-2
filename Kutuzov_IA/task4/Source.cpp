#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <time.h>

// Defining Data structure
struct Code // Represents item's unique ID
{
	int Arr[5];
};

struct ItemData // Contains all available information about the item
{
	char Name[30];

	float Cost;

	int Discount;
};

struct LibraryData // Contains all data and pointers nececery to access library
{
	int LibSize;

	struct Code* Codes;
	
	struct ItemData* Library;
};

struct BillElement // Represents items in the bill
{
	int DataID; // Not a Code! This is the index of the item in the library

	int Count;
};


// Initialize Library
struct LibraryData InitLibrary(FILE* FileP);

// Scanning procedure
void ItemScanned(struct Code Code, struct LibraryData LibData);

// Forms and prints out a bill
void FormBill(int* Bill, int BillSize, struct LibraryData LibData);

// Converting strings to codes
struct Code ConvertStrToCode(char Str[4]);

// Access data
struct ItemData GetLibraryData(struct Code Code, struct LibraryData LibData);

// Cleans up the keyboard buffer
void ClearKeyboardBuffer();

// == for codes
int CodeEqual(struct Code a, struct Code b);

// Finds code's ID in the data base
int GetDataID(struct Code Code, struct LibraryData LibData);

// Compare function for qsort
int CmpF(const void* a, const void* b);

// Picks random code from available ones
struct Code GetRandomCode(int Seed, struct LibraryData LibData);


// MAIN


int main()
{
	setlocale(LC_ALL, "rus");

	int* Bill;
	struct LibraryData LibData;

	// Opening Data File and reading Library File
	FILE* FileP;
	fopen_s(&FileP, "ItemDataBase.txt", "r");

	if (FileP == NULL)
	{
		printf("No library file located, please make sure it's in the same folder as the program!\n");

		system("pause");
		return 1;
	}

	LibData = InitLibrary(FileP);

	fclose(FileP);

	// Bill Initialization
	Bill = (int*)malloc(sizeof(int) * LibData.LibSize);


	// Scanning procedure
	printf("Input codes to scan them, input 's' to finish scanning, 'r' to add random item to the bill\nInputExample: 0001\n\n");

	int IsScanning = 1;
	int CurrentBillPosition = 0;

	while (IsScanning)
	{
		char Input[5];
		struct Code CodeInp;

		int InputingCode;
		do
		{
			printf("Scan code: ");
			scanf("%5s", Input);
			ClearKeyboardBuffer();

			if(strcmp(Input, "s") != 0)
				CodeInp = ConvertStrToCode(Input);

			InputingCode = !(strcmp(Input, "s") == 0 || strcmp(Input, "r") == 0 || GetDataID(CodeInp, LibData) != -1);

			if (InputingCode)
				printf("Invalid Code!\n\n");

		} while (InputingCode);
		

		// Exit scanning procedure
		if (strcmp(Input, "s") == 0)
			break;

		// Get random item code
		if (strcmp(Input, "r") == 0)
			CodeInp = GetRandomCode(CurrentBillPosition + 1, LibData);

		// Scan item and add it to the bill
		ItemScanned(CodeInp, LibData);
		Bill[CurrentBillPosition++] = GetDataID(CodeInp, LibData);
	}

	FormBill(Bill, CurrentBillPosition, LibData);

	system("pause");

	// Freeing allocated memory
	free(Bill);
	free(LibData.Codes);
	free(LibData.Library);

	return 0;
}


// FUNCTIONS


struct LibraryData InitLibrary(FILE* FileP)
{
	struct LibraryData LibData;

	int LibrarySize = 1;
	struct Code* Codes;
	struct ItemData* Library;
	
	char RBuffer[255];

	// Reading Library Size
	fgets(RBuffer, 255, FileP);
	sscanf(RBuffer, "%i\n", &LibrarySize);


	// Active Data Pool Initialization
	Codes = (struct Code*)malloc(sizeof(struct Code) * LibrarySize);
	Library = (struct ItemData*)malloc(sizeof(struct ItemData) * LibrarySize);

	// Reading data from the file
	for (int i = 0; i < LibrarySize; i++)
	{
		struct ItemData LData = ItemData();
		char CodeStr[5] = "0000";

		fgets(RBuffer, 255, FileP);
		sscanf(RBuffer, "%5s %s %f %i\n", CodeStr, LData.Name, &LData.Cost, &LData.Discount);

		Codes[i] = ConvertStrToCode(CodeStr);
		Library[i] = LData;
	}

	// Initializing quick access library data
	LibData.Codes = Codes;
	LibData.Library = Library;
	LibData.LibSize = LibrarySize;

	return LibData;
}


// Scanning procedure
void ItemScanned(struct Code Code, struct LibraryData LibData)
{
	struct ItemData Data = GetLibraryData(Code, LibData);

	printf("Name: %s\nBase Cost: %g\nDiscount: %i percent\nFinalCost:%g\n\n", Data.Name, Data.Cost, Data.Discount, Data.Cost - Data.Cost * Data.Discount / 100);
}


// Forms and prints out a bill
void FormBill(int* Bill, int BillSize, struct LibraryData LibData)
{
	printf("\n\n\nYOUR BILL:\n\n");

	float BaseCost = 0;
	float FinalCost = 0;

	// Sorting the bill
	qsort(Bill, BillSize, sizeof(int), CmpF);

	// Converting it so it consists only of unique elements
	struct BillElement* BillSet = (struct BillElement*)malloc(sizeof(struct BillElement) * (BillSize + 1));
	int BillSetSize = 0;

	for (int i = 0; i < BillSize; i++)
	{
		if (BillSetSize == 0 || BillSet[BillSetSize - 1].DataID != Bill[i])
		{
			BillSet[BillSetSize].DataID = Bill[i];
			BillSet[BillSetSize].Count = 1;

			BillSetSize++;
		}

		else
			BillSet[BillSetSize - 1].Count++;
	}

	// Printing out the bill
	for (int i = 0; i < BillSetSize; i++)
	{
		struct ItemData Item = LibData.Library[BillSet[i].DataID];

		printf("%s : %g rub x %i\n", Item.Name, Item.Cost, BillSet[i].Count);

		BaseCost += Item.Cost * BillSet[i].Count;
		FinalCost += (Item.Cost - Item.Cost * Item.Discount / 100) * BillSet[i].Count;
	}

	printf("\nCost: %g rub\nDiscount: %g rub\n\nFinal Cost: %g rub\n\nThank you for shoping with us!\n\n\n\n", BaseCost, BaseCost - FinalCost, FinalCost);

	// Freeing allocated memory
	free(BillSet);
}


// Converting strings to codes
struct Code ConvertStrToCode(char Str[4])
{
	struct Code Code;

	for (int i = 0; i < 4; i++)
	{
		Code.Arr[i] = Str[i] - '0';
	}

	return Code;
}

// Access data
struct ItemData GetLibraryData(struct Code Code, struct LibraryData LibData)
{
	for (int i = 0; i < LibData.LibSize; i++)
	{
		if (CodeEqual(LibData.Codes[i], Code))
			return LibData.Library[i];
	}

	return LibData.Library[0];
}


// Cleans up the keyboard buffer
void ClearKeyboardBuffer()
{
	int ch;
	while (ch = getchar() != '\n')
		;
}


// == for codes
int CodeEqual(struct Code a, struct Code b)
{
	for (int i = 0; i < 4; i++)
		if (a.Arr[i] != b.Arr[i])
			return 0;

	return 1;
}


// Finds code's ID in the data base
int GetDataID(struct Code Code, struct LibraryData LibData)
{
	for (int i = 0; i < LibData.LibSize; i++)
		if (CodeEqual(Code, LibData.Codes[i]))
			return i;

	return -1;
}


// Compare function for sorting Code's using qsort
int CmpF(const void* a, const void* b)
{
	int* A = (int*)a, * B = (int*)b;

	return (*A > *B) - (*A < *B);
}


// Picks random code from available ones
struct Code GetRandomCode(int Seed, struct LibraryData LibData)
{
	srand(time(0) * Seed);

	int Rand = rand() % LibData.LibSize;

	return LibData.Codes[Rand];
}