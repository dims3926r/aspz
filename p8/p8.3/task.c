#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 10000

int compare_ints(const void *x, const void *y) {
    int a = *(const int *)x;
    int b = *(const int *)y;
    return (a > b) - (a < b);
}

int is_sorted_correctly(int *arr, int len) {
    for (int i = 1; i < len; ++i) {
        if (arr[i - 1] > arr[i]) return 0;
    }
    return 1;
}

void fill_equal(int *arr, int len) {
    for (int i = 0; i < len; ++i)
        arr[i] = 42;
}

void fill_alternating(int *arr, int len) {
    for (int i = 0; i < len; ++i)
        arr[i] = (i % 2 == 0) ? 1 : 100000;
}

void fill_ascending(int *arr, int len) {
    for (int i = 0; i < len; ++i)
        arr[i] = i;
}

void fill_descending(int *arr, int len) {
    for (int i = 0; i < len; ++i)
        arr[i] = len - i;
}

void fill_random(int *arr, int len) {
    for (int i = 0; i < len; ++i)
        arr[i] = rand();
}

void run_test(const char *label, void (*generator)(int *, int)) {
    int *array = malloc(SIZE * sizeof(int));
    if (!array) {
        fprintf(stderr, "Помилка виділення памʼяті\n");
        return;
    }

    generator(array, SIZE);

    clock_t start = clock();
    qsort(array, SIZE, sizeof(int), compare_ints);
    clock_t end = clock();

    double duration = (double)(end - start) / CLOCKS_PER_SEC;
    const char *status = is_sorted_correctly(array, SIZE) ? "OK" : "FAIL";

    printf("%-15s | Час: %7.4fs | Сортування: %s\n", label, duration, status);

    free(array);
}

int main() {
    srand((unsigned int)time(NULL));

    run_test("Random", fill_random);
    run_test("Ascending", fill_ascending);
    run_test("Descending", fill_descending);
    run_test("Equal", fill_equal);
    run_test("Alternating", fill_alternating);

    return 0;
}
