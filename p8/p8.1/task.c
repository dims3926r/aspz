#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

int main() {
    int pipefd[2];
    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    fcntl(pipefd[1], F_SETFL, O_NONBLOCK);

    char buffer[65536];
    memset(buffer, 'A', sizeof(buffer));

    ssize_t count = write(pipefd[1], buffer, sizeof(buffer));
    if (count == -1) {
        perror("write");
        exit(EXIT_FAILURE);
    }

    printf("пробуєм записти %ld записано %zd байт\n", sizeof(buffer), count);

    close(pipefd[0]);
    close(pipefd[1]);

    return 0;
}