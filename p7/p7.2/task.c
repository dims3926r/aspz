#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <unistd.h>

void show_mode(mode_t m) {
    putchar(S_ISDIR(m) ? 'd' :
            S_ISLNK(m) ? 'l' :
            S_ISCHR(m) ? 'c' :
            S_ISBLK(m) ? 'b' :
            S_ISFIFO(m) ? 'p' :
            S_ISSOCK(m) ? 's' : '-');

    putchar(m & S_IRUSR ? 'r' : '-');
    putchar(m & S_IWUSR ? 'w' : '-');
    putchar(m & S_IXUSR ? 'x' : '-');

    putchar(m & S_IRGRP ? 'r' : '-');
    putchar(m & S_IWGRP ? 'w' : '-');
    putchar(m & S_IXGRP ? 'x' : '-');

    putchar(m & S_IROTH ? 'r' : '-');
    putchar(m & S_IWOTH ? 'w' : '-');
    putchar(m & S_IXOTH ? 'x' : '-');
}

int main() {
    DIR *folder;
    struct dirent *item;
    struct stat info;
    char formatted_time[64];

    folder = opendir(".");
    if (!folder) {
        perror("Не вдалося відкрити поточний каталог");
        return 1;
    }

    while ((item = readdir(folder)) != NULL) {
        if (item->d_name[0] == '.' && 
           (item->d_name[1] == '\0' || 
           (item->d_name[1] == '.' && item->d_name[2] == '\0'))) {
            continue;
        }

        if (stat(item->d_name, &info) == -1) {
            perror("Помилка при stat()");
            continue;
        }

        show_mode(info.st_mode);
        printf(" %ld", (long)info.st_nlink);

        struct passwd *owner = getpwuid(info.st_uid);
        struct group  *group = getgrgid(info.st_gid);

        printf(" %s %s",
               owner ? owner->pw_name : "невідомо",
               group ? group->gr_name : "невідомо");

        printf(" %8ld", (long)info.st_size);

        strftime(formatted_time, sizeof(formatted_time), "%b %d %H:%M", localtime(&info.st_mtime));
        printf(" %s", formatted_time);

        printf(" %s\n", item->d_name);
    }

    closedir(folder);
    return 0;
}
