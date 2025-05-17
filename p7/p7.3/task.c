#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Використання: %s <слово> <файл>\n", argv[0]);
        return 1;
    }

    FILE *file = fopen(argv[2], "r");
    if (file == NULL) {
        perror("Помилка відкриття файлу");
        return 1;
    }

    char buffer[1024];
    const char *search = argv[1];

    while (fgets(buffer, sizeof(buffer), file)) {
        if (strstr(buffer, search) != NULL) {
            printf("%s", buffer);
        }
    }

    fclose(file);
    return 0;
}
