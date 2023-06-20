#include <stdio.h>
#include <stdlib.h>
#include "add.h"

int *add_1_svc(int *args, struct svc_req *req) {
  static int result;

  // 执行计算
  result = args[0] + args[1];

  return &result;
}

int main(int argc, char *argv[]) {
  if (argc != 2) {
    printf("Usage: %s <program_name>\n", argv[0]);
    exit(1);
  }

  // 注册远程过程
  register_add_prog_1(atoi(argv[1]), add_1, 1, 1);

  // 运行服务器
  svc_run();

  return 0;
}
