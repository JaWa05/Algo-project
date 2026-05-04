/*
 * quickhybrid.c
 * CS 3364 - Design and Analysis of Algorithms
 * Part 1: Quick-Based Hybrid Sorting
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/* ---------------------------------------------------
 * INSERTION SORT   
 * Sorts a subarray from index 'low' to 'high'
 * Used when subarray size is <= K
 * --------------------------------------------------- */
void insertionSort(int A[], int low, int high) {
    int i, j, key;
    for (i = low + 1; i <= high; i++) {
        key = A[i];
        j = i - 1;
        while (j >= low && A[j] > key) {
            A[j + 1] = A[j];
            j--;
        }
        A[j + 1] = key;
    }
}

/* ---------------------------------------------------
 * PARTITION
 * Picks last element as pivot, puts smaller elements
 * to the left and larger to the right
 * Returns the final position of the pivot
 * --------------------------------------------------- */
int partition(int A[], int low, int high) {
    int pivot = A[high];
    int i = low - 1;
    int j, temp;
    for (j = low; j < high; j++) {
        if (A[j] <= pivot) {
            i++;
            temp = A[i]; A[i] = A[j]; A[j] = temp;
        }
    }
    temp = A[i + 1]; A[i + 1] = A[high]; A[high] = temp;
    return i + 1;
}

/* ---------------------------------------------------
 * QUICK HYBRID SORT
 * Uses Quicksort for large subarrays
 * Switches to Insertion Sort when size <= K
 * --------------------------------------------------- */
void quickHybridSort(int A[], int low, int high, int K) {
    if (low < high) {
        if ((high - low + 1) <= K) {
            insertionSort(A, low, high);
        } else {
            int p = partition(A, low, high);
            quickHybridSort(A, low, p - 1, K);
            quickHybridSort(A, p + 1, high, K);
        }
    }
}

/* ---------------------------------------------------
 * HELPER FUNCTIONS
 * --------------------------------------------------- */
void printArray(int A[], int n) {
    int i;
    for (i = 0; i < n; i++) printf("%d ", A[i]);
    printf("\n");
}

void copyArray(int src[], int dst[], int n) {
    int i;
    for (i = 0; i < n; i++) dst[i] = src[i];
}

int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

/* ---------------------------------------------------
 * MAIN - Tests correctness + measures runtime
 * --------------------------------------------------- */
int main() {
    int i;
    int n = 50;
    int K = 5;

    int original[] = {
        73, 412, 985, 156, 640, 289, 901, 34, 567, 778,
        245, 890, 123, 654, 321, 432, 876, 210, 543, 678,
        111, 222, 333, 444, 555, 666, 7777, 888, 999, 135,
        246, 357, 468, 579, 680, 791, 802, 913, 1024, 2048,
        409, 512, 613, 714, 815, 916, 101, 202, 303, 404
    };
    int ourSort[50];
    int builtinSort[50];

    copyArray(original, ourSort, n);
    copyArray(original, builtinSort, n);

    /* ---- RUNTIME MEASUREMENT: only wraps quickHybridSort ---- */
    clock_t start, end;
    double cpu_time_used;

    start = clock();
    quickHybridSort(ourSort, 0, n - 1, K);
    end = clock();

    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    /* ---------------------------------------------------------- */

    qsort(builtinSort, n, sizeof(int), compare);

    printf("Original:  "); printArray(original, n);
    printf("Our sort:  "); printArray(ourSort, n);
    printf("Built-in:  "); printArray(builtinSort, n);

    int correct = 1;
    for (i = 0; i < n; i++) {
        if (ourSort[i] != builtinSort[i]) { correct = 0; break; }
    }

    printf(correct ? "\nCORRECT - Matches built-in sort!\n"
                   : "\nWRONG - Does not match built-in sort.\n");

    printf("\n--- Runtime ---\n");
    printf("quickHybridSort time: %.9f seconds\n", cpu_time_used);
    printf("quickHybridSort time: %.3f ms\n", cpu_time_used * 1000.0);

    return 0;
}