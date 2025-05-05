#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BLOCK_COUNT 10
#define BLOCK_SIZE  1024 * 1024 * 10

int main() {
    void *blocks[BLOCK_COUNT];

    printf("Виділення %d блоків по %d байт...\n", BLOCK_COUNT, BLOCK_SIZE);

    for (int i = 0; i < BLOCK_COUNT; i++) {
        blocks[i] = malloc(BLOCK_SIZE);
        if (blocks[i] == NULL) {
            perror("malloc failed");
            return 1;
        }
        printf("Блок %d виділено за адресою: %p\n", i, blocks[i]);
    }

    printf("\nЗвільняємо парні блоки...\n");
    for (int i = 0; i < BLOCK_COUNT; i += 2) {
        free(blocks[i]);
        printf("Блок %d звільнено\n", i);
    }

    printf("\nСпроба виділити великий блок памʼяті (50 MB)...\n");
    void *large_block = malloc(50 * 1024 * 1024);
    if (large_block == NULL) {
        printf("Не вдалося виділити 50 MB — можливо через фрагментацію heap\n");
    } else {
        printf("Великий блок виділено за адресою: %p\n", large_block);
        free(large_block);
    }

    for (int i = 1; i < BLOCK_COUNT; i += 2) {
        free(blocks[i]);
    }

    return 0;
}
