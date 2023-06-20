#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define SERVER_IP "127.0.0.1"
#define PORT 12345
#define BUFFER_SIZE 1024

int main() {
    int client_socket;
    struct sockaddr_in server_addr;
    char buffer[BUFFER_SIZE];

    // 创建客户端socket
    client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket == -1) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // 设置服务器地址结构
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr(SERVER_IP);
    server_addr.sin_port = htons(PORT);

    // 连接服务器
    if (connect(client_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1){
        perror("Connection failed");
        exit(EXIT_FAILURE);
    }
    printf("Connected to server\n");

    // 与服务器进行通信
    while (1) {
        printf("Enter message to send (or 'q' to quit): ");
        fgets(buffer, BUFFER_SIZE, stdin);

        // 去除换行符
        buffer[strcspn(buffer, "\n")] = '\0';

        // 发送消息给服务器
        if (send(client_socket, buffer, strlen(buffer), 0) == -1) {
            perror("Send failed");
            exit(EXIT_FAILURE);
        }

        // 检查是否退出
        if (strcmp(buffer, "q") == 0) {
            break;
        }

        // 接收服务器的响应
        int recv_size = recv(client_socket, buffer, BUFFER_SIZE - 1, 0);
        if (recv_size == -1) {
            perror("Receive failed");
            exit(EXIT_FAILURE);
        } else if (recv_size == 0) {
            printf("Server disconnected\n");
            break;
        }

        buffer[recv_size] = '\0';
        printf("Received message from server: %s\n", buffer);
    }

    // 关闭连接
    close(client_socket);

    return 0;
}       
