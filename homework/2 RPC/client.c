#include <stdio.h>
#include <stdlib.h>
#include "add.h"

int main(int argc, char *argv[]) {
  CLIENT *cl;
  int a, b, result;

  if (argc != 4) {
    printf("Usage: %s <hostname> <arg1> <arg2>\n", argv[0]);
    exit(1);
  }

  cl = clnt_create(argv[1], ADD_PROG, ADD_VERS, "tcp");
  if (cl == NULL) {
    clnt_pcreateerror(argv[1]);
    exit(1);
  }

  a = atoi(argv[2]);
  b = atoi(argv[3]);

  result = add_1(a, b, cl); // 调用远程过程

  if (result == -1) {
    clnt_perror(cl, "RPC call failed");
    exit(1);
  }

  printf("Result: %d\n", result);

  clnt_destroy(cl);
  return 0;
}
