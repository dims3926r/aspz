#include <stdio.h>
#include <stdlib.h>

int main() {
    printf("Поточний користувач:\n");
    system("whoami");

    printf("\nІнформація про користувача та групи:\n");
    system("id");

    return 0;
}
