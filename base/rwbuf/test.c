#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#define DEVICE_NAME "/dev/rwbuf"
#define RW_CLEAR 0x909090
#define RW_RDOLD 0x909091
#define RW_RDNEW 0x909092

int main() {
    int fd;
    int ret;
    char buf[1024];

    fd = open(DEVICE_NAME, O_RDWR);
    if (fd == -1) {
        printf("Open device error");
        return 0;
    }
    printf("\nRead student id...");
    if (read(fd, buf, 3) > 0)
    {
        buf[3] = '\0';
        printf("%s\n", buf);
    } else {
        printf("%s\n", buf);
    }

    printf("read old_buf. Then write aaaaa into buf.\n");
    write(fd, "aaaaa", 5);
    ioctl(fd, RW_RDOLD);
    if (read(fd, buf, 3) > 0)
    {
        printf("Old Buffer:%s\n", buf);
    }
    ioctl(fd, RW_RDNEW);
    if (read(fd, buf, 5) > 0)
    {
        printf("New Buffer:%s\n", buf);
    }
    printf("Write 1100 'a'...");
    if (write(fd, "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa", 1100) == -1)
    {
        printf("Failed\n");
        return 0;
    }
    printf("\nRead from device...");
    if (read(fd, buf, 1024) > 0)
    {
        buf[1023] = '\0';
        printf("%s\n", buf);
    }
    else
    {
        printf("Failed\n");
        return 0;
    }
    printf("\nClear device...");
    if (ioctl(fd, RW_CLEAR) == 0)
        printf("Successful\n");
    else
    {
        printf("Failed\n");
        return 0;
    }
    ret = close(fd);
    printf("Device closed\n");
    return 0;
}