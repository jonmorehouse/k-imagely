#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libmill.h>

#include "server.h"

const int URI_MAXIMUM_LENGTH = 256;
const int QUERY_ARG_MAXIMUM_LENGTH = 2083 - URI_MAXIMUM_LENGTH;
const char* HTTP_PROTOCOL = "HTTP/1.1";

Request * getPostData(tcpsock socket) {

  return NULL;
}

Request * getRequest(tcpsock socket) {
  char method[8], uri[URI_MAXIMUM_LENGTH];
  Request * request = malloc(sizeof(Request));

  size_t size = tcprecvuntil(socket, method, 8, " ", 1, -1);
  if (errno) {
    request->error = errno;
    return request;
  } else {


  }

  size = tcprecvuntil(socket, uri, URI_MAXIMUM_LENGTH, " ?", 2, -1);
  if (errno) {
    request->error = errno;
    return request;
  } else if (uri[size - 1] == '?') {
    // parse query args out of the response
    char queryArgs[QUERY_ARG_MAXIMUM_LENGTH];
    size = tcprecvuntil(socket, queryArgs, QUERY_ARG_MAXIMUM_LENGTH, " ", 1, -1);
  }

  char protocol[8];
  size = tcprecvuntil(socket, protocol, 8, "\r\n\r\n", 1, -1);
  if (errno) {
    request->error = errno;
    return request;
  }

  request->isHTTP = !(strncmp(protocol, HTTP_PROTOCOL,5));
  return request;
}

Request* parseRequest(tcpsock socket) {
  Request * route = getRequest(socket);

  // parse other headers
  return NULL;
}

void socketHandler(tcpsock socket, Server *server) {
  // read entirety of socket into buffer
  // send to API parser
  // apiParser will handle JSON
  parseRequest(socket);

  char response[256];
  int responseCharacters = snprintf(response, sizeof(response), "Hello World");
  tcpsend(socket, response, responseCharacters, -1);
  tcpflush(socket, -1);
  tcpclose(socket);
}

void startServer(Server *server) {
  int port = 5555;
  char *hostAddress = NULL;
  
  ipaddr address = iplocal(hostAddress, port, 0);
  tcpsock listeningSocket = tcplisten(address);
  if (!listeningSocket) {
    return;
  }

  // accept socket connections, spawn a worker process request and call handler
  while(1) {
    tcpsock acceptedSocket = tcpaccept(listeningSocket, -1);
    if (!acceptedSocket) {
      continue;
    }
    
    go(socketHandler(acceptedSocket, server));
  }
}



