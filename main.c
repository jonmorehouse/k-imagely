#include <libmill.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void dialogue(tcpsock as) {
  tcpsend(as, "What's your name?\r\n", 19, -1);

  tcpclose(as);
}

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

    tcpsend(as, "What's your name?\r\n", 19, -1);
    tcpflush(as, -1);

    char inbuf[256];
    size_t size = tcprecvuntil(as, inbuf, sizeof(inbuf), "\r", 1, -1);
    inbuf[size-1] = 0;
    char outbuf[256];
    int rc = snprintf(outbuf, sizeof(outbuf), "Hello, %s!\r\n", inbuf);
    tcpsend(as, outbuf, rc, -1);
    tcpflush(as, -1);

    cleanup:
    tcpclose(as);
  }

  return 0;
}
