#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>

void show_files(const char *directory) {
    DIR *dir = opendir(directory);
    if (!dir) {
        perror("opendir");
        return;
    }

    struct dirent *entry;
    char path[1024];
    struct stat info;

    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            continue;

        snprintf(path, sizeof(path), "%s/%s", directory, entry->d_name);

        if (stat(path, &info) == -1) {
            perror("stat");
            continue;
        }

        if (S_ISDIR(info.st_mode)) {
            show_files(path);
        } else if (S_ISREG(info.st_mode)) {
            printf("%s\n", path);
        }
    }

    closedir(dir);
}

int main() {
    show_files(".");
    return 0;
}
