#include "sorting_algorithms.h"

#include <memory.h>

void swap(FileData* files, int i, int j) {
    FileData temp;

    temp = files[i];
    files[i] = files[j];
    files[j] = temp;
}

int bubble_sort(FileData* files, int length) {
    int i, j, swaps;

    for (i = 0; i < length - 1; i++) {
        swaps = 0;
        for (j = 0; j < length - i - 1; j++) {
            if (files[j].size > files[j + 1].size) {
                swap(files, j, j + 1);
                swaps++;
            }
        }

        if (swaps == 0) {
            break;
        }
    }

    return 1;
}

int select_sort(FileData* files, int length) {
    int i, j, min_index;
    _fsize_t min_size;

    for (i = 0; i < length; i++) {
        min_index = i;
        min_size = files[i].size;

        for (j = i + 1; j < length; j++) {
            if (files[j].size < min_size) {
                min_index = j;
                min_size = files[j].size;
            }
        }

        swap(files, i, min_index);
    }

    return 1;
}

int insert_sort(FileData* files, int length) {
    int i, j;
    FileData current_element;

    for (i = 1; i < length; i++) {
        current_element = files[i];

        j = i - 1;
        while (j >= 0 && files[j].size > current_element.size) {
            files[j + 1] = files[j];
            --j;
        }

        files[j + 1] = current_element;
    }

    return 1;
}

int quick_sort(FileData* files, int length) {
    int i, j;
    _fsize_t center_size;

    i = 0;
    j = length - 1;
    center_size = files[length / 2].size;

    do {
        while (files[i].size < center_size) i++;
        while (files[j].size > center_size) j--;

        if (i <= j) {
            swap(files, i, j);
            i++;
            j--;
        }
    } while (i <= j);

    if (j > 0) quick_sort(files, i);
    if (length > i) quick_sort(files + i, length - i);

    return 1;
}

int shell_sort(FileData* files, int length) {
    int s, i, j;
    FileData current_element;

    for (s = length / 2; s > 0; s /= 2) {
        for (i = s; i < length; ++i) {
            current_element = files[i];

            j = i - 1;
            while (j >= 0 && files[j].size > current_element.size) {
                files[j + 1] = files[j];
                --j;
            }

            files[j + 1] = current_element;
        }
    }

    return 1;
}

int merge(FileData* files, int lower_bound, int split_index, int upper_bound) {
    int left_index, right_index, merge_index;
    FileData* temp;

    left_index = lower_bound;
    right_index = split_index;
    merge_index = 0;

    temp = (FileData*)malloc(sizeof(FileData) * (upper_bound - lower_bound));
    if (temp == NULL) {
        return 0;
    }

    while (left_index < split_index && right_index < upper_bound) {
        if (files[left_index].size < files[right_index].size)
            temp[merge_index++] = files[left_index++];
        else
            temp[merge_index++] = files[right_index++];
    }

    while (right_index < upper_bound)
        temp[merge_index++] = files[right_index++];
    while (left_index < split_index)
        temp[merge_index++] = files[left_index++];

    for (merge_index = 0; merge_index < upper_bound - lower_bound; merge_index++)
        files[lower_bound + merge_index] = temp[merge_index];

    free(temp);

    return 1;
}

int merge_sort(FileData* files, int lower_bound, int upper_bound) {
    int success;
    int split;

    if (upper_bound - lower_bound > 1) {
        split = (lower_bound + upper_bound) / 2;

        merge_sort(files, lower_bound, split);
        merge_sort(files, split, upper_bound);
        success = merge(files, lower_bound, split, upper_bound);
        if (!success) {
            return 0;
        }
    }

    return 1;
}

int count_sort(FileData* files, int length) {
    int i;
    _fsize_t j;
    _fsize_t max_size = 0;
    int* counts;
    FileData* temp;

    for (i = 0; i < length; i++) {
        if (files[i].size > max_size) {
            max_size = files[i].size;
        }
    }

    counts = (int*)calloc(max_size + 1, sizeof(int));
    if (counts == NULL) {
        return 0;
    }

    for (i = 0; i < length; i++) {
        counts[files[i].size]++;
    }


    for (j = 1; j <= max_size; j++) {
        counts[j] += counts[j - 1];
    }

    temp = (FileData*)malloc(sizeof(FileData) * length);
    if (temp == NULL) {
        free(counts);
        return 0;
    }

    for (i = 0; i < length; i++) {
        temp[counts[files[i].size] - 1] = files[i];
        counts[files[i].size]--;
    }

    for (i = 0; i < length; i++) {
        files[i] = temp[i];
    }


    free(counts);
    free(temp);

    return 1;
}
