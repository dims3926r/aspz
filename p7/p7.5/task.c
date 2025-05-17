#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>

void list(const char *path) {
    struct dirent *e;
    DIR *d = opendir(path);
    char full[1024];
    struct stat s;

    while ((e = readdir(d))) {
        if (!strcmp(e->d_name, ".") || !strcmp(e->d_name, ".."))
            continue;

        snprintf(full, sizeof(full), "%s/%s", path, e->d_name);
        stat(full, &s);

        if (S_ISDIR(s.st_mode))
            list(full);
        else
            printf("%s\n", full);
    }

    closedir(d);
}

int main() {
    list(".");
    return 0;
}