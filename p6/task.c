#include <stdlib.h>
#include <stdio.h>

int main() {
    int *arr = malloc(5 * sizeof(int)); 

    printf("arr[2] = %d\n", arr[2]); 

    return 0;
}
