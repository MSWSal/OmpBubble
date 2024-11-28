#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

#define N 80000 // Size of the array(1000,5000,10000,20000,30000,40k,50k,60k,70k,80k,100k,200k)

// Function prototypes
void bubbleSortSequential(int arr[], int n);
void bubbleSortParallel(int arr[], int n);
void printArray(int arr[], int size);

int main()
{
    int arr1[N], arr2[N];
    double start, end;

    // Initialize the arrays with random values
    srand(time(NULL));
    for (int i = 0; i < N; i++)
    {
        int value = rand() % 100000; // Random numbers between 0 and 99999
        arr1[i] = value;
        arr2[i] = value; 
    }

    // Sequential 
    start = omp_get_wtime();
    bubbleSortSequential(arr1, N);
    end = omp_get_wtime();
    printf("Time taken by sequential bubble sort: %f seconds\n", end - start);

    // Parallel 
    // printArray(arr2, N);
    start = omp_get_wtime();
    bubbleSortParallel(arr2, N);
    end = omp_get_wtime();
    // printArray(arr2, N);
    printf("Time taken by parallel bubble sort: %f seconds\n", end - start);

    return 0;
}

//print array
void printArray(int arr[], int size)
{
    printf("Array elements: ");
    for (int i = 0; i < size; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

// Sequential Bubble Sort
void bubbleSortSequential(int arr[], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                // Swap arr[j] and arr[j + 1]
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

// Parallel Bubble Sort using OpenMP
void bubbleSortParallel(int arr[], int n)
{
    int i, j;
#pragma omp parallel shared(arr, n) private(i, j)
    {
        for (i = 0; i < n - 1; i++)
        {
#pragma omp for
            for (j = 0; j < n - i - 1; j++)
            {
                if (arr[j] > arr[j + 1])
                {
                    // Swap arr[j] and arr[j + 1]
                    int temp = arr[j];
                    arr[j] = arr[j + 1];
                    arr[j + 1] = temp;
                }
            }
        }
    }
}
