# 指定编译器
CC := gcc

# 内核源代码目录
KERNEL_DIR := /lib/modules/$(shell uname -r)/build

# 模块名称
MODULE_NAME := rwbuf

# 模块源文件
MODULE_SRC := rwbuf.c

# 构建目标
obj-m := $(MODULE_NAME).o

# 构建规则
all:
	$(MAKE) -C $(KERNEL_DIR) M=$(PWD) modules

# 清理规则
clean:
	$(MAKE) -C $(KERNEL_DIR) M=$(PWD) clean
