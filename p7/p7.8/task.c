#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>

int main() {
    DIR *d = opendir(".");
    if (!d) {
        perror("Помилка відкриття каталогу");
        return 1;
    }

    struct dirent *ent;
    char answer;

    while ((ent = readdir(d)) != NULL) {
        if (ent->d_name[0] == '.') 
            continue;

        printf("Файл: %s\n", ent->d_name);
        printf("Видалити цей файл? (y/n): ");
        scanf(" %c", &answer);

        if (answer == 'y' || answer == 'Y') {
            if (remove(ent->d_name) == 0)
                printf("Файл %s успішно видалено.\n", ent->d_name);
            else
                perror("Помилка видалення файлу");
        }
    }

    closedir(d);
    return 0;
}
