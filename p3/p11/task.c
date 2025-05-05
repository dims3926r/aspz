#include <stdio.h>

int counter = 0;

void recurse() {
    char buffer[1024];
    counter++;

    if (counter % 100 == 0) {
        printf("Поточна глибина рекурсії: %d\n", counter);
    }

    recurse();
}

int main() {
    recurse();
    return 0;
}
