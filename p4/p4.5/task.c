#include <stdio.h>
#include <stdlib.h>

int main() {
    size_t size = 1024 * 1024 * 1024; 
    printf("Спроба виділити %zu байт памʼяті через malloc...\n", size);
    void *ptr = malloc(size);

    if (!ptr) {
        printf("malloc не вдалося — недостатньо памʼяті\n");
        return 1;
    }
    printf("malloc успішно виділив %zu байт памʼяті за адресою: %p\n", size, ptr);

    printf("Спроба збільшити розмір блоку через realloc...\n");
    void *newptr = realloc(ptr, (size_t)-1); 

    if (!newptr) {
        printf("realloc не вдалося — попередній ptr не втрачено, ptr = %p\n", ptr);
        free(ptr); 
    } else {
        printf("realloc виділив нову памʼять за адресою: %p\n", newptr);
        free(newptr);
    }

    return 0;
}