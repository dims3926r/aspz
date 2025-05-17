#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void) {
    srand((unsigned int)time(NULL));

    // Випадкове число від 0.0 до 1.0
    double r1 = (double)rand() / RAND_MAX;
    printf("Від 0.0 до 1.0: %.6f\n", r1);

    double n;
    printf("Введіть n: ");
    if (scanf("%lf", &n) != 1 || n <= 0) {
        printf("Неправильне число\n");
        return 1;
    }

    // Випадкове число від 0.0 до n
    double r2 = ((double)rand() / RAND_MAX) * n;
    printf("Від 0.0 до %.6f: %.6f\n", n, r2);

    return 0;
}
