//#define _CRT_SECURE_NO_WARNINGS
//#include<stdio.h>
//#include<stdlib.h>
//#include<locale.h>
//#include <io.h>  
//#include <time.h>  
//#include <omp.h>
//#include <memory.h>
//
//typedef struct {
//    long size;
//    char* name;
//}file;
//
//enum Stype
//{
//    size = 0,
//    name = 1,
//    //time = 2
//};
//
//int cmp(file a, file b, enum Stype type, int rev) {
//    int ans = 0;
//    switch (type) {
//
//
//    default:
//        if (rev)
//            ans = a.size > b.size;
//        else
//            ans = a.size < b.size;
//        break;
//
//    case name:
//        if (rev)
//            ans = strcmp(a.name, b.name) > 0;
//        else
//            ans = strcmp(a.name, b.name) < 0;
//        break;
//    }
//    return ans;
//}
//
//
//void bubbleSort(file a[], long size, enum Stype type, int rev) {
//    long i, j;
//    file x;
//
//    for (i = 0; i < size; i++) {            // i - ����� �������
//        for (j = size - 1; j > i; j--) {     // ���������� ���� �������
//            if (cmp(a[j - 1], a[j], type, !rev)) {
//                x = a[j - 1]; a[j - 1] = a[j]; a[j] = x;
//            }
//        }
//    }
//}
//
//void selectSort(file a[], long size, enum Stype type, int rev) {
//    long i, j, k;
//    file x;
//
//    for (i = 0; i < size; i++) {   	// i - ����� �������� ����
//        k = i; x = a[i];
//
//        for (j = i + 1; j < size; j++)	// ���� ������ ����������� ��������
//            if (cmp(a[j], x, type, rev)) {
//                k = j; x = a[j];	        // k - ������ ����������� ��������
//            }
//
//        a[k] = a[i]; a[i] = x;   	// ������ ������� ���������� � a[i]
//    }
//}
//
//void merge(file a[], long lb, long split, long ub, enum Stype type, int rev) {
//    // ������� ������� ������ �� ������ ������������������ a[lb]...a[split]
//    long pos1 = lb;
//
//    // ������� ������� ������ �� ������ ������������������ a[split+1]...a[ub]
//    long pos2 = split + 1;
//
//    // ������� ������� ������ � temp
//    long pos3 = 0;
//
//    file* temp = (file*)malloc((ub - lb + 1) * sizeof(file));
//
//    // ���� �������, ���� ���� ���� ���� ������� � ������ ������������������
//    while (pos1 <= split && pos2 <= ub) {
//        if (cmp(a[pos1], a[pos2], type, rev))
//            temp[pos3++] = a[pos1++];
//        else
//            temp[pos3++] = a[pos2++];
//    }
//
//    // ���� ������������������ ����������� - 
//    // ���������� ������� ������ � ����� ������
//    while (pos2 <= ub)   // ���� ������ ������������������ �������
//        temp[pos3++] = a[pos2++];
//    while (pos1 <= split)  // ���� ������ ������������������ �������
//        temp[pos3++] = a[pos1++];
//
//    // ����������� ����� temp � a[lb]...a[ub]
//    for (pos3 = 0; pos3 < ub - lb + 1; pos3++)
//        a[lb + pos3] = temp[pos3];
//
//    free(temp);
//}
//
//void mergeSort(file a[], long lb, long ub, enum Stype type, int rev) {
//    long split;
//
//    if (lb < ub) {
//        split = (lb + ub) / 2;
//
//        mergeSort(a, lb, split, type, rev);
//        mergeSort(a, split + 1, ub, type, rev);
//        merge(a, lb, split, ub, type, rev);
//    }
//}
//
//void callMergeSort(file a[], long size, enum Stype type, int rev) {
//    mergeSort(a, 0, size - 1, type, rev);
//}
//
//void swap(file* a, file* b) {
//    file temp = *a;
//    *a = *b;
//    *b = temp;
//}
//
//long partition(file arr[], long low, long high, enum Stype type, int rev) {
//    //long pivot = arr[high].size;
//    long i = (low - 1);
//
//    for (long j = low; j <= high - 1; j++) {
//        // ���������� �� ���� size
//        if (cmp(arr[j], arr[high], type, rev)) {
//            i++;
//            swap(&arr[i], &arr[j]);
//        }
//    }
//    swap(&arr[i + 1], &arr[high]);
//    return (i + 1);
//}
//
//void quickSortR(file arr[], long low, long high, enum Stype type, int rev) {
//    if (low < high) {
//        long pi = partition(arr, low, high, type, rev);
//
//        quickSortR(arr, low, pi - 1, type, rev);
//        quickSortR(arr, pi + 1, high, type, rev);
//    }
//}
//
//void callquickSortR(file a[], long size, enum Stype type, int rev) {
//    quickSortR(a, 0, size - 1, type, rev);
//}
//
//void insertSort(file a[], long size, enum Stype type, int rev) {
//    file x;
//    long i, j;
//
//    for (i = 0; i < size; i++) {  // ���� ��������, i - ����� �������
//        x = a[i];
//
//        // ����� ����� �������� � ������� ������������������ 
//        for (j = i - 1; j >= 0 && cmp(a[j], x, type, rev); j--)
//            a[j + 1] = a[j];  	// �������� ������� �������, ���� �� �����
//
//        // ����� �������, �������� �������
//        a[j + 1] = x;
//    }
//}
//
//void shellSort(file arr[], long size, enum Stype type, int rev) {
//    for (int gap = size / 2; gap > 0; gap /= 2) {
//        for (int i = gap; i < size; i++) {
//            file temp = arr[i];
//            int j;
//            for (j = i; j >= gap && cmp(arr[j - gap], temp, type, !rev); j -= gap) {
//                arr[j] = arr[j - gap];
//            }
//            arr[j] = temp;
//        }
//    }
//}
//
//void countingSort(file a[], long size, enum Stype type, int rev) {
//    const long MAX_SIZE = 1000000; // ������������ ������ �����
//
//    // ������� ������ ��� �������� ������
//    long* count = (long*)malloc((MAX_SIZE + 1) * sizeof(long));
//    if (count == NULL) {
//        printf("�� ������� �������� ������ ��� ������� count");
//        return;
//    }
//    memset(count, 0, (MAX_SIZE + 1) * sizeof(long));
//
//    // ������������ ������� �������� ������
//    for (long i = 0; i < size; i++) {
//        //a[i].size %= MAX_SIZE+1;//a[i].size % (MAX_SIZE+1)
//        count[a[i].size % (MAX_SIZE + 1)]++;
//        //printf(">>> %-25.25s %25u\n", a[i].name, a[i].size);
//
//    }
//
//    // ��������� ���������� �����
//    for (long i = 1; i <= MAX_SIZE; i++) {
//        count[i] += count[i - 1];
//    }
//
//    // ������� ��������� ������ ��� ����������
//    file* temp = (file*)malloc((size + 1) * sizeof(file));
//    if (temp == NULL) {
//        printf("�� ������� �������� ������ ��� ������� temp");
//        return;
//    }
//
//    // ��������� ������ �� ������� �����
//    for (long i = size - 1; i >= 0; i--) {
//
//        temp[count[(a[i].size % (MAX_SIZE + 1)) % (MAX_SIZE + 1)] - 1] = a[i];
//        count[a[i].size % (MAX_SIZE + 1)]--;
//        //printf("? %-25.25s %25u\n", a[i].name, a[i].size);
//
//    }
//    // �������� ��������������� ������ ������� � ��������
//    if (!rev) {
//        for (long i = 0; i < size; i++) {
//            a[i] = temp[i];
//            //printf(">%-25.25s %25u\n", a[i].name, a[i].size);
//        }
//    }
//    else {
//        for (long i = 0; i < size; i++) {
//            a[i] = temp[size - i - 1];
//        }
//    }
//    free(count);
//    free(temp);
//}
//
//// ��������������� �������
//void printfiles(file* f, int count) {
//    printf("\n��� %40c ������\n", ' ');
//    for (int i = 0; i < count;i++) {
//        //printf("%-12.12s %.24s  %10ld\n", c_file.name, buffer, c_file.size);
//        //printf("%s %d\n", f[i].name, f[i].size);
//        printf("%-25.25s %25u\n", f[i].name, f[i].size);
//    }
//}
//
//void extend(file** arr, long* cap) {
//    file* narr = (file*)realloc(*arr, *cap * 2 * sizeof(file));
//    if (narr) {
//        *arr = narr;
//        *cap *= 2;
//    }
//    else {
//        printf("! REALLOC ERROR");
//    }
//
//}
//
//void isSortValid(file a[], long size) {
//    for (long i = 1;i < size;i++) {
//        if (a[i].size < a[i - 1].size) {
//            printf("INVALID SORT!!!!!!!!!!!");
//        }
//
//    }
//
//}
//
//int main() {
//    setlocale(LC_ALL, "");
//
//    
//
//    struct _finddata_t c_file;
//    intptr_t hFile = -1L;
//    char path[200] = "D:\\Static\\RWDP_MS_pre\\*.*";
//
//    long count = 0;
//    
//    void (*sort) (file a[], long size, enum Stype type, int rev);
//    int sortID = 0;
//    sort = countingSort;
//    enum Stype type = size;
//    int rev = 0;
//    file* files = (file*)malloc(10 * sizeof(file));
//    long fcap = 10;
//    for (int sortID = 1; sortID < 8;sortID++) {
//        //files = (file*)malloc(10 * sizeof(file));
//        count = 0;
//        long fcap = 10;
//        hFile = _findfirst(path, &c_file);
//        do {
//            char buffer[30];
//            ctime_s(buffer, _countof(buffer), &c_file.time_write);
//
//            if (count >= fcap)
//                extend(&files, &fcap);
//
//            files[count].size = c_file.size;
//            files[count].name = (char*)malloc(strlen(c_file.name) * sizeof(char));
//            if (files[count].name) {
//                strcpy(files[count].name, c_file.name);
//            }
//            else {
//                printf("! MALLOC ERROR\n");
//            }
//
//            count++;
//        } while (_findnext(hFile, &c_file) == 0);
//        _findclose(hFile);
//        //printf("\n������: %d\n", count);
//        
//
//        switch (sortID) {
//        case 1:
//            sort = bubbleSort;
//        case 2:
//            sort = selectSort;
//        case 3:
//            sort = insertSort;
//        case 4:
//            sort = callMergeSort;
//        case 5:
//            sort = callquickSortR;
//        case 6:
//            sort = shellSort;
//        case 7:
//            sort = countingSort;
//        default:
//            sort = bubbleSort;
//
//        }
//        file* f2 = (file*)malloc(sizeof(file) * count);
//        double start = omp_get_wtime();
//        for (int s = 500; s <count; s +=500) {
//            double res = 0;
//            for (int g = 0; g < 10;g++) {
//                memcpy(f2, files, sizeof(file) * count);
//                
//                sort(f2, s, type, rev);
//
//                
//                
//            }
//            double end = omp_get_wtime();
//            double wtick = omp_get_wtick();
//            res += end - start;
//            
//            printf("%lf ", res);
//        }
//        //printfiles(f2, count);
//        
//        
//
//        
//        printf("\n");
//        //free(files);
//    }
//    //isSortValid(files, count);
//
//    system("pause");
//}