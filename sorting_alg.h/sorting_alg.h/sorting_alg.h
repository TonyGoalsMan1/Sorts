#include <iostream>
#include <stdio.h>
#include <stdlib.h>

// функция сортировки
typedef struct SortFunc {
    void (*sort) (int* a, size_t n);
    char name[64];
} SortFunc;

typedef struct nSortFunc {
    long long int (*sort) (int* a, size_t n);
    char name[64];
} SortFunc;

// функция генерации
typedef struct GeneratingFunc {
    void (*generate) (int* a, size_t n);

    char name[64];

} GeneratingFunc;

void swap(int* num1, int* num2) {
    int temp = *num1;
    *num1 = *num2;
    *num2 = temp;
}

int index_of_min(int a[], int low, int high) {
    int lowind = low, i; //two vars are declared, the first is initialized, the second is not
    //int lowind, i;
    //lowind = i;
    for (i = low + 1; i <= high; i++) {   /* check for smaller elements from low+1 to high */
        if (a[i] < a[lowind])
            lowind = i;
    }
    return lowind;
}

void selection_sort(int* a, size_t n) {
    int lowind, i, j;
    for (i = 0; i < n - 1; i++) {   /* number of passes through a */
        lowind = index_of_min(a, i, n - 1);
        if (i != lowind)               /* swap if lowind not the same as position i */
            swap(&a[i], &a[lowind]);
    }
}



void bubble(int* a, size_t n) // function to implement bubble sort  
{
    int i, j, temp;
    for (i = 0; i < n; i++)
    {
        for (j = i + 1; j < n; j++)
        {
            if (a[j] < a[i])
            {
                temp = a[i];
                a[i] = a[j];
                a[j] = temp;
            }
        }
    }
}


void generateRandomArray(int* a, size_t n) {

    srand(time(0));

    for (int i = 0; i < n; i++)
        a[i] = rand() % 10000;
}

void generateOrderedArray(int* a, size_t n) {

    for (int i = 0; i < n; i++)
        a[i] = i;

}

void generateOrderedBackwards(int* a, size_t n) {

    for (int i = n; i >= 0; i--)
        a[i] = i;
}


void generateRandomPosNeg(int* a, size_t n) {

    srand(time(0));

    for (int i = 0; i < n; i++)
        a[i] = rand() % 20000 - 10000;
}

// Quick sort in C


// function to find the partition position
int partition(int array[], int low, int high) {

    // select the rightmost element as pivot
    int pivot = array[high];

    // pointer for greater element
    int i = (low - 1);

    // traverse each element of the array
    // compare them with the pivot
    for (int j = low; j < high; j++) {
        //Count comparisons nComp
        if (array[j] <= pivot) {

            // if element smaller than pivot is found
            // swap it with the greater element pointed by i
            i++;

            // swap element at i with element at j
            swap(&array[i], &array[j]);
        }
    }

    // swap the pivot element with the greater element at i
    swap(&array[i + 1], &array[high]);

    // return the partition point
    return (i + 1);
}

void quickSort(int array[], int low, int high) {
    if (low < high) {

        // find the pivot element such that
        // elements smaller than pivot are on left of pivot
        // elements greater than pivot are on right of pivot
        int pi = partition(array, low, high);

        // recursive call on the left of pivot
        quickSort(array, low, pi - 1);

        // recursive call on the right of pivot
        quickSort(array, pi + 1, high);
    }
}

void qSort(int* a, size_t n) {

    quickSort(a, 0, n - 1);
}

// function to print array elements
void printArray(int array[], int size) {
    for (int i = 0; i < size; ++i) {
        printf("%d  ", array[i]);
    }
    printf("\n");
}

/*
// main function
int main() {
  int data[] = {8, 7, 2, 1, 0, 9, 6};

  int n = sizeof(data) / sizeof(data[0]);

  printf("Unsorted Array\n");
  printArray(data, n);

  // perform quicksort on data
  quickSort(data, 0, n - 1);

  printf("Sorted array in ascending order: \n");
  printArray(data, n);
}
*/

void shellSort(int* intArray, size_t elements) {
    int inner, outer;
    int valueToInsert;
    int interval = 1;
    int i = 0;

    while (interval <= elements / 3) {
        interval = interval * 3 + 1;
    }

    while (interval > 0) {
        //printf("iteration %d#:",i); 
        //display();

        for (outer = interval; outer < elements; outer++) {
            valueToInsert = intArray[outer];
            inner = outer;

            while (inner > interval - 1 && intArray[inner - interval]
                >= valueToInsert) {
                intArray[inner] = intArray[inner - interval];
                inner -= interval;
                //printf(" item moved :%d\n",intArray[inner]);
            }

            intArray[inner] = valueToInsert;
            //printf(" item inserted :%d, at position :%d\n",valueToInsert,inner);
        }

        interval = (interval - 1) / 3;
        i++;
    }
}

/* Function to sort an array using insertion sort*/
void insertionSort(int* arr, size_t n)
{
    int i, key, j;
    for (i = 1; i < n; i++) {
        key = arr[i];
        j = i - 1;

        /* Move elements of arr[0..i-1], that are
          greater than key, to one position ahead
          of their current position */
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

void Combsort(int* a, size_t nElements)
{
    int i, j, gap, swapped = 1;
    int temp;

    gap = nElements;
    while (gap > 1 || swapped == 1)
    {
        gap = gap * 10 / 13;
        if (gap == 9 || gap == 10) gap = 11;
        if (gap < 1) gap = 1;
        swapped = 0;
        for (i = 0, j = gap; j < nElements; i++, j++)
        {
            if (a[i] > a[j])
            {
                temp = a[i];
                a[i] = a[j];
                a[j] = temp;
                swapped = 1;
            }
        }
    }
}