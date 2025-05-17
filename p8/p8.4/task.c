#include <stdio.h>
#include <unistd.h>

int main() {
    pid_t pid = fork();

    if (pid == 0)
        printf("Дочірній процес: pid = %d\n", pid);
    else if (pid > 0)
        printf("Батьківський процес: pid дочірнього = %d\n", pid);
    else
        printf("Помилка при fork()\n");

    return 0;
}
