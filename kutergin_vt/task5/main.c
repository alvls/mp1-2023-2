#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <dirent.h> // для работы программы и на Mac OS, и на Windows (вместо io.h)
#include <sys/types.h> // определения основных типов данных, используемых в других библиотеках
#include <sys/stat.h> // содержит функции для работы со статусом файлов
#include <time.h>
#include <string.h>
#include <memory.h>
#include <stdlib.h>

struct DATA { // структура, содержащая информацию о файле,  для дальнейшей сортировки
    char name[100];
    char date[100];
    long int size;
};

// все сортировки выполнены для массива размеров файлов sizes, их нужно затем связать с массивом структур files
void BubbleSort(long int array[], int array_size) {
    for (int i = 0; i < array_size - 1; i++) {
        for (int j = 0;  j < array_size - i - 1; j++) {
            if (array[j]  > array[j+1]) {
                long int tmp = array[j];
                array[j] = array[j+1];
                array[j+1] = tmp;
            }
        }
    }
}

void SelectionSort(long int array[], int array_size) {
    long int minPosition, tmp;
    for (int i = 0; i < array_size; i++){
        minPosition = i;
        for (int j = i + 1; j < array_size; j++)
            if (array[minPosition] > array[j])
                minPosition = j;
        tmp = array[minPosition];
        array[minPosition] = array[i];
        array[i] = tmp;
    }
}

void InsertionSort(long int array[], int array_size) {
    long int x;
    int j;
    for (int i  = 1; i < array_size; i++) {
        x = array[i];
        j = i - 1;
        while (j >= 0 && array[j] > x) {
            array[j+1] = array[j];
            j--;
        }
        array[j+1] = x;
    }
}

void Merge(long int array[], int left, int mid, int right) {
    int size = right - left + 1;
    int pos1 = left;
    int pos2 = mid + 1;
    int pos3 = 0;
    long int *b = (long int*)malloc(size*sizeof(long int));
    while ((pos1 <= mid) && (pos2 <= right)) {
        if (array[pos1] < array[pos2])
            b[pos3++] = array[pos1++];
        else
            b[pos3++] = array[pos2++];
    }
    while (pos2 <= right)
        b[pos3++] = array[pos2++];
    while (pos1 <= mid)
        b[pos3++] = array[pos1++];
    memcpy(array + left, b, size*sizeof(long int));
    free(b);
}
void MergeSort(long int array[], int left, int right) {
    int mid;
    if (left < right) {
        mid = (right + left) / 2;
        MergeSort(array, left, mid);
        MergeSort(array, mid + 1, right);
        Merge(array, left, mid, right);
    }
}

void QuickSort(long int array[], int first, int last) {
    int i = first;
    int j = last;
    long int tmp;
    long int x = array[(first + last) / 2];
    do {
        while (array[i] < x)
            i++;
        while (array[j] > x)
            j--;
        if (i <= j) {
            if (i < j) {
                tmp = array[i];
                array[i] = array[j];
                array[j] = tmp;
            }
            i++;
            j--;
        }
    } while (i <= j);
    if (i < last)
        QuickSort(array, i, last);
    if (first < j)
        QuickSort(array, first, j);
}

void ShellSort(long int array[], int array_size) {
    int i, j, tmp, step;
    for (step = array_size / 2; step > 0; step /= 2) {
        for (i = step;  i < array_size; i++) {
            tmp = array[i];
            for (j = i; j >= step; j -=step) {
                if (tmp < array[j - step])
                    array[j] = array[j - step];
                else
                    break;
            }
            array[j] = tmp;
        }
    }
}

void CountingSort(long int array[], int array_size) {
    long int *sorted_array = (long int*)malloc(array_size * sizeof(long int));
    int k;
    for (int i = 0; i < array_size; i++) {
        k = 0;
        for (int j = 0; j < array_size; j++) {
            if (array[i] > array[j])
                k++;
        }
        sorted_array[k] = array[i];
    }
    for (int i = 0; i < array_size; i++)
        array[i] = sorted_array[i];
}

// переворот массива для сортировки по убыванию
void reverseArray(long int array[], int start, int end) {
    long int tmp;
    while (start < end) {
        tmp = array[start];
        array[start] = array[end];
        array[end] = tmp;
        start++;
        end--;
    }
}

int main() {
    DIR *dir; // указатель на директорию
    struct dirent *FILE_INFO; //хранит информацию о файле (имя, тип, ...) в открытой директории
    struct stat FILE_STAT; // хранит информацию о файле (размер, время доступа и модификации, ...) в открытой директории
    char path[1000]; // путь к файлу
    int count = 0; // число файлов  в каталоге
    int i; // счетчик для вывода
    char sort_method[100]; // название метода сортировки
    long int sizes[1000]; // массив для хранения размеров файлов
    clock_t start, end; // начало и конце работы сортировки
    double cpu_time_used; // время выполнения сортировки процессором в секундах (кол-во тактов поделим на число тактов в секунду)
    
    printf("Enter the directory path: ");
    scanf("%s", &path);
    getchar(); // удаление символа новой строки для корректной работы fgets() дальше

    dir = opendir(path); // указатель на директорию с указанным в "" путем
    // сменить на строку-путь, вводимую пользователем
    
    if (dir == NULL) {  //проверка на успешное открытие директории
        perror("opendir");
        while (dir == NULL) {
            printf("\nEnter the path to the existing directory: ");
            scanf("%s", &path);
            getchar();
            dir = opendir(path);
        }
    }
    
    struct DATA files[1000]; // массив структур для хранения информации о файлах и дальнейшей сортировке
    struct DATA tmp; // структура необходимая для сопоставления отсортированного массива размеров файлов с массивом струтур files
    
    while ((FILE_INFO = readdir(dir)) != NULL) { // считывание файлов из каталога
        // проверка на наличие в директории скрытых файлов и других  поддиректорий (readdir не различает файлы и поддиректории, а также считывает и скрытые файлы . , .. , .DS_Store)
        if (strcmp(FILE_INFO -> d_name, ".") == 0 || strcmp(FILE_INFO -> d_name, "..") == 0 || strcmp(FILE_INFO -> d_name, ".DS_Store") == 0)
            continue; // пропускаем поддиректории
        
        char buffer[100]; // отформатированная дата и время последнего изменения файла
        char fullpath[1100]; // полный путь каждого файла
        sprintf(fullpath, "%s/%s", path, FILE_INFO -> d_name); // создается полный путь  к файлу объдинением пути к папке и именем самого файла
        stat(fullpath, &FILE_STAT); // информации о файле, расположенному по указанному пути, записывается в структуру stat
        
        strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", localtime(&FILE_STAT.st_mtime)); // дата изменения файла форматируется в удобочитаемый вид
        
        // заполнение элемента массива структур информацией о файле
        strncpy(files[count].name, FILE_INFO -> d_name, sizeof(files[count].name));
        strncpy(files[count].date, buffer, sizeof(buffer));
        files[count].size = FILE_STAT.st_size;
        sizes[count] = FILE_STAT.st_size;
        
        count++; //считаем число файлов
    }
    
    printf("\nYou can choose one of the sorting methods: ");
    printf("\n - bubble sort;"); // пузырьком
    printf("\n - selection sort;"); // выбором
    printf("\n - insertion sort;"); // вставками
    printf("\n - merge sort;"); // слиянием
    printf("\n - quicksort;"); // Хоара
    printf("\n - Shell sort;"); // Шелла
    printf("\n - counting sort;"); // подсчётом
    printf("\nIf you want to sort in ascending order, enter: up"); // up - возрастание
    printf("\nAnd if you want to sort in descending order, enter: down"); // down - убывание
    
    //возможность смены метода сортировки и повторного формирования выходных данных
    while (1) {
        printf("\nEnter sort method for file sizes + ' up' (or ' down') or enter 'exit' to end: ");
        // fgets() вместо scanf(), чтобы символ пробела в названии сортировок был записан в строку
        fgets(sort_method, sizeof(sort_method), stdin); // stdin - поток, из которого производится чтение (клавиатура)
        sort_method[strcspn(sort_method, "\n")] = 0; // символ вхождения новой строки заменяется на нулевой символ (удаление)
        if (strcmp(sort_method, "bubble sort up") == 0) {
            start = clock();
            BubbleSort(sizes, count);
            end = clock();
            cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
            printf("\nbubble sort took %f seconds to sort files by their sizes\n", cpu_time_used);
        } else if (strcmp(sort_method, "bubble sort down") == 0){
            start = clock();
            BubbleSort(sizes, count);
            end = clock();
            cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
            printf("\nbubble sort took %f seconds to sort files by their sizes\n", cpu_time_used);
            reverseArray(sizes, 0, count - 1);
        } else if (strcmp(sort_method, "selection sort up") == 0) {
            start = clock();
            SelectionSort(sizes, count);
            end = clock();
            cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
            printf("\nselection sort took %f seconds to sort files by their sizes\n", cpu_time_used);
        } else if (strcmp(sort_method, "selection sort down") == 0) {
            start = clock();
            SelectionSort(sizes, count);
            end = clock();
            cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
            printf("\nselection sort took %f seconds to sort files by their sizes\n", cpu_time_used);
            reverseArray(sizes, 0, count - 1);
        } else if (strcmp(sort_method, "insertion sort up") == 0) {
            start = clock();
            InsertionSort(sizes, count);
            end = clock();
            cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
            printf("\ninsertion sort took %f seconds to sort files by their sizes\n", cpu_time_used);
        } else if (strcmp(sort_method, "insertion sort down") == 0) {
            start = clock();
            InsertionSort(sizes, count);
            end = clock();
            cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
            printf("\ninsertion sort took %f seconds to sort files by their sizes\n", cpu_time_used);
            reverseArray(sizes, 0, count - 1);
        } else if (strcmp(sort_method, "merge sort up") == 0) {
            start = clock();
            MergeSort(sizes, 0, count - 1);
            end = clock();
            cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
            printf("\nmerge sort took %f seconds to sort files by their sizes\n", cpu_time_used);
        } else if (strcmp(sort_method, "merge sort down") == 0) {
            start = clock();
            MergeSort(sizes, 0, count - 1);
            end = clock();
            cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
            printf("\nmerge sort took %f seconds to sort files by their sizes\n", cpu_time_used);
            reverseArray(sizes, 0, count - 1);
        } else if (strcmp(sort_method, "quicksort up") == 0) {
            start = clock();
            QuickSort(sizes, 0, count - 1);
            end = clock();
            cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
            printf("\nquicksort took %f seconds to sort files by their sizes\n", cpu_time_used);
        } else if (strcmp(sort_method, "quicksort down") == 0) {
            start = clock();
            QuickSort(sizes, 0, count - 1);
            end = clock();
            cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
            printf("\nquicksort took %f seconds to sort files by their sizes\n", cpu_time_used);
            reverseArray(sizes, 0, count - 1);
        } else if (strcmp(sort_method, "Shell sort up") == 0) {
            start = clock();
            ShellSort(sizes, count);
            end = clock();
            cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
            printf("\nShell sort took %f seconds to sort files by their sizes\n", cpu_time_used);
        } else if (strcmp(sort_method, "Shell sort down") == 0) {
            start = clock();
            ShellSort(sizes, count);
            end = clock();
            cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
            printf("\nShell sort took %f seconds to sort files by their sizes\n", cpu_time_used);
            reverseArray(sizes, 0, count - 1);
        } else if (strcmp(sort_method, "counting sort up") == 0) {
            start = clock();
            CountingSort(sizes, count);
            end = clock();
            cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
            printf("\ncounting sort took %f seconds to sort files by their sizes\n", cpu_time_used);
        } else if (strcmp(sort_method, "counting sort down") == 0) {
            start = clock();
            CountingSort(sizes, count);
            end = clock();
            cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
            printf("\ncounting sort took %f seconds to sort files by their sizes\n", cpu_time_used);
            reverseArray(sizes, 0, count - 1);
        } else if (strcmp(sort_method, "exit") == 0) {
            break; // выход из цикла
        } else {
            printf("There is no such sorting method. Please try again");
            continue;
        }

        
        // связь отсортированного массива sizes с массивом структур
        for (int i = 0; i < count; i++) {
            for (int j = 0; j < count; j++) {
                if (sizes[i] == files[j].size) {
                    tmp = files[i];
                    files[i] = files[j];
                    files[j] = tmp;
                    break;
                }
            }
        }
            
        i = 0; // счетчик вывода в 0 для каждой новой сортировки
        printf("\nLISTING OF FILES\n\n");
        printf("FILE         DATE %24c   SIZE\n", ' ');
        printf("----         ---- %24c   ----\n", ' ');
        while (i < count) {
            printf("%-12.12s %.24s  %10ld B\n", files[i].name, files[i].date , files[i].size);
            i++;
        }
        
        printf("\nCOUNT OF FILES: %d \n\n", count); // вывод числа файлов
    }
    closedir(dir); // закрыли директорию
}

