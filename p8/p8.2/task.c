#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main() {
    int file = open("binary_data.bin", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (file < 0) {
        perror("Не вдалося створити файл");
        return 1;
    }

    unsigned char bytes[] = {4, 5, 2, 2, 3, 3, 7, 9, 1, 5};
    write(file, bytes, sizeof(bytes));
    close(file);

    file = open("binary_data.bin", O_RDONLY);
    if (file < 0) {
        perror("Не вдалося відкрити файл");
        return 1;
    }

    if (lseek(file, 3, SEEK_SET) == -1) {
        perror("Помилка зміщення покажчика");
        close(file);
        return 1;
    }

    unsigned char read_bytes[4];
    ssize_t read_count = read(file, read_bytes, sizeof(read_bytes));
    if (read_count < 0) {
        perror("Помилка читання");
        close(file);
        return 1;
    }

    printf("Зчитані байти:\n");
    for (int i = 0; i < read_count; i++) {
        printf("%d ", read_bytes[i]);
    }
    printf("\n");

    close(file);
    return 0;
}
