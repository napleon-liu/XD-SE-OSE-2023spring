#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <errno.h>

#define SHM_SIZE 1024

union semun {
    int val;
    struct semid_ds *buf;
    unsigned short *array;
};

// 创建信号量函数 
int createsem (const char *pathname, int proj_id, int members, int init_val) {
    key_t msgkey;
    int index, sid;
    union semun semopts;

    if ((msgkey = ftok(pathname, proj_id)) == -1) {
        perror("ftok error\n");
        return -1;
    }
}