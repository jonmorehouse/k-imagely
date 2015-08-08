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

  ipaddr addr = iplocal(NULL, port, 0);
  tcpsock ls = tcplisten(addr);
  if (!ls) {
    perror("Can't open listening socker");
    return 1;
  }

  while(1) {
    tcpsock as = tcpaccept(ls, -1);
    printf("New Connection\n");
    tcpclose(as);
  }

  printf("%s", "hello world");
  return 0;
}
