#include "sort.h"

void BubbleSort(struct file_info* files, long size)
{
    long i, j;
    struct file_info temp;
    for (i = 0; i < size; i++)
    {
        for (j = size - 1; j > i; j--)
        {
            if (files[j - 1].size > files[j].size)
            {
                temp = files[j - 1];
                files[j - 1] = files[j];
                files[j] = temp;
            }
        }
    }
}

void SelectSort(struct file_info* files, long size)
{
    long i, j, k;
    struct file_info temp;

    for (i = 0; i < size; i++)
    {
        k = i; temp = files[i];

        for (j = i + 1; j < size; j++)
            if (files[j].size < temp.size)
            {
                k = j; temp = files[j];
            }

        files[k] = files[i]; files[i] = temp;
    }
}

void InsertSort(struct file_info* files, long size)
{
    struct file_info temp;
    long i, j;

    for (i = 0; i < size; i++)
    {
        temp = files[i];
        for (j = i - 1; j >= 0 && files[j].size > temp.size; j--)
            files[j + 1] = files[j];
        files[j + 1] = temp;
    }
}

void Merge(struct file_info* files, long lb, long split, long ub)
{
    long pos1 = lb;
    long pos2 = split + 1;
    long pos3 = 0;
    struct file_info* temp = malloc(sizeof(struct file_info) * (ub - lb + 1));
    while (pos1 <= split && pos2 <= ub)
    {
        if (files[pos1].size < files[pos2].size)
            temp[pos3++] = files[pos1++];
        else
            temp[pos3++] = files[pos2++];
    }
    while (pos2 <= ub)
        temp[pos3++] = files[pos2++];
    while (pos1 <= split)
        temp[pos3++] = files[pos1++];
    for (pos3 = 0; pos3 < ub - lb + 1; pos3++)
        files[lb + pos3] = temp[pos3];

    free(temp);
}

void MergeSort(struct file_info* files, long lb, long ub)
{
    long split;

    if (lb < ub)
    {
        split = (lb + ub) / 2;

        MergeSort(files, lb, split);
        MergeSort(files, split + 1, ub);
        Merge(files, lb, split, ub);
    }
}

void HoareSort(struct file_info* files, long N)
{
    long i = 0, j = N - 1;
    struct file_info temp, q;

    q = files[N >> 1];
    do {
        while (files[i].size < q.size)
            i++;
        while (files[j].size > q.size)
            j--;

        if (i <= j)
        {
            temp = files[i]; files[i] = files[j]; files[j] = temp;
            i++;
            j--;
        }
    } while (i <= j);
    if (j > 0)
        HoareSort(files, j + 1);
    if (N > i)
        HoareSort(files + i, N - i);
}

int increment(long inc[], long size)
{
    int p1, p2, p3, s;
    p1 = p2 = p3 = 1;
    s = -1;
    do {
        if (++s % 2)
        {
            inc[s] = 8 * p1 - 6 * p2 + 1;
        }
        else
        {
            inc[s] = 9 * p1 - 9 * p3 + 1;
            p2 *= 2;
            p3 *= 2;
        }
        p1 *= 2;
    } while (3 * inc[s] < size);
    return s > 0 ? --s : 0;
}

void ShellSort(struct file_info* files, long size)
{
    long inc, i, j, seq[40];
    int s;
    s = increment(seq, size);
    while (s >= 0)
    {
        inc = seq[s--];

        for (i = inc; i < size; i++)
        {
            struct file_info temp = files[i];
            for (j = i - inc; (j >= 0) && (files[j].size > temp.size); j -= inc)
                files[j + inc] = files[j];
            files[j + inc] = temp;
        }
    }
}

void CountingSort(struct file_info* files, long size)
{
    int max_value = 0;
    for (int i = 0; i < size; i++)
    {
        if (files[i].size > max_value)
            max_value = files[i].size;
    }
    struct file_info* c = (struct file_info*)malloc((max_value + 1) * sizeof(struct file_info));
    memset(c, 0, sizeof(*files) * (max_value + 1));

    for (int i = 0; i < size; ++i) {
        ++c[files[i].size].size;
        strcpy_s(c[files[i].size].name, sizeof(c[files[i].size].name), files[i].name);

    }

    int b = 0;
    for (int i = 0; i < max_value + 1; ++i)
    {
        for (int j = 0; j < c[i].size; ++j)
        {
            files[b++].size = i;
            strcpy_s(files[b - 1].name, sizeof(files[b - 1].name), c[i].name);
        }
    }
    free(c);
}