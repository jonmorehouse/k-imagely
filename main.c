#include <libmill.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
  int port = 5555;
  if (argc > 1) {
    port = atoi(argv[1]);
  }

  printf("%s", "hello world");
  return 0;
}
