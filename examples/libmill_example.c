#include <libmill.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void handler(tcpsock accepted_socket, chan channel) {
  // request name from connected client
  tcpsend(accepted_socket, "What's your name?\r\n", 19, -1);
  tcpflush(accepted_socket, -1);

  // send a message to the communication channel, signifying this connection
  chs(channel, int, 1);
  
  // capture the name, and create a response message
  char inbuf[256], outbuf[256];
  size_t size = tcprecvuntil(accepted_socket, inbuf, sizeof(inbuf), "\r", 1, -1);
  inbuf[size-1] = 0;
  int rc = snprintf(outbuf, sizeof(outbuf), "Hello, %s!\r\n", inbuf);
  
  // flush the message to the server
  tcpsend(accepted_socket, outbuf, rc, -1);

  cleanup:
    tcpflush(accepted_socket, -1);
    tcpclose(accepted_socket);
}

int test = 0;
void channel_handler(chan channel) {
  while(1) {
    int received_value = chr(channel, int);
    test = test + 1;
  }
}

int main(int argc, char *argv[]) {
  int port = 5555;
  if (argc > 1) {
    port = atoi(argv[1]);
  }

  // create a communication channel
  chan channel = chmake(int, 0);
  go(channel_handler(channel));

  // create server that listens and routes traffic to handler function
  ipaddr addr = iplocal(NULL, port, 0);
  tcpsock ls = tcplisten(addr);
  if (!ls) {
    perror("Can't open listening socket");
    return 1;
  }

  while(1) {
    tcpsock accepted_socket = tcpaccept(ls, -1);
    if (!accepted_socket) {
      continue;
    } else {
      go(handler(accepted_socket, channel));
    }

    // temporary stop gap :)
    if (test == 3) {
      break;
    }
  }

  return 0;
}
