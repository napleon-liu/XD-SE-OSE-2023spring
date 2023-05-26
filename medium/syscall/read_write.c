#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <semaphore.h>
#include <syscall.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#define MAX_SIZE 1024
int fd; // 文件描述符

int* shm_addr;
void print1() {
    while (shm_addr[0] == 0);
    char* content = "223PROC1   MYFILE1\n";
    for (int i = 0; i < 19; i++) {
        write(fd, content + i, 1);
    }
    shm_addr[0] = 0;    
}

void print2() {
    while (shm_addr[0] == 1);
    char* content = "223PROC2   MYFILE1\n";
    for (int i = 0; i < 19; i++) {
        write(fd, content + i, 1);
    }
    shm_addr[0] = 1;    
}
int main(int argc, char* argv[])
{
    int shmid;
    key_t key;

    // char* filename = argv[1];
    // char* mode = argv[2];
    // for test
    char* filename = "myfile.txt";
    char* mode = "1";

    key = ftok("./", 2023);
    if (key == -1)
    {
        perror("ftok");
    }
    shmid = shmget(key, MAX_SIZE, IPC_CREAT | 0666);
    if (shmid < 0)
    {
        perror("shmget");
        exit(-1);
    }

    // 连接共享内存
    shm_addr = shmat(shmid, NULL, 0); // 连接共享内存
    shm_addr[0] = 0;
    // if (shm_addr[0] == 0)
    //     printf("OK\n");
    if(strcmp(mode, "0") == 0) {
        if ((fd = open(filename, O_RDONLY)) == -1) {
        // perror("fail to open %s\n", filename);
        fprintf(stderr, "fail to open %s\n", filename);
        exit(2);
        }
        char buf[MAX_SIZE];
        // 读信息
        // while ((read(fd, buf, MAX_SIZE - 1)) != 0) {
        //     printf("%s\n", buf);
        // }
        read(fd, buf, MAX_SIZE - 1);
        printf("%s", buf);
        close(filename);
    }
    // 写信息 
    else if (strcmp(mode, "1") == 0) {
        if ((fd = open(filename, O_WRONLY | O_APPEND)) == -1) {
            // perror("fail to open %s\n", filename);
            fprintf(stderr, "fail to open %s\n", filename);
            exit(2);
        }
        pid_t pid = fork();
        if (pid == 0) {
            print2();
        } else {
            print1();
        }
    }
    else {
        fprintf(stderr, "usage: 0:read, 1:write.\n");
    }
    close(fd);
    exit(0);
}