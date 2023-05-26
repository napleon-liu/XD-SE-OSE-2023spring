#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>


/* 读管道 */
void read_from_pipe(int fd) {
    char message[100];
    read(fd, message, 100);
    printf("read from pipe:%s", message);
}

/* 写管道 */
void write_to_pipe(int fd) {
    char *message = "Hello, pipe!\n";
    write(fd, message, strlen(message) + 1);
}

int main(void) {
    int fd[2];
    pid_t pid;
    int sta_val;
    if (pipe(fd)) {
        fprintf(stderr, "create pipe failed!\n");
        exit(1);
    }

    pid = fork();
    if (pid == 0) {
        close(fd[1]);
        read_from_pipe(fd[0]);
        exit(0);
    } else {
        close(fd[0]);
        write_to_pipe(fd[1]);
        exit(0);
    }
    return 0;
}