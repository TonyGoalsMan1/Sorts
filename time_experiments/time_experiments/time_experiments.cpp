#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include "C:\Users\User\OneDrive\Рабочий стол\5c\sorting_alg.h\sorting_alg.h\sorting_alg.h"

#define ARRAY_SIZE(array) sizeof (array) / sizeof (array [0])
//No white space in macro function header!
#define TIME_TEST(testCode,time) { \
clock_t start_time = clock () ; \
testCode \
clock_t end_time = clock () ;\
clock_t sort_time = end_time - start_time ; \
time = ( double ) sort_time / CLOCKS_PER_SEC ; \
}


void checkTime(void (*sortFunc) (int*, size_t),
    void (*generateFunc) (int*, size_t),
    size_t size, char* experimentName);

int isOrdered(int*, size_t size);

void outputArray_(int* array, size_t size);


double getTime() {
    clock_t start_time = clock();
    // фрагмент кода
    // время которого измеряется
    clock_t end_time = clock(); \
        clock_t sort_time = end_time - start_time;
    return (double)sort_time / CLOCKS_PER_SEC;
}


void timeExperiment() {
    // описание функций сортировки
    SortFunc sorts[] = {
    { selection_sort, "Selection_Sort" } ,
    { bubble, "Bubble_Sort" } ,
    // вы добавите свои сортировки
    {qSort, "Quick_Sort"},
    {shellSort, "Shell_Sort"},
    {insertionSort, "Insertion_Sort"},
    {Combsort, "Comb_Sort"}
    };
    const unsigned FUNCS_N = ARRAY_SIZE(sorts);

    // описание функций генерации
    GeneratingFunc generatingFuncs[] = {
        // генерируется случайный массив
        { generateRandomArray,    "_random_" } ,
        // генерируется массив 0, 1, 2, ..., n - 1
        { generateOrderedArray , "_ordered_" } ,
        // генерируется массив n - 1, n - 2, ..., 0
        { generateOrderedBackwards , "_orderedBackwards_" },
        { generateRandomPosNeg, "_mixed_pos_neg_"}
    };
    const unsigned CASES_N = ARRAY_SIZE(generatingFuncs);


    // запись статистики в файл
    for (size_t size = 1000; size <= 10000; size += 1000) {
        printf(" - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n ");
        printf(" Size : %ld \n ", size);
        for (int i = 0; i < FUNCS_N; i++) {
            for (int j = 0; j < CASES_N; j++) {
                // генерация имени файла
                static char filename[256];
                sprintf(filename, " %s_ %s_time ", sorts[i].name, generatingFuncs[j].name);
                checkTime(sorts[i].sort, generatingFuncs[j].generate, size, filename);
            }
        }
        printf("\n");

    }

}


void checkTime(void (*sortFunc) (int*, size_t),
    void (*generateFunc) (int*, size_t),
    size_t size, char* experimentName) {

    static size_t runCounter = 1;
    // генерация последовательности
    static int innerBuffer[100000];
    generateFunc(innerBuffer, size);
    printf(" Run #%zu | ", runCounter++);
    printf(" Name : %s \n ", experimentName);
    // замер времени
    double time;
    TIME_TEST({ sortFunc(innerBuffer,size); }, time);

    // результаты замера
    printf(" Status : ");
    if (isOrdered(innerBuffer, size)) {
        printf(" OK ! Time : %.3f s .\n ", time);
        // запись в файл
        char filename[256];
        sprintf(filename, "./data/%s.csv", experimentName);
        FILE* f = fopen(filename, "a");
        if (f == NULL) {
            printf(" FileOpenError %s ", filename);
            exit(1);
        }
        fprintf(f, "%zu;%.3f\n", size, time);
        fclose(f);
    }
    else {
        printf(" Wrong !\n ");
        // вывод массива, который не смог быть отсортирован
        outputArray_(innerBuffer, size);
        exit(1);
    }

} //end of checkTime() function


int isOrdered(int* array, size_t size) {

    //return 0 or 1

    for (int i = 0; i < size - 1; i++)
        if (array[i] > array[i + 1])
            return 0;

    return 1;
}

void outputArray_(int* array, size_t size) {

    for (int i = 0; i < size; i++)
        printf("%d ", array[i]);

    printf(" \n");

}







int main() {

    timeExperiment();

    return 0;

}