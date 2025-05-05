#include <stdio.h>
#include <time.h>

int main() {
    time_t example_time;
    size_t time_size = sizeof(example_time);

    printf("Тип time_t займає %zu байт(и)\n", time_size);

    if (time_size == 4) {
        time_t limit_time = 0x7FFFFFFF;
        printf("На 32-бітній архітектурі час досягне межі: %s", ctime(&limit_time));
    } else {
        printf("На 64-бітних системах обмеження часу практично недосяжне\n");
    }

    return 0;
}

