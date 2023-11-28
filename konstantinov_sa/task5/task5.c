#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<locale.h>
#include <io.h>  
#include <time.h>  
#include <omp.h>
//#include<string.h>

typedef struct {
    long size;
    char* name;
}file;

enum Stype
{
    size = 0,
    name = 1,
    //time = 2
};

int cmp(file a, file b, enum Stype type, int rev) {
    int ans = 0;
    switch (type) {


    case size:
        if (rev)
            ans = a.size > b.size;
        else
            ans = a.size < b.size;
        break;

    case name:
        if (rev)
            ans = strcmp(a.name, b.name);
        else
            ans = -strcmp(a.name, b.name);
        break;
    }
}


void bubbleSort(file a[], long size, enum Stype type, int rev) {
    long i, j;
    file x;

    for (i = 0; i < size; i++) {            // i - номер прохода
        for (j = size - 1; j > i; j--) {     // внутренний цикл прохода
            if (a[j - 1].size > a[j].size) {
                x = a[j - 1]; a[j - 1] = a[j]; a[j] = x;
            }
        }
    }
}

void selectSort(file a[], long size) {
    long i, j, k;
    file x;

    for (i = 0; i < size; i++) {   	// i - номер текущего шага
        k = i; x = a[i];

        for (j = i + 1; j < size; j++)	// цикл выбора наименьшего элемента
            if (a[j].size < x.size) {
                k = j; x = a[j];	        // k - индекс наименьшего элемента
            }

        a[k] = a[i]; a[i] = x;   	// меняем местами наименьший с a[i]
    }
}

void merge(file a[], long lb, long split, long ub) {
    // Текущая позиция чтения из первой последовательности a[lb]...a[split]
    long pos1 = lb;

    // Текущая позиция чтения из второй последовательности a[split+1]...a[ub]
    long pos2 = split + 1;

    // Текущая позиция записи в temp
    long pos3 = 0;

    file* temp = (file*)malloc((ub - lb + 1) * sizeof(file));

    // Идет слияние, пока есть хоть один элемент в каждой последовательности
    while (pos1 <= split && pos2 <= ub) {
        if (a[pos1].size < a[pos2].size)
            temp[pos3++] = a[pos1++];
        else
            temp[pos3++] = a[pos2++];
    }

    // Одна последовательность закончилась - 
    // копировать остаток другой в конец буфера
    while (pos2 <= ub)   // Пока вторая последовательность непуста
        temp[pos3++] = a[pos2++];
    while (pos1 <= split)  // Пока первая последовательность непуста
        temp[pos3++] = a[pos1++];

    // Скопировать буфер temp в a[lb]...a[ub]
    for (pos3 = 0; pos3 < ub - lb + 1; pos3++)
        a[lb + pos3] = temp[pos3];

    free(temp);
}

void mergeSort(file a[], long lb, long ub) {
    long split;

    if (lb < ub) {
        split = (lb + ub) / 2;

        mergeSort(a, lb, split);
        mergeSort(a, split + 1, ub);
        merge(a, lb, split, ub);
    }
}

void callMergeSort(file a[], long size) {
    mergeSort(a, 0, size-1);
}

void swap(file* a, file* b) {
    file temp = *a;
    *a = *b;
    *b = temp;
}

long partition(file arr[], long low, long high) {
    long pivot = arr[high].size;
    long i = (low - 1);

    for (long j = low; j <= high - 1; j++) {
        // сравниваем по полю size
        if (arr[j].size < pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

void quickSortR(file arr[], long low, long high) {
    if (low < high) {
        long pi = partition(arr, low, high);

        quickSortR(arr, low, pi - 1);
        quickSortR(arr, pi + 1, high);
    }
}

void callquickSortR(file a[], long size) {
    quickSortR(a, 0, size-1);
}

void insertSort(file a[], long size) {
    file x;
    long i, j;

    for (i = 0; i < size; i++) {  // цикл проходов, i - номер прохода
        x = a[i];

        // поиск места элемента в готовой последовательности 
        for (j = i - 1; j >= 0 && a[j].size > x.size; j--)
            a[j + 1] = a[j];  	// сдвигаем элемент направо, пока не дошли

        // место найдено, вставить элемент
        a[j + 1] = x;
    }
}



void printfiles(file* f, int count) {
    printf("FILES SORTED\n");
    for (int i = 0; i < count;i++) {
        //printf("%-12.12s %.24s  %10ld\n", c_file.name, buffer, c_file.size);
        //printf("%s %d\n", f[i].name, f[i].size);
        printf("%-25.25s %25u\n", f[i].name, f[i].size);
    }
}

//void printsarr(char** arr, int size) {
//    for (int i = 0; i < size;i++) {
//        printf("%s\n", arr[i]);
//    }
//}

void extend(file** arr, long* cap) {
    file* narr = (file*)realloc(*arr, *cap*2*sizeof(file));
    if (narr) {
        *arr = narr;
        *cap *= 2;
    }
    else {
        printf("! REALLOC ERROR");
    }

}

void isSortValid(file a[], long size) {
    for (long i = 1;i < size;i++) {
        if (a[i].size < a[i - 1].size) {
            printf("INVALID SORT!!!!!!!!!!!");
        }
            
    }

}

int main() {
	setlocale(LC_ALL, "");
    /*char* a[] = {"ворон","белочка","агуша","генератор","вариант"};
    long size = 5;
    printsarr(a, size);
    bubbleSort(a, size);
    printsarr(a, size);*/
    file *files = (file*)malloc(10*sizeof(file));
    long fcap = 10;

    struct _finddata_t c_file;
    intptr_t hFile;
    char path[200] = "E:\\TVR4\\3D\\Render\\*.*";
    long count = 0;

    if ((hFile = _findfirst(path, &c_file)) == -1L)
        printf("No files in current directory!\n");
    else
    {
        printf("Listing of .c files\n\n");
        printf("FILE         DATE %24c   SIZE\n", ' ');
        printf("----         ---- %24c   ----\n", ' ');
        do {
            char buffer[30];
            ctime_s(buffer, _countof(buffer), &c_file.time_write); 
            //printf("%-12.12s %.24s  %10ld\n", c_file.name, buffer, c_file.size);
            if (count >= fcap)
                extend(&files, &fcap);

            files[count].size = c_file.size;
            files[count].name = (char*)malloc(strlen(c_file.name) * sizeof(char));
            if (files[count].name) {
                strcpy(files[count].name, c_file.name);
            }
            else {
                printf("! MALLOC ERROR\n");
            }
                
            
            
            count++;
        } while (_findnext(hFile, &c_file) == 0);
        _findclose(hFile);
        printf("\ncount of files: %d\n", count);
    }

    void (*sort) (file a[], long size);

    sort = callquickSortR;
    ///////////////////////////////////////////////////////////////////
    double start = omp_get_wtime();
    sort(files, count);//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
    //mergeSort(files, 0, count);

    double end = omp_get_wtime();
    double wtick = omp_get_wtick();

    printfiles(files, count);

    printf("Execution time = %lf\n", end - start);

    //printf("wtick = %.16g\n", wtick);



    //clock_t start, end;
    //start = clock();

    //end = clock();
    //printf("Total time:%g\n", (double)(end - start) / CLOCKS_PER_SEC);

    isSortValid(files, count);
    
    system("pause");
}

//int main2(void)
//{
//    struct _finddata_t c_file;
//    intptr_t hFile;
//    char path[200];
//    int count = 0;
//
//    // Find first file in directory c:\temp
//    if ((hFile = _findfirst("c:\\temp\\*.*", &c_file)) == -1L)
//        printf("No files in current directory!\n");
//    else
//    {
//        printf("Listing of .c files\n\n");
//        printf("FILE         DATE %24c   SIZE\n", ' ');
//        printf("----         ---- %24c   ----\n", ' ');
//        do {
//            char buffer[30];
//            ctime_s(buffer, _countof(buffer), &c_file.time_write);
//            if (count <= 20)
//                printf("%-12.12s %.24s  %10ld\n", c_file.name, buffer, c_file.size);
//            count++;
//        } while (_findnext(hFile, &c_file) == 0);
//        _findclose(hFile);
//        printf("\ncount of files: %d", count);
//    }
//    system("pause");
//}

//Разработать прототип файлового менеджера с функцией показа файлов в заданном каталоге, упорядоченных по возрастанию / убыванию размера.
//
//Входные данные :
//Путь до директории, в которой необходимо отсортировать содержимое.
//Метод сортировки.
//Выходные данные :
//Отсортированный список имен файлов с указанием размера.
//Время сортировки.
//Программа должна предоставлять пользователю возможность сменить метод сортировки и повторно формировать выходные данные.
//
//Программа должна реализовывать диалог с пользователем посредством интерфейса, который включает :
//возможность ввода пути до заданного каталога;
//возможность выбора метода сортировки;
//возможность просмотра отсортированного списка файлов с указанием размера.
//Cписок методов сортировки :
//пузырьком
//выбором
//вставками
//слиянием
//Хоара
//Шелла
//подсчетом
//https://metanit.com/c/tutorial/5.11.php
//https://www.techiedelight.com/ru/find-execution-time-c-program/