#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>  
#include <stdlib.h>  
#include <io.h>  
#include <time.h>  
#include <string.h>
#include <locale.h>
#include <omp.h>

#define MAX_FILES_PER_PAGE 600
#define DIRECTORY_SIZE 1000
#define COUTNSORT_MAXFILESIZE 1000000


// Possible commands
typedef
enum {Skip, Exit, ODir, OFile, Back, Conf, NPage, PPage, Help} CommandType;


// User Settings structure
typedef
struct
{
    int CompareMode;

    int SortAlgorithm;

    int ReverseOrder;

    int FilesPerPage;

} Settings;


// Receives user's input
int UserInput();

// Finds files in the given directory
void FindFilesInDirectory(char Dir[DIRECTORY_SIZE], struct _finddata_t* FilesOut, int* CountOut, int Page, Settings UserSettings);

// Command function for opening a directory
void OpenDirectory(struct _finddata_t* FoundFiles, int* FoundFilesCount, char* Directory, int UseInputDirectory, int* Page, Settings UserSettings);

// Commnad function for opening subfolder's directory
void OpenFile(struct _finddata_t* FoundFiles, int* FoundFilesCount, char* Directory, int* Page, Settings UserSettings);

// Command function for going back (up the file tree)
void GoBack(struct _finddata_t* FoundFiles, int* FoundFilesCount, char* Directory, int* Page, Settings UserSettings);

// Command function for opening user settings
void OpenSettings(Settings* UserSettings);

// Command function for navigating file pages
void OffsetPage(int Offset, int* Page, struct _finddata_t* FoundFiles, int* FoundFilesCount, char* Directory, Settings UserSettings);

// Checks if the file is a folder
int IsFolder(struct _finddata_t File);

// Compare functions used for sorting algorithms
int CompareFiles(struct _finddata_t FileA, struct _finddata_t FileB, int CompareMode);

// Sort Algorithms
void BubbleSort(struct _finddata_t* Files, int Size, Settings UserSettings);
void SelectSort(struct _finddata_t* Files, int Size, Settings UserSettings);
void InsertSort(struct _finddata_t* Files, int Size, Settings UserSettings);
void MergeSort(struct _finddata_t* Files, int LB, int UB, Settings UserSettings);
void Merge(struct _finddata_t* Files, int LB, int Split, int UB, Settings UserSettings);
void QuickSort(struct _finddata_t* Files, int Size, Settings UserSettings);
void ShellSort(struct _finddata_t* Files, int Size, Settings UserSettings);
int Increment(long Inc[], int Size);
void CountSort(struct _finddata_t* Files, int Size, Settings UserSettings);

// Calls user's selected sorting function
void SortFiles(struct _finddata_t* Files, int Size, Settings UserSettings);

// Cleans up the keyboard buffer
void ClearKeyboardBuffer();



int main(void)
{
    printf("FILE BROWSER PROTOTYPE\n\n\Please, use single slashes for paths (Example: F:/Video/Footage/OBS)\n\nAvailable Commands:\nO - open directory;\nF - open folder by it's id in the current directory;\nB - go back (up the file tree);\nN - next page;\nP - previous page;\nS - open settings;\nQ - exit the program\n\n");

    setlocale(0, "Rus");

    struct _finddata_t CurrentFiles[MAX_FILES_PER_PAGE];
    int CurrentFilesCount = 0;
    char CurrentDirectory[DIRECTORY_SIZE];
    int CurrentPage = 0;
    Settings UserSettings;

    UserSettings.FilesPerPage = 30;
    UserSettings.CompareMode = 0;
    UserSettings.SortAlgorithm = 0;
    UserSettings.ReverseOrder = 0;

    // Commands Handling
    int CurrentCommand = -1;
    do
    {
        CurrentCommand = UserInput();

        switch (CurrentCommand)
        {
        case Exit:
            break;
        
        case ODir: OpenDirectory(CurrentFiles, &CurrentFilesCount, CurrentDirectory, 0, &CurrentPage, UserSettings);
            break;

        case OFile: OpenFile(CurrentFiles, &CurrentFilesCount, CurrentDirectory, &CurrentPage, UserSettings);
            break;
        
        case Back: GoBack(CurrentFiles, &CurrentFilesCount, &CurrentPage, CurrentDirectory, UserSettings);
            break;

        case Conf: OpenSettings(&UserSettings);
            break;

        case NPage: OffsetPage(1, &CurrentPage, CurrentFiles, &CurrentFilesCount, CurrentDirectory, UserSettings);
            break;

        case PPage: OffsetPage(-1, &CurrentPage, CurrentFiles, &CurrentFilesCount, CurrentDirectory, UserSettings);
            break;

        case Help: printf("\nAvailable Commands:\nO - open directory;\nF - open folder by it's id in the current directory;\nB - go back (up the file tree);\nN - next page;\nP - previous page;\nS - open settings;\nQ - exit the program\n\n");
            break;

        default: 
            CurrentCommand = -1;
            printf("Command unidentified!");
            break;
        }

    } while (CurrentCommand != Exit);

    system("pause");
    return 0;
}


// Receives user's input
int UserInput()
{
    char CommandC;
    int Inputing = 1;

    do
    {
        printf("\nInput command (O, F, B, N, P, S, Q or H - Help): ");
        scanf_s("%c", &CommandC);
        ClearKeyboardBuffer();

        Inputing = 0;
        switch (CommandC)
        {
            case 'Q': return Exit;

            case 'O': return ODir;

            case 'F': return OFile;

            case 'B': return Back;

            case 'S': return Conf;

            case 'N': return NPage;

            case 'P': return PPage;

            case 'H': return Help;
        }

        if (Inputing)
            printf("Invalid Command!\n");

    } while (Inputing);
}


// Finds files in the given directory
void FindFilesInDirectory(char Dir[DIRECTORY_SIZE], struct _finddata_t* FilesOut, int* CountOut, int Page, Settings UserSettings)
{
    intptr_t hFile;

    if ((hFile = _findfirst(Dir, &FilesOut[0])) == -1)
    {
        printf("No files in %s !\n", Dir);
        *CountOut = 0;
        return;
    }

    *CountOut = -1 - Page * UserSettings.FilesPerPage; // To ignore first 2 files, cause the first one is the directory and the other one idk...  + handling previous pages

    while (*CountOut < MAX_FILES_PER_PAGE && *CountOut < UserSettings.FilesPerPage && _findnext(hFile, &FilesOut[*CountOut > 0 ? *CountOut : 0]) == 0)
        (*CountOut)++;
}


// Command function for opening a directory
void OpenDirectory(struct _finddata_t* FoundFiles, int* FoundFilesCount, char* Directory, int UseInputDirectory, int* Page, Settings UserSettings)
{
    char LDirectory[500];
    if (!UseInputDirectory)
    {
        printf("Enter Directory: \n");
        scanf("%s", LDirectory);
        ClearKeyboardBuffer();

        *Page = 0;

        strcpy(Directory, LDirectory);
    }

    else
        strcpy(LDirectory, Directory);

    strcat(LDirectory, "/*.*");

    FindFilesInDirectory(LDirectory, FoundFiles, FoundFilesCount, *Page, UserSettings);

    // Sorting
    double start = omp_get_wtime();
    SortFiles(FoundFiles, *FoundFilesCount, UserSettings);

    double SortTime = omp_get_wtime() - start;
    
    if (*FoundFilesCount > 0)
    {
        printf("\n\nOpening Directory:\n%-49s SortT: %lf\n\n", Directory, SortTime);
        printf("ID  NAME %-27s SIZE %-7s TIME WRITE\n\n", " ", " ");
    }

    else if (*Page > 0)
        printf("\nEMPTY PAGE\n\n");

    for (int i = 0; i < *FoundFilesCount; i++)
    {
        char TimeWrite[30];
        ctime_s(TimeWrite, _countof(TimeWrite), &FoundFiles[i].time_write);
        printf("%-3i : %-30.30s : %-10lu : %.24s\n", i + 1, FoundFiles[i].name, FoundFiles[i].size, TimeWrite);
    }

    if (*FoundFilesCount > 0)
        printf("PAGE: %i\n", *Page + 1);

    printf("\n");
}


// Command function for opening subfolder's directory
void OpenFile(struct _finddata_t* FoundFiles, int* FoundFilesCount, char* Directory, int* Page, Settings UserSettings)
{
    if (*FoundFilesCount == 0)
    {
        printf("No files in this directory!\n");
        return;
    }

    int FileID = 0;
    int Inputing = 0;

    do
    {
        printf("Enter file ID (0 to cancel): ");
        scanf("%i", &FileID);
        ClearKeyboardBuffer();

        Inputing = !(FileID > -1 && FileID < (*FoundFilesCount) + 1);

        if (Inputing)
            printf("Incorrect File ID!\n\n");

    } while (Inputing);

    if (FileID == 0)
        return;

    if (IsFolder(FoundFiles[FileID - 1]))
    {
        char NewDirectory[DIRECTORY_SIZE];
        strcpy(NewDirectory, Directory);

        strcat(NewDirectory, "/");
        strcat(NewDirectory, FoundFiles[FileID - 1].name);

        strcpy(Directory, NewDirectory);

        *Page = 0;
        OpenDirectory(FoundFiles, FoundFilesCount, NewDirectory, 1, Page, UserSettings);

        printf("\n\n");
    }

    else
        printf("File %s isn't a folder!\n", FoundFiles[FileID - 1].name);
}


// Command function for going back (up the file tree)
void GoBack(struct _finddata_t* FoundFiles, int* FoundFilesCount, int* Page, char* Directory, Settings UserSettings)
{
    int DirLen = 0;
    while (Directory[DirLen++] != 0)
        ;

    int j = DirLen;
    while (j > 0)
    {
        j--;

        if (Directory[j] == '/')
            break;
    }

    if (j == 0)
    {
        printf("\nCan not go back!\n");
        return;
    }
   
    Directory[j] = '\0';
    *Page = 0;
    OpenDirectory(FoundFiles, FoundFilesCount, Directory, 1, Page, UserSettings);

    printf("\n\n");
}


// Command function for opening user settings
void OpenSettings(Settings* UserSettings)
{
    printf("\nUSER SETTINGS\n\nChoose what you want to change:\n1 - Files per page;\n2 - Sorting mode\n3 - Sorting order\n4 - Sorting algorithm;\n\n0 - Exit\n\nYour Choice: ");

    int Option = 0;
    int NewValue = 0;

    do
    {
        int Inputing = 0;
        do
        {
            scanf("%i", &Option);
            ClearKeyboardBuffer();

            Inputing = !(Option > -1 && Option < 5);

            if (Inputing)
                printf("No such option!\n");

        } while (Inputing);


        switch (Option)
        {
            case 0:
                break;
            
            case 1:
                NewValue = 1;
                do
                {
                    printf("\nEnter new Files Per Page value (1 - %i): ", MAX_FILES_PER_PAGE);

                    scanf("%i", &NewValue);
                    ClearKeyboardBuffer();

                    Inputing = !(NewValue > 0 && NewValue < MAX_FILES_PER_PAGE + 1);

                    if (Inputing)
                        printf("Incorrect value!\n");

                } while (Inputing);

                UserSettings->FilesPerPage = NewValue;

                printf("\n");
                break;

            case 2:
                printf("\nChoose Sorting mode: \n0 - Size;\n1 - Name;\n2 - Time Create;\n3 - Time Write;\n4 - Time Access\n\n");

                NewValue = 0;
                do
                {
                    printf("Your choice: ");

                    scanf("%i", &NewValue);
                    ClearKeyboardBuffer();

                    Inputing = !(NewValue > -1 && NewValue < 5);

                    if (Inputing)
                        printf("Incorrect sorting mode!\n");

                } while (Inputing);

                UserSettings->CompareMode = NewValue;

                printf("\n");
                break;

            case 3:
                printf("\nChoose Sorting Order: \n0 - Ascending;\n1 - Descending\n\n");

                NewValue = 0;
                do
                {
                    printf("Your choice: ");

                    scanf("%i", &NewValue);
                    ClearKeyboardBuffer();

                    Inputing = !(NewValue > -1 && NewValue < 2);

                    if (Inputing)
                        printf("Incorrect sorting order!\n");

                } while (Inputing);

                UserSettings->ReverseOrder = NewValue;

                printf("\n");
                break;

            case 4:
                printf("\nChoose Sorting Algorithm: \n0 - Bubble Sort;\n1 - Select Sort;\n2 - Insert Sort;\n3 - Merge Sort;\n4 - Quick Sort;\n5 - Shell Sort;\n6 - Count Sort (Size only, Size <= %i, otherwise defaults to Quick Sort)\n\n", COUTNSORT_MAXFILESIZE);

                NewValue = 0;
                do
                {
                    printf("Your choice: ");

                    scanf("%i", &NewValue);
                    ClearKeyboardBuffer();

                    Inputing = !(NewValue > -1 && NewValue < 7);

                    if (Inputing)
                        printf("Incorrect sorting algoritm!\n");

                } while (Inputing);

                UserSettings->SortAlgorithm = NewValue;

                printf("\n");
                break;
        }

        if (Option != 0)
            printf("Good! Anything else (1, 2, 3, 4 or 0): ");
    } while (Option != 0);

    printf("\n\n");
}


// Command function for navigating file pages
void OffsetPage(int Offset, int* Page, struct _finddata_t* FoundFiles, int* FoundFilesCount, char* Directory, Settings UserSettings)
{
    if (*Page + Offset >= 0 && (Offset < 0 || *FoundFilesCount == UserSettings.FilesPerPage))
    {
        *Page += Offset;

        printf("\n");
        OpenDirectory(FoundFiles, FoundFilesCount, Directory, 1, Page, UserSettings);
    }
}


// Checks if the file is a folder
int IsFolder(struct _finddata_t File)
{
    int Ans = strstr(File.name, ".") == NULL;

    return Ans;
}


int CompareFiles(struct _finddata_t FileA, struct _finddata_t FileB, int CompareMode)
{
    switch (CompareMode)
    {
    case 0:
        return FileA.size > FileB.size;

    case 1:
        return strcmp(FileA.name, FileB.name) > 0;

    case 2:
        return FileA.time_create > FileB.time_create;

    case 3:
        return FileA.time_write > FileB.time_write;

    case 4:
        return FileA.time_access > FileB.time_access;
    }
}

// Sort Algorithms
void BubbleSort(struct _finddata_t* Files, int Size, Settings UserSettings)
{
    for (int i = 0; i < Size; i++)
        for (int j = Size - 1; j > i; j--)
            if (CompareFiles(Files[j - 1], Files[j], UserSettings.CompareMode) == !UserSettings.ReverseOrder)
            {
                struct _finddata_t x = Files[j - 1];
                Files[j - 1] = Files[j];
                Files[j] = x;
            }
}

void SelectSort(struct _finddata_t* Files, int Size, Settings UserSettings)
{
    for (int i = 0; i < Size; i++)
    {
        int k = i;
        struct _finddata_t x = Files[i];

        for (int j = i + 1; j < Size; j++)
            if (CompareFiles(x, Files[j], UserSettings.CompareMode) == !UserSettings.ReverseOrder)
            {
                k = j;
                x = Files[j];
            }

        Files[k] = Files[i];
        Files[i] = x;
    }
}

void InsertSort(struct _finddata_t* Files, int Size, Settings UserSettings)
{
    for (int i = 0; i < Size; i++)
    {
        struct _finddata_t x = Files[i];
        int j;

        for (j = i - 1; j >= 0 && (CompareFiles(Files[j], x, UserSettings.CompareMode) == !UserSettings.ReverseOrder); j--)
            Files[j + 1] = Files[j];

        Files[j + 1] = x;
    }
}


void MergeSort(struct _finddata_t* Files, int LB, int UB, Settings UserSettings)
{
    if (LB < UB)
    {
        int Split = (LB + UB) / 2;

        MergeSort(Files, LB, Split, UserSettings);
        MergeSort(Files, Split + 1, UB, UserSettings);
        Merge(Files, LB, Split, UB, UserSettings);
    }
}


void Merge(struct _finddata_t* Files, int LB, int Split, int UB, Settings UserSettings)
{
    int Pos1 = LB;
    int Pos2 = Split + 1;
    int Pos3 = 0;

    struct _finddata_t* Temp = (struct _finddata_t*)malloc(sizeof(struct _finddata_t) * (UB - LB + 1));

    while (Pos1 <= Split && Pos2 <= UB)
    {
        if (CompareFiles(Files[Pos2], Files[Pos1], UserSettings.CompareMode) == !UserSettings.ReverseOrder)
            Temp[Pos3++] = Files[Pos1++];

        else
            Temp[Pos3++] = Files[Pos2++];
    }

    while (Pos2 <= UB)
        Temp[Pos3++] = Files[Pos2++];

    while (Pos1 <= Split)
        Temp[Pos3++] = Files[Pos1++];

    for (int i = 0; i < UB - LB + 1; i++)
        Files[LB + i] = Temp[i];

    free(Temp);
}


void QuickSort(struct _finddata_t* Files, int N, Settings UserSettings)
{
    int i = 0, j = N;
    struct _finddata_t P;

    P = Files[N >> 1];

    do
    {
        while (CompareFiles(P, Files[i], UserSettings.CompareMode) == !UserSettings.ReverseOrder) i++;
        while (CompareFiles(Files[j], P, UserSettings.CompareMode) == !UserSettings.ReverseOrder) j--;

        if (i <= j)
        {
            struct _finddata_t Temp = Files[i];
            Files[i] = Files[j];
            Files[j] = Temp;

            i++;
            j--;
        }

    } while (i <= j);

    if (j > 0) QuickSort(Files, j, UserSettings);
    if (N > i) QuickSort(Files + i, N - i, UserSettings);
}


void ShellSort(struct _finddata_t* Files, int Size, Settings UserSettings)
{
    long Inc;
    int Seq[40], S;

    S = Increment(Seq, Size);

    while (S >= 0)
    {
        Inc = Seq[S--];
        
        for (int i = Inc; i < Size; i++)
        {
            struct _finddata_t Temp = Files[i];

            int j;
            for (j = i - Inc; (j >= 0) && (CompareFiles(Files[j], Temp, UserSettings.CompareMode) == !UserSettings.ReverseOrder); j -= Inc)
                Files[j + Inc] = Files[j];

            Files[j + Inc] = Temp;
        }
    }
}


int Increment(long Inc[], int Size)
{
    int P1, P2, P3, S;

    P1 = P2 = P3 = 1;
    S = -1;

    do
    {
        if (++S % 2)
            Inc[S] = 8 * P1 - 6 * P2 + 1;

        else
        {
            Inc[S] = 9 * P1 - 9 * P3 + 1;
            P2 *= 2;
            P3 *= 2;
        }

        P1 *= 2;

    } while (3 * Inc[S] < Size);

    return S > 0 ? --S : 0;
}


void CountSort(struct _finddata_t* Files, int Size, Settings UserSettings)
{
    int Condition = UserSettings.CompareMode == 0;
    if (Condition)
    {
        unsigned long Max = 1;
        for (int i = 0; i < Size; i++)
            Max = Files[i].size > Max ? Files[i].size : Max;

        Condition = Max <= COUTNSORT_MAXFILESIZE;
        if (Condition)
        {
           int* Counts = (int*)malloc(sizeof(int) * (Max + 1));
           struct _finddata_t** FilesMatrix = (struct _finddata_t**)malloc(sizeof(struct _finddata_t*) * (Max + 1));
           for (int i = 0; i < Max + 1; i++)
               FilesMatrix[i] = (struct _finddata_t*)malloc(sizeof(struct _finddata_t) * MAX_FILES_PER_PAGE);
           
           for (int i = 0; i < Max + 1; i++)
               Counts[i] = 0;

           for (int i = 0; i < Size; i++)
               FilesMatrix[Files[i].size][Counts[Files[i].size]++] = Files[i];

           
           int k = 0;
           for (int i = 0; i < Max; i++)
               for (int j = 0; j < Counts[i]; j++)
               {
                   Files[k++] = FilesMatrix[i][j];
                   free(Counts);
                   free(FilesMatrix[i]);
               }
            
           free(FilesMatrix);
        }
    }

    if (!Condition)
    {
        printf("\nCount Sort Error: sorting mode isn't 'Size' or file sizes are greater than %i !\n", COUTNSORT_MAXFILESIZE);
        QuickSort(Files, Size - 1, UserSettings);
    }
}


void SortFiles(struct _finddata_t* Files, int Size, Settings UserSettings)
{
    switch (UserSettings.SortAlgorithm)
    {
    case 0:
        return BubbleSort(Files, Size, UserSettings);

    case 1:
        return SelectSort(Files, Size, UserSettings);

    case 2:
        return InsertSort(Files, Size, UserSettings);

    case 3:
        return MergeSort(Files, 0, Size - 1, UserSettings);

    case 4:
        return QuickSort(Files, Size - 1, UserSettings);

    case 5:
        return ShellSort(Files, Size, UserSettings);

    case 6:
        return CountSort(Files, Size, UserSettings);
    }
}


// Cleans up the keyboard buffer
void ClearKeyboardBuffer()
{
    int ch;
    while (ch = getchar() != '\n')
        ;
}