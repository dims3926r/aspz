#include <stdio.h>
#include <stdlib.h>

int global_var = 42;

void check_segments() {
    int local_var = 10;
    static int static_var = 20;
    void *heap_var = malloc(1);

    printf("=== Перевірка розташування сегментів ===\n");
    printf("Адреса функції (text segment):      %p\n", (void*)check_segments);
    printf("Адреса глобальної змінної:          %p\n", (void*)&global_var);
    printf("Адреса статичної змінної:           %p\n", (void*)&static_var);
    printf("Адреса локальної змінної (stack):   %p\n", (void*)&local_var);
    printf("Адреса динамічної змінної (heap):   %p\n", heap_var);

    free(heap_var);
}

int main() {
    check_segments();
    return 0;
}

