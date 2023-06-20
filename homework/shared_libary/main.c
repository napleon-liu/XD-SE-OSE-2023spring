/*************************************************************************
	> File Name: main.c
	> Author: napleon
	> Mail: 798936274@qq.com 
	> Created Time: Sun 09 Apr 2023 05:55:22 AM PDT
 ************************************************************************/

#include<stdio.h>
#include "foo.h"

int main(void) {
	puts("This is a shared library test...\n");
	foo();
	return 0;
}
