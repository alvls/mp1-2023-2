#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>  
#include <stdlib.h>  
#include <locale.h>
#include <io.h>  
#include <time.h>  
#include <omp.h>

#define M 500 //������������ ����� ������, �������������� ����������
struct direct {
    char * name;
    long int size;
}dir[M]; 
void merge(long int sorted_massive[], long int lb, long int split, long int ub) { //�������
    long pos1 = lb;
    long pos2 = split + 1;
    long pos3 = 0;
    long int* temp = (long int*)malloc((ub - lb + 1) * sizeof(long int));
    while (pos1 <= split && pos2 <= ub) { // ���� �������, ���� ���� ���� ���� ������� � ������ ������������������
        if (sorted_massive[pos1] < sorted_massive[pos2])
            temp[pos3++] = sorted_massive[pos1++];
        else
            temp[pos3++] = sorted_massive[pos2++];
    }
    while (pos2 <= ub)  
        temp[pos3++] = sorted_massive[pos2++];
    while (pos1 <= split) 
        temp[pos3++] = sorted_massive[pos1++];
    for (pos3 = 0; pos3 < ub - lb + 1; pos3++)
        sorted_massive[lb + pos3] = temp[pos3];
    free(temp);
}
void mergeSort(long int sorted_massive[], long int lb, long int ub) {  // ���������� ���������
    long int  split;                   // ������, �� �������� ����� ������
    if (lb < ub) {                // ���� ���� ����� 1 ��������
        split = (lb + ub) / 2;
        mergeSort(sorted_massive, lb, split);       // ����������� ����� �������� 
        mergeSort(sorted_massive, split + 1, ub);// ����������� ������ �������� 
        merge(sorted_massive, lb, split, ub);    // ����� ���������� � ����� ������
    }
}
void quickSortR(long int sorted_massive[], long int m) { //���������� �����
    long int i = 0, j = m; 
    long int temp, p;
    p = sorted_massive[m >> 1];		// ����������� �������
    do {
        while (sorted_massive[i] < p) i++;
        while (sorted_massive[j] > p) j--;
        if (i <= j) {
            temp = sorted_massive[i]; sorted_massive[i] = sorted_massive[j]; sorted_massive[j] = temp;
            i++; j--;
        }
    } while (i <= j); 
    if (j > 0) quickSortR(sorted_massive, j);
    if (m > i) quickSortR(sorted_massive + i, m - i);
}
int increment(long inc[], long size) { // ���������� ������������������ ����������
    int p1, p2, p3, s;
    p1 = p2 = p3 = 1;
    s = -1;
    do {
        if (++s % 2) {
            inc[s] = 8 * p1 - 6 * p2 + 1;
        }
        else {
            inc[s] = 9 * p1 - 9 * p3 + 1;
            p2 *= 2;
            p3 *= 2;
        }
        p1 *= 2;
    } while (3 * inc[s] < size);
    return s > 0 ? --s : 0;
}
void shellSort(long int sorted_massive[], long int size) { //���������� �����
    long int inc, i, j, seq[40];
    int s;
    s = increment(seq, size); // ���������� ������������������ ����������
    while (s >= 0) {// ���������� ��������� � ������������ inc[] 
        inc = seq[s--];
        for (i = inc; i < size; i++) {
            long int temp = sorted_massive[i];
            for (j = i - inc; (j >= 0) && (sorted_massive[j] > temp); j -= inc)
                sorted_massive[j + inc] = sorted_massive[j];
            sorted_massive[j + inc] = temp;
        }
    }
}
void main() {
    char path[200]; //���� �� ��������
    setlocale(LC_ALL, "rus");
    struct _finddata_t c_file; // ���������, � ������� ��������� �������� � �����
    intptr_t hFile; //��������� �������� ���������
    long int unsorted_massive[M];
    long int sorted_massive[M];
    long int check_massive[M];
    for (int j = 0; j < M; j++) {
        unsorted_massive[j] = -1; sorted_massive[j] = -1; check_massive[j] = -1;
    }
    int choice = -1;
    int close_program = 1;
    long int max_elem = 0;
    double start;
    double end;

    printf("������������ ��� � ��������� \"�������� ��������\"\n��� ������������ ������� ������ ������ � �������� ��������, ������������� �� �����������/�������� �������.\n");
    while (close_program != 0) {
        int count_file = 0;
        choice = -1;
        printf("������� ���� �� ��������, � ������� ����� �������� ����������: ");
        scanf("%s", &path);
        if ((hFile = _findfirst(path, &c_file)) == -1L) {// ��������� = ����� ����� == �� ������
            printf("� ��������� ����� ��� ������\n"); choice = 0;
        }
        else
        {
            do {
                dir[count_file].name = (char*)malloc(sizeof(char) * strlen(c_file.name) + sizeof(char));
                strcpy(dir[count_file].name, c_file.name);
                dir[count_file].size = c_file.size; unsorted_massive[count_file] = c_file.size; sorted_massive[count_file] = c_file.size; check_massive[count_file] = c_file.size;
                if (dir[count_file].size > max_elem)
                    max_elem = dir[count_file].size;
                count_file++;
            } while (_findnext(hFile, &c_file) == 0);
        }
        while (choice!=0) {
            printf("�������� ����� ����������:\n1.���������\n2.�������\n3.���������\n4.��������\n5.�����\n6.�����\n7.���������\n0.��������� � ����������� ����\n");
            do {
                printf("������� ����� �� 0 �� 7 ������������: ");
                scanf("%d", &choice);
            } while (choice > 7 || choice < 0);
            if (choice == 0) {
                break;
            }
            if (choice == 1) { //���������
                start = omp_get_wtime();
                long int help_in_bubble = 0;
                for (int i = 0; i < count_file; i++) {
                    for (int j = count_file - 1; j > i; j--) {
                        if (sorted_massive[j] < sorted_massive[j - 1]) {
                            help_in_bubble = sorted_massive[j - 1];
                            sorted_massive[j - 1] = sorted_massive[j];
                            sorted_massive[j] = help_in_bubble;
                        }
                    }
                    end = omp_get_wtime();
                }
            }
            if (choice == 2) { //�������
                start = omp_get_wtime();
                for (int i = 0; i < count_file; i++) {
                    int k = sorted_massive[i];
                    int p = i;
                    for (int j = i + 1; j < count_file; j++) {
                        if (sorted_massive[j] < k) {
                            k = sorted_massive[j]; p = j;
                        }
                    }
                    sorted_massive[p] = sorted_massive[i];
                    sorted_massive[i] = k;
                }
                end = omp_get_wtime();
            }
            if (choice == 3) {
                start = omp_get_wtime();
                for (int i = 1; i < count_file; i++) {
                    int k = sorted_massive[i];
                    int p = -1;
                    for (int j = i - 1; j >= 0 && sorted_massive[j] > k; j--) {
                        sorted_massive[j + 1] = sorted_massive[j];
                        p = j;
                    }
                    sorted_massive[p] = k;
                }
                end = omp_get_wtime();
            }
            if (choice == 4) {
                start = omp_get_wtime();
                long int lb = 0; long int ub = count_file - 1;
                mergeSort(sorted_massive, lb, ub);
                end = omp_get_wtime();
            }
            if (choice == 5) {
                start = omp_get_wtime();
                quickSortR(sorted_massive, count_file - 1);
                end = omp_get_wtime();
            }
            if (choice == 6) {
                start = omp_get_wtime();
                shellSort(sorted_massive, count_file);
                end = omp_get_wtime();
            }
            if (choice == 7) {
                start = omp_get_wtime();
                long int* help = (long int*)malloc((max_elem + 1) * sizeof(long int));
                memset(help, 0, sizeof(long int) * (max_elem + 1));
                for (int i = 0; i < count_file; ++i) {
                    ++help[sorted_massive[i]];
                }
                long int b = 0;
                for (int i = 0; i < max_elem + 1; ++i) {
                    for (int j = 0; j < help[i]; ++j) {
                        sorted_massive[b++] = i;
                    }
                }
                end = omp_get_wtime();
                free(help);
            }
            for (int i = 0; i < count_file; i++) {
                for (int j = 0; j < count_file; j++) {
                    if (sorted_massive[i] == unsorted_massive[j]) {
                        unsorted_massive[j] = -1;
                        printf("%s %10ld\n", dir[j].name, dir[j].size);
                        break;
                    }
                }
            }
            printf("����� ���������� �����: %f\n\n", end - start);
            for (int i = 0; i < count_file; i++) {
                sorted_massive[i] = check_massive[i];
                unsorted_massive[i] = check_massive[i];
            }
        }
        for (int i = 0; i < count_file; i++) {
            free(dir[i].name);
        }
        printf("������� 0, ���� ������ ������� ���������, ����� ����� ������ �����");
        scanf("%d", &close_program);
    }
}