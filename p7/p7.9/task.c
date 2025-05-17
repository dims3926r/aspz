#include <stdio.h>
#include <time.h>

int main() {
    clock_t begin_time, finish_time;
    double elapsed_ms;

    begin_time = clock();

    for (int i = 0; i < 1000000; i++) {
        int val = i * i; 
    }

    finish_time = clock();

    elapsed_ms = ((double)(finish_time - begin_time) / CLOCKS_PER_SEC) * 1000.0;

    printf("Витрачено часу: %.3f мілісекунд\n", elapsed_ms);

    return 0;
}
