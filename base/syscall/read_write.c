#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <semaphore.h>
#include <syscall.h>
#include <fcntl.h>
#include <unistd.h>
#define MAX_SIZE 1024
sem_t semaphore;
int fd; // 文件描述符
void* print1(void* arg) {
    sem_wait(&semaphore);
    // printf("223PROC1   MYFILE1\n");
    char* content = "223PROC1   MYFILE1\n";
    for (int i = 0; i < 19; i++) {
        write(fd, content + i, 1);
    }
    sem_post(&semaphore);
}

void* print2(void* arg) {
    sem_wait(&semaphore);
    // printf("223PROC2   MYFILE2\n");
    char* content = "223PROC2   MYFILE1\n";
    for (int i = 0; i < 19; i++) {
        write(fd, content + i, 1);
    }
    sem_post(&semaphore);
}

/**
 * 
 * @brief 接受两个参数，第一个参数是读写的文件名，第二个参数是标志位，0代表读，1代表写
*/
int main(int argc, char* argv[]) {
    // 参数检测
    if (argc != 3) {
        printf("usage: <filename> <flag>\n");
        exit(1);
    }
    // 打开文件
    if ((fd = open(argv[1], O_WRONLY | O_APPEND)) == -1) {
        fprintf(stderr, "fail to open %s\n", argv[1]);
        exit(2);
    }
    // 读信息
    if(strcmp(argv[2], "0") == 0) {
        char buf[MAX_SIZE];
        read(fd, buf, MAX_SIZE - 1);
        printf("%s", buf);
    }
    // 写信息 
    else if (strcmp(argv[2], "1") == 0) {
        sem_init(&semaphore, 0, 1); // 初始化信号量
        pid_t pid = fork(); // 创建子进程
        // 子进程
        if (pid == 0) {
            print2(NULL);
        } else {
            print1(NULL);
        } // 父进程

        sem_destroy(&semaphore); // 销毁信号量
    }
    else {
        fprintf(stderr, "usage: 0:read, 1:write.\n");
    }
    close(fd);  // 关闭文件
    exit(0);
}