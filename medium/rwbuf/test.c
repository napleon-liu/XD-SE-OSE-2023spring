#include <stdio.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>

#define DEVICE_PATH "/dev/rwbuf"
#define MAP_SIZE 1024

int main() {
    int fd;
    char *mapped_addr;

    // 打开设备文件
    // printf("hello\n");
    fd = open(DEVICE_PATH, O_RDWR);
    // printf("hello\n");
    if (fd == -1) {
        perror("Failed to open device");
        return -1;
    }

    // 进行 mmap 映射
    // printf("hello\n");
    mapped_addr = mmap(0, MAP_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    // mapped_addr[1023] = '\0';
    // printf("hello\n");
    if (mapped_addr == MAP_FAILED) {
        perror("Failed to mmap");
        close(fd);
        return -1;
    }
    printf("hello\n");
    // 从映射的内存读取数据
    printf("Device Data:\n");
    puts(mapped_addr);
    // printf("hello\n");
    // 修改映射的内存中的数据
    // mapped_addr[0] = 'A';
    // printf("hello\n");
    // 解除映射
    if (munmap(mapped_addr, MAP_SIZE) == -1) {
        perror("Failed to unmap");
        close(fd);
        return -1;
    }
    // printf("hello\n");
    // 关闭设备文件
    close(fd);

    return 0;
}
