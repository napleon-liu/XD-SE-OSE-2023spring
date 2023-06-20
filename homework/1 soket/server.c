#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 12345
#define BUFFER_SIZE 1024

int main() {
    int server_socket, client_socket;
    struct sockaddr_in server_addr, client_addr;
    char buffer[BUFFER_SIZE];

    // 创建服务器端socket
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == -1) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // 设置服务器地址结构
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(PORT);

    // 将服务器socket绑定到指定地址和端口
    if (bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        perror("Socket bind failed");
        exit(EXIT_FAILURE);
    }

    // 开始监听连接请求
    if (listen(server_socket, 5) == -1) {
        perror("Listen failed");
        exit(EXIT_FAILURE);
    }

    printf("Server listening on port %d\n", PORT);

    // 接受客户端连接
    socklen_t client_addr_len = sizeof(client_addr);
    client_socket = accept(server_socket, (struct sockaddr *)&client_addr, &client_addr_len);
    if (client_socket == -1) {
        perror("Accept failed");
        exit(EXIT_FAILURE);
    }

    printf("Client connected: %s\n", inet_ntoa(client_addr.sin_addr));

    // 与客户端进行通信
    while (1) {
        // 接收客户端消息
        int recv_size = recv(client_socket, buffer, BUFFER_SIZE, 0);
        if (recv_size == -1) {
            perror("Receive failed");
            exit(EXIT_FAILURE);
        } else if (recv_size == 0) {
            printf("Client disconnected\n");
            break;
        }

        buffer[recv_size] = '\0';
        printf("Received message from client: %s\n", buffer);

        // 发送响应给客户端
        if (send(client_socket, buffer, strlen(buffer), 0) == -1) {
            perror("Send failed");
            exit(EXIT_FAILURE);
        }
    }

    // 关闭连接
    close(client_socket);
    close(server_socket);

    return 0;
}
