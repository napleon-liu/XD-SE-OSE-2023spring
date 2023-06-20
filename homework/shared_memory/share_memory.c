/*************************************************************************
	> File Name: share_memory.c
	> Author: napleon
	> Mail: 798936274@qq.com 
	> Created Time: Thu 06 Apr 2023 09:15:56 PM PDT
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define BUFSZ 1024

int main(int argc, char *argv[]) {
	int shmid;
	key_t key;

	key = ftok("./", 2015);
	if (key == -1) {
		perror("ftok");
	}

	shmid = shmget(key, BUFSZ, IPC_CREAT | 0666);
	if (shmid < 0) {
		perror("shmget");
		exit(-1);
	}
}
