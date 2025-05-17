#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *rwho, *more;
    char text[256];

    rwho = popen("who", "r");
    if (rwho == NULL) {
        perror("Помилка при відкритті rwho");
        return 1;
    }

    more = popen("more", "w");
    if (more == NULL) {
        perror("Помилка при відкритті more");
        pclose(rwho);
        return 1;
    }

    while (fgets(text, sizeof(text), rwho)) {
        fputs(text, more);
    }

    pclose(rwho);
    pclose(more);

    return 0;
}
