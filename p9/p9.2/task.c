#include <stdio.h>
#include <stdlib.h>

int main() {
    int status = system("sudo cat /etc/shadow");
    if (status == -1) {
        perror("Помилка виконання команди");
        return 1;
    } else {
        if (WIFEXITED(status)) {
            int code = WEXITSTATUS(status);
            if (code != 0) {
                fprintf(stderr, "Команда завершилась з кодом помилки: %d\n", code);
                return code;
            }
        } else {
            fprintf(stderr, "Команда завершилась ненормально\n");
            return 1;
        }
    }
    return 0;
}
