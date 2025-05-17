#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int key;
    int id;
} Item;

int cmp(const void *a, const void *b) {
    const Item *x = (const Item *)a;
    const Item *y = (const Item *)b;
    if (x->key == y->key)
        return 0;
    return (x->key < y->key) ? -1 : 1;
}

int cmp_stable(const void *a, const void *b) {
    const Item *x = (const Item *)a;
    const Item *y = (const Item *)b;
    if (x->key == y->key)
        return (x->id < y->id) ? -1 : 1;
    return (x->key < y->key) ? -1 : 1;
}

void mysort(void *arr, size_t n, size_t size, int (*cmp_func)(const void*, const void*)) {
    if (n < 2) return;

    char *a = (char *)arr;
    void *pivot = a + (n - 1) * size;

    size_t i = 0;
    for (size_t j = 0; j < n - 1; j++) {
        if (cmp_func(a + j*size, pivot) < 0) {
            char tmp[size];
            memcpy(tmp, a + i*size, size);
            memcpy(a + i*size, a + j*size, size);
            memcpy(a + j*size, tmp, size);
            i++;
        }
    }
    char tmp[size];
    memcpy(tmp, a + i*size, size);
    memcpy(a + i*size, pivot, size);
    memcpy(a + (n - 1)*size, tmp, size);

    mysort(a, i, size, cmp_func);
    mysort(a + (i + 1)*size, n - i - 1, size, cmp_func);
}

void print_arr(Item *arr, size_t n) {
    for (size_t i = 0; i < n; i++) {
        printf("{key=%d, id=%d} ", arr[i].key, arr[i].id);
    }
    printf("\n");
}

int main() {
    Item data[] = {
        {3, 1}, {1, 2}, {2, 3}, {3, 4}, {2, 5}, {1, 6}
    };
    size_t n = sizeof(data) / sizeof(data[0]);

    Item a1[n], a2[n];
    memcpy(a1, data, sizeof(data));
    memcpy(a2, data, sizeof(data));

    printf("Початковий масив:\n");
    print_arr(data, n);

    mysort(a1, n, sizeof(Item), cmp);
    printf("Відсортовано власним mysort (нестабільно):\n");
    print_arr(a1, n);

    qsort(a2, n, sizeof(Item), cmp);
    printf("Відсортовано системним qsort (нестабільно):\n");
    print_arr(a2, n);

    memcpy(a1, data, sizeof(data));
    qsort(a1, n, sizeof(Item), cmp_stable);
    printf("Відсортовано системним qsort (стабільно):\n");
    print_arr(a1, n);

    return 0;
}
