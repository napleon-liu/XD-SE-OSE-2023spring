#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define BUF_SIZE    256
#define PROJ_ID 32
#define PATH_NAME   "."

int main() {
    /* 用户自定义消息队列 */
    struct mymsgbf {
        long msgtype;
        char ctrlstring[BUF_SIZE];
    } msgbuffer;
    int qid;
    int msglen;
    key_t msgkey;
    /* 获取键值 */
    if ((msgkey = ftok(PATH_NAME, PROJ_ID)) == -1) {
        perror ("ftok error!\n");
        exit(1);
    }

    /* 创建消息队列 */
    if ((qid = msgget(msgkey, IPC_CREAT | 0660)) == -1) {
        perror("msgget error!\n");
        exit(1);
    }

    /* 填充消息结构， 发送到消息队列 */
    msgbuffer.msgtype = 3;
    strcpy(msgbuffer.ctrlstring, "Hello, message queue");
    msglen = sizeof(struct mymsgbf) - 4;

    exit(0);
}