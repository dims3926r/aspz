#include <stdio.h>
#include <stdlib.h>

int main() {
    const char *filename = "/tmp/mytemp.txt";

    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        perror("Помилка при створенні файлу");
        return 1;
    }
    fputs("Це тимчасовий файл\n", file);
    fclose(file);

    printf("Змінюємо власника на root та права доступу на 600...\n");
    system("sudo chown root:root /tmp/mytemp.txt");
    system("sudo chmod 600 /tmp/mytemp.txt");

    file = fopen(filename, "r");
    if (file) {
        printf("Файл можна читати\n");
        fclose(file);
    } else {
        printf("Читання файлу заборонено\n");
    }

    file = fopen(filename, "a");
    if (file) {
        printf("Файл можна редагувати (дописувати)\n");
        fclose(file);
    } else {
        printf("Запис у файл заборонено\n");
    }

    return 0;
}
