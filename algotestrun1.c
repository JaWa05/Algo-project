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
    int nValues[] = {50, 100, 300, 500, 750};
    int kValues[] = {1, 5, 10, 15, 20, 30, 50};
    int numN = 5;
    int numK = 7;
    int trials = 10; // average over 10 runs for more accurate timing

    int i, j, t;
    clock_t start, end;
    double cpu_time_used;

    printf("=== RANDOM INPUT ===\n");
    for (i = 0; i < numN; i++) {
        int n = nValues[i];
        printf("\nn = %d\n", n);

        for (j = 0; j < numK; j++) {
            int K = kValues[j];
            double total = 0.0;

            for (t = 0; t < trials; t++) {
                // generate random array
                int *A = malloc(n * sizeof(int));
                int k;
                for (k = 0; k < n; k++) A[k] = rand() % 10000;

                start = clock();
                quickHybridSort(A, 0, n - 1, K);
                end = clock();

                total += ((double)(end - start)) / CLOCKS_PER_SEC;
                free(A);
            }

            printf("  K = %2d | avg time = %.9f s\n", K, total / trials);
        }

        // Pure Quicksort (K = 0)
        double total = 0.0;
        for (t = 0; t < trials; t++) {
            int *A = malloc(n * sizeof(int));
            int k;
            for (k = 0; k < n; k++) A[k] = rand() % 10000;
            start = clock();
            quickHybridSort(A, 0, n - 1, 0);
            end = clock();
            total += ((double)(end - start)) / CLOCKS_PER_SEC;
            free(A);
        }
        printf("  Quicksort (K=0) | avg time = %.9f s\n", total / trials);

        // Pure Insertion Sort (K = n)
        total = 0.0;
        for (t = 0; t < trials; t++) {
            int *A = malloc(n * sizeof(int));
            int k;
            for (k = 0; k < n; k++) A[k] = rand() % 10000;
            start = clock();
            quickHybridSort(A, 0, n - 1, n);
            end = clock();
            total += ((double)(end - start)) / CLOCKS_PER_SEC;
            free(A);
        }
        printf("  Insertion Sort (K=n) | avg time = %.9f s\n", total / trials);
    }

    return 0;
}