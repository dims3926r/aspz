#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char *data = malloc(20);
    if (!data) {
        perror("malloc failed");
        return 1;
    }

    strcpy(data, "Important data");
    printf("Before realloc: %s\n", data);

    data = realloc(data, 1000000000);  

    if (!data) {
        printf("ERROR: realloc failed. Data is now lost!\n");
        free(data);
        return 1;
    }

    printf("After realloc: %s\n", data);

    free(data);
    return 0;
}
