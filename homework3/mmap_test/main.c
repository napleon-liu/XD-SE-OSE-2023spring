/*************************************************************************
	> File Name: main.c
	> Author: napleon
	> Mail: 798936274@qq.com 
	> Created Time: Sun 09 Apr 2023 06:42:44 AM PDT
 ************************************************************************/
#include <sys/types.h> 
#include <sys/stat.h> 
#include <fcntl.h> 
#include <stdio.h>
#include <unistd.h>
#include <sys/mman.h>
#include <string.h>
int main() {
	size_t pagesize = getpagesize();
	int fd = open("./hello.txt", O_RDWR, 00700);
	printf("%d\n", fd);
	printf("System page size: %zu bytes\n", pagesize);
	char *region = mmap(NULL, pagesize, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, fd, 0);
	if (region == MAP_FAILED){
		perror("Could not mmap");
		return 1;
	}
	printf("Before change\n");
	puts(region);
	strcpy(region, "Hello, Napleon");
	printf("After change\n");
	puts(region);

	close(fd);
	return 0;
}
