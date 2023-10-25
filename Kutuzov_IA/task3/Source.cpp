#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <windows.h>

#define N_MAX 5     // Max valid N size, should be MORE than 1 and LESS than 10



// __FUNCTION DECLARATIONS__



// Function for clearing keyboard buffer
void ClearKeyBuffer();

// Checks if a is of size n and has no repetitions
int Check(int a, int n);

// Generates random digit froam a given seed (time is already taken into account)
int GenerateRandomDigit(int seed);

// Checks if array a of size N_MAX, contains b in it's first n elements
int Contains(int n, int a[N_MAX], int b);

// Converts Number into an array containing each digit separately in reverse order. Example: 12345 -> {5, 4, 3, 2, 1}
void ConvertNumberToDataArray(int Number, int ArrayOut[N_MAX]);

// Calculates the number of "cow" and "bulls" based on the guess and the correct number of size n, returns if the numbers are equal
int GetResponse(int n, int Guess, int Number, int* cows, int* bulls);


// Windows API

enum TColor {
    BLACK, BLUE, GREEN, CYAN, RED, MAGENTA, BROWN, LIGHTGRAY,
    DARKGRAY, LIGHTBLUE, LIGHTGREEN, LIGHTCYAN, LIGHTRED,
    LIGHTMAGENTA, YELLOW, WHITE
};

int wherex(void);
int wherey(void);
COORD WhereXY(void);
void clrscr(void);
void gotoxy(int x, int y);
void textcolor(int color);
void textbackground(int color);
void textattr(int color);
void setwindow(int width, int height);
void SetWindow(SMALL_RECT rect, COORD size);
void GetWindow(SMALL_RECT* rect, COORD* size);
void HideCursor(void);
void ShowCursor(void);



// __MAIN LOGIC__

// Game logic and stuff
void Game()
{
    textcolor(WHITE);
    textbackground(RED);
    printf("!!!BULLS & COWS!!!\n\n\n");

    textbackground(BLUE);
    printf("Hello, player! This is just another guessing game called 'Bulls & Cows'! \n\nThe program will generate a random number of length 'n' with no repeating digits, your objective is to guess it out!\n");
    printf("Once you input your guess, the program will tell you how many numbers in your guess are in correct positions - Bulls,\nand how many of them are just present in the number (not counting bulls) - Cows.\n");
    printf("Use this information to correct your guess and try beating the game with the minimum ammount of attempts!\n\nIf you think you had enough of this game, just type in '-1' to give up\n\n\n");
    printf("Good luck playing! \n\n\n");

    textbackground(BLACK);

    // Inputing n
    int n, inp = 0;
    do
    {
        printf("Input n (2 - %i): ", N_MAX);
        scanf_s("%i", &n);
        ClearKeyBuffer();

        inp = !(n >= 2 && n <= N_MAX);
        if (inp)
            printf("Incorrect n\n\n");

    } while (inp);


    // Generating random number of size n with no repetitions
    int UsedDigits[10] = { 0 }; // Used numbers
    int RandomNum = 0; // Resulting number


    for (int i = 0; i < n; i++)
    {
        int InnerSeed = 1;
        int CurrentDigit = -1;

        // A loop for generating digits wiht no repetitions
        // The first iteration is triggered in any case, if the number is already used or if the first (left to rgiht) digit is zero, it continues
        while ((CurrentDigit == -1 || UsedDigits[CurrentDigit] == 1) || (i == n - 1 && CurrentDigit == 0))
        {
            CurrentDigit = GenerateRandomDigit((i + 1) * InnerSeed);
            InnerSeed++;
        }

        UsedDigits[CurrentDigit] = 1; // Marking the digit as used
        RandomNum += CurrentDigit * pow(10, i); // Adding the nuber to its position
    }

    textcolor(YELLOW);
    printf("\nThe number is ready, now try to guess it!\n\n", n);
    textcolor(WHITE);

    // Game loop
    int Attempts = 0;

    int Playing = 1;
    int GaveUp = 0;

    while (Playing && !GaveUp)
    {
        int Guess = 0, Cows = 0, Bulls = 0;

        // Receiving input
        do
        {
            printf("Input your guess %i digits, no repetitions: \n", n);
            scanf_s("%i", &Guess);
            ClearKeyBuffer();

            GaveUp = Guess == -1;

            inp = !(Check(Guess, n) || GaveUp);
            if (inp)
                printf("Incorrect guess\n\n");

        } while (inp);

        // Handling giving up
        if (GaveUp)
            continue;

        // Updating play state
        Attempts++;

        Playing = !GetResponse(n, Guess, RandomNum, &Cows, &Bulls); // Wining condition

        // Outputting info to the player
        if (Playing)
            printf("Cows: %i, Bulls: %i\n\n", Cows, Bulls);
    }

    // Final messages
    if (GaveUp)
        printf("\n\nYou gave up, haha, it was %i\n\n", RandomNum);

    else
        printf("\n\nNice! It took you %i attempts to figure out!\n\n", Attempts);


}


// Main Function
int main()
{
    int ShouldRun = 1;
    while (ShouldRun)
    {
        Game();

        // Cycle option

        textbackground(BLUE);
        printf("To continue playing type: 'p'\n");
        printf("To quit game type: 'q'");
        textbackground(BLACK);

        char CycleResponse = ' ';
        int inp;

        textcolor(YELLOW);
        do
        {
            printf("\n\nYour choice: ");
            scanf_s("%c", &CycleResponse);
            ClearKeyBuffer();

            inp = !(CycleResponse == 'p' || CycleResponse == 'q');
            if (inp)
                printf("There is no such option");

        } while (inp);

        
        if (CycleResponse == 'q')
            ShouldRun = 0;

        else
            clrscr();

    }
 
    return 0;
}




// __FUNCTION IMPLEMENTATIONS__



// Function for clearing keyboard buffer
void ClearKeyBuffer()
{
    int ch;
    while (ch = getchar() != '\n')
        ;
}


// Checks if a is of size n and has no repetitions
int Check(int a, int n)
{
    int d[10] = { 0 }; // Array containing the count of each digit in the number
    int ac = a; // Copy of the number
    int Result = 1; // Result: 0 - has repetions, 1 - has no repetitions
    int Num = 0; // Size counter of the nubmer

    while (ac > 0 && Result)
    {
        if (d[ac % 10] == 1) // If the number has already been used then the number has repetitions
            Result = 0;

        Num++;
        d[ac % 10] = 1; // Marking the number as used
        ac /= 10;
    }

    return Result && Num == n;
}


// Generates random digit froam a given seed (time is already taken into account)
int GenerateRandomDigit(int seed)
{
    srand(seed * time(0));
    return rand() % 10;
}


// Checks if array a of size N_MAX, contains b in it's first n elements
int Contains(int n, int a[N_MAX], int b)
{
    for (int i = 0; i < n; i++)
    {
        if (a[i] == b)
            return 1;
    }

    return 0;
}


// Converts Number into an array containing each digit separately in reverse order. Example: 12345 -> {5, 4, 3, 2, 1}
void ConvertNumberToDataArray(int Number, int ArrayOut[N_MAX])
{
    int LNumber = Number;

    int i = 0;

    while (LNumber > 0)
    {
        ArrayOut[i] = LNumber % 10;
        LNumber /= 10;

        i++;
    }
}


// Calculates the number of "cow" and "bulls" based on the guess and the correct number of size n, returns if the numbers are equal
int GetResponse(int n, int Guess, int Number, int* cows, int* bulls)
{
    // Declaring Data arrays
    int Guess_D[N_MAX] = { 0 };
    int Number_D[N_MAX] = { 0 };

    // Filling up data arrays
    ConvertNumberToDataArray(Guess, Guess_D);
    ConvertNumberToDataArray(Number, Number_D);

    for (int i = 0; i < n; i++)
    {
        if (Guess_D[i] == Number_D[i]) // If the elements are equal, its a 'bull'
        {
            (*bulls)++;
        }

        else if (Contains(n, Number_D, Guess_D[i])) // Else if the the digit is present in the Number, its a 'cow'
        {
            (*cows)++;
        }
    }

    return Guess == Number; // Return value is the wining condition
}





// __FUNCTIONS FOR WINDOWS API__





int wherex(void)
{
    HANDLE Console = GetStdHandle(STD_OUTPUT_HANDLE);
    if (!Console)
        return -1;

    CONSOLE_SCREEN_BUFFER_INFO buf;

    GetConsoleScreenBufferInfo(Console, &buf);
    return buf.dwCursorPosition.X;
}

//-----------------------------------------------------------------------------
int wherey(void)
{
    HANDLE Console = GetStdHandle(STD_OUTPUT_HANDLE);
    if (!Console)
        return -1;

    CONSOLE_SCREEN_BUFFER_INFO buf;

    GetConsoleScreenBufferInfo(Console, &buf);
    return buf.dwCursorPosition.Y;
}

//-----------------------------------------------------------------------------
COORD WhereXY(void)
{
    HANDLE Console = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos = { -1, -1 };
    if (!Console)
        return pos;

    CONSOLE_SCREEN_BUFFER_INFO buf;

    GetConsoleScreenBufferInfo(Console, &buf);
    return buf.dwCursorPosition;
}

//-----------------------------------------------------------------------------
void clrscr(void)
{
    HANDLE Console = GetStdHandle(STD_OUTPUT_HANDLE);
    if (!Console)
        return;

    CONSOLE_SCREEN_BUFFER_INFO buf;
    GetConsoleScreenBufferInfo(Console, &buf);

    WORD Attr;
    DWORD Count;
    COORD pos = buf.dwCursorPosition;
    ReadConsoleOutputAttribute(Console, &Attr, 1, pos, &Count);

    int col = Attr;
    int width = buf.dwSize.X;
    int height = buf.dwSize.Y;

    COORD zpos;
    zpos.X = 0;
    zpos.Y = 0;
    SetConsoleCursorPosition(Console, zpos);

    FillConsoleOutputAttribute(Console, col, width * height, zpos, &Count);
    FillConsoleOutputCharacter(Console, ' ', width * height, zpos, &Count);
}

//-----------------------------------------------------------------------------
void gotoxy(int x, int y)
{
    HANDLE Console = GetStdHandle(STD_OUTPUT_HANDLE);
    if (!Console)
        return;

    COORD pos;
    pos.X = x;
    pos.Y = y;

    SetConsoleCursorPosition(Console, pos);
}

//-----------------------------------------------------------------------------
void textcolor(int color)
{
    HANDLE Console = GetStdHandle(STD_OUTPUT_HANDLE);
    if (!Console)
        return;

    CONSOLE_SCREEN_BUFFER_INFO buf;
    GetConsoleScreenBufferInfo(Console, &buf);

    WORD Attr;
    DWORD Count;
    COORD pos = buf.dwCursorPosition;
    ReadConsoleOutputAttribute(Console, &Attr, 1, pos, &Count);

    int bk_col = Attr / 16;
    int col = color % 16;
    col = col + bk_col * 16;

    SetConsoleTextAttribute(Console, col);

    char ch;
    pos = WhereXY();
    ReadConsoleOutputCharacter(Console, &ch, 1, pos, &Count);
    printf("%c", ch);
    gotoxy(pos.X, pos.Y);
}

//-----------------------------------------------------------------------------
void textbackground(int color)
{
    HANDLE Console = GetStdHandle(STD_OUTPUT_HANDLE);
    if (!Console)
        return;

    CONSOLE_SCREEN_BUFFER_INFO buf;
    GetConsoleScreenBufferInfo(Console, &buf);

    WORD Attr;
    DWORD Count;
    COORD pos = buf.dwCursorPosition;
    ReadConsoleOutputAttribute(Console, &Attr, 1, pos, &Count);

    int text_col = Attr % 16;
    int col = color % 16;
    col = color * 16 + text_col;

    SetConsoleTextAttribute(Console, col);

    char ch;
    pos = WhereXY();
    ReadConsoleOutputCharacter(Console, &ch, 1, pos, &Count);
    printf("%c", ch);
    gotoxy(pos.X, pos.Y);
}

//-----------------------------------------------------------------------------
void textattr(int color)
{
    HANDLE Console = GetStdHandle(STD_OUTPUT_HANDLE);
    if (!Console)
        return;

    SetConsoleTextAttribute(Console, color);

    DWORD Count;
    char ch;
    COORD pos = WhereXY();
    ReadConsoleOutputCharacter(Console, &ch, 1, pos, &Count);
    printf("%c", ch);
    gotoxy(pos.X, pos.Y);
}

//-----------------------------------------------------------------------------
void setwindow(int width, int height)
{
    HANDLE Console = GetStdHandle(STD_OUTPUT_HANDLE);
    if (!Console)
        return;

    SMALL_RECT rect;
    rect.Left = 0;
    rect.Right = width - 1;
    rect.Top = 0;
    rect.Bottom = height - 1;
    COORD size;
    size.X = width;
    size.Y = height;
    SetConsoleWindowInfo(Console, true, &rect);
    //  printf("%d %d %d %d", rect.Left, rect.Top, rect.Right, rect.Bottom);
    SetConsoleScreenBufferSize(Console, size);
    //  printf("%d %d", size.X, size.Y);
}

//-----------------------------------------------------------------------------
void SetWindow(SMALL_RECT rect, COORD size)
{
    HANDLE Console = GetStdHandle(STD_OUTPUT_HANDLE);
    if (!Console)
        return;

    SetConsoleScreenBufferSize(Console, size);
    SetConsoleWindowInfo(Console, true, &rect);
}

//-----------------------------------------------------------------------------
void GetWindow(SMALL_RECT* rect, COORD* size)
{
    HANDLE Console = GetStdHandle(STD_OUTPUT_HANDLE);
    if (!Console)
        return;

    CONSOLE_SCREEN_BUFFER_INFO buf;
    GetConsoleScreenBufferInfo(Console, &buf);

    *rect = buf.srWindow;
    size->X = buf.dwSize.X;
    size->Y = buf.dwSize.Y;
}

//-----------------------------------------------------------------------------
void HideCursor(void)
{
    HANDLE Console = GetStdHandle(STD_OUTPUT_HANDLE);
    if (!Console)
        return;

    CONSOLE_CURSOR_INFO buf;
    GetConsoleCursorInfo(Console, &buf);
    buf.bVisible = false;
    SetConsoleCursorInfo(Console, &buf);
}

//-----------------------------------------------------------------------------
void ShowCursor(void)
{
    HANDLE Console = GetStdHandle(STD_OUTPUT_HANDLE);
    if (!Console)
        return;

    CONSOLE_CURSOR_INFO buf;
    GetConsoleCursorInfo(Console, &buf);
    buf.bVisible = true;
    SetConsoleCursorInfo(Console, &buf);
}