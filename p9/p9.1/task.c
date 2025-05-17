#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main() {
    FILE *stream = popen("getent passwd", "r");
    if (stream == NULL) {
        fprintf(stderr, "Не вдалося виконати команду getent passwd\n");
        return 1;
    }

    char buffer[1024];
    char *current_user = getlogin();
    if (!current_user) current_user = getenv("USER");

    while (fgets(buffer, sizeof(buffer), stream)) {
        char *saveptr = NULL;
        char *username = strtok_r(buffer, ":", &saveptr);
        if (!username) continue;

        strtok_r(NULL, ":", &saveptr);

        char *uid_field = strtok_r(NULL, ":", &saveptr);
        if (!uid_field) continue;

        int uid = atoi(uid_field);

        if (uid > 999 && current_user && strcmp(username, current_user) != 0) {
            printf("Користувач: %s (UID=%d)\n", username, uid);
        }
    }

    pclose(stream);
    return 0;
}
