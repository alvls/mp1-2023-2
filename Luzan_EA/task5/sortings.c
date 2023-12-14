#define _CRT_SECURE_NO_WARNINGS
#include "sortings.h"
#include <string.h>
#include <stdlib.h>
#include <limits.h>



void swap(struct Files* files, int i, int j) {
    struct Files tmp;
    tmp = files[i]; 
    files[i] = files[j]; 
    files[j] = tmp;
}

void bubbleSort(struct Files* files, int size) {
    int i, j, countSwaps;
    for (i = 0; i < size - 1; i++) {
        countSwaps = 0;
        for (j = 0; j < size - i - 1; j++) {
            if (files[j].size > files[j + 1].size) {
                swap(files, j, j + 1); countSwaps++;
            }
        }
        if (countSwaps == 0) { break; }
    }
}

void selectSort(struct Files* a, long size) {
    long i, j, k;
    unsigned long long x;

    for (i = 0; i < size; i++) {   	
        k = i;
        x = a[i].size;

        for (j = i + 1; j < size; j++)
            if (a[j].size < x) {
                k = j; x = a[j].size;	       
            }
        swap(a, i, k);
        a[i].size = x;   	
    }
}

void insertSort(struct Files* a, long size) {
    unsigned long long x;
    long i, j;

    for (i = 0; i < size; i++) {  //i = 1, тк для 0 итерации нет
        x = a[i].size;
        for (j = i - 1; j >= 0 && a[j].size > x; j--)
            swap(a, j + 1, j); 
        a[j + 1].size = x;
    }
}

int quickSort(struct Files* files, int size) {
    int i, j;
    unsigned long long midSize;

    if (size == 0) { return 0; }

    i = 0;
    j = size - 1;
    midSize = files[size / 2].size;

    do {
        while (files[i].size < midSize) { i++; }
        while (files[j].size > midSize) { j--; }

        if (i <= j) {
            swap(files, i, j);
            i++;
            j--;
        }
    } while (i <= j);

    if (j > 0) { quickSort(files, i); }
    if (size > i) { quickSort(files + i, size - i); }
    return 0;
} 

int increment(long inc[], long size) {
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

void shellSort(struct Files* a, long size) {
    long inc, i, j, seq[40];
    int s;

    
    s = increment(seq, size);
    while (s >= 0) {
        
        inc = seq[s--];

        for (i = inc; i < size; i++) {
            struct Files* tmp = (struct Files*)malloc(sizeof(struct Files));
            tmp[0].size = a[i].size;
            strcpy(tmp[0].name, a[i].name);
            for (j = i - inc; (j >= 0) && (a[j].size > tmp[0].size); j -= inc) {
                swap(a, j + inc, j);
            }
            a[j + inc].size = tmp[0].size;
            strcpy(a[j + inc].name, tmp[0].name);
        }
    }
}

int countingSort(struct Files* files, int len) {
    if (len <= 1) {
        return 0;  
    }

    unsigned long long minSize = ULLONG_MAX, maxSize = 0;
    for (int i = 0; i < len; ++i) {
        if (files[i].size < minSize) {
            minSize = files[i].size;
        }
        if (files[i].size > maxSize) {
            maxSize = files[i].size;
        }
    }
    
    unsigned long long  range = maxSize - minSize + 1;
    // maybe even less
    //if (range > 100000) { printf("Too big files. Please change sorting method \n"); return -1; }
    unsigned long long* count =  (unsigned long long*)calloc(range, sizeof(unsigned long long));

    struct Files* tmp = (struct Files*)malloc(sizeof(struct Files) * len);
    
    for (int i = 0; i < len; i++) {
        count[files[i].size - minSize]++;
    }

    for (int i = 1; i < range; i++) {
        count[i] += count[i-1];
    }
    int i = 0;

    for (int i =0; i < len; i++) {
            tmp[count[files[i].size - minSize] - 1] = files[i];
            count[files[i].size - minSize]--;
    }

    for (i = 0; i < len; i++) {
        files[i] = tmp[i];
    }
    
    free(tmp);
    free(count);
    return 0;
}

void merge(struct Files* a, long lb, long split, long ub) {
    long pos1 = lb;
    long pos2 = split + 1;
    long pos3 = 0;
    struct Files* temp = (struct Files*)malloc(sizeof(struct Files) * (ub - lb + 1));

    while ( (pos1 <= split) && (pos2 <= ub)) {
        if (a[pos1].size < a[pos2].size) {
            temp[pos3++] = a[pos1++];
        }
        else {
            temp[pos3++] = a[pos2++];
        }
    }

    while (pos2 <= ub) {  
        temp[pos3++] = a[pos2++];
    }
    while (pos1 <= split) {  
        temp[pos3++] = a[pos1++];
    }

    for (pos3 = 0; pos3 < ub - lb + 1; pos3++) {
        a[lb + pos3] = temp[pos3];
    }

    free(temp);
}

void mergeSort(struct Files* a, long lb, long ub) {
    long split;                  
    if (lb < ub) {                
        split = (lb + ub) / 2;

        mergeSort(a, lb, split);       
        mergeSort(a, split + 1, ub);
        merge(a, lb, split, ub);    
    }
}