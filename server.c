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

void parseRequestMethod(Request *request, char *value) {
  if (!strncmp(value, "GET", 3)) {
    request->HTTPMethod = HTTP_GET;
  } else if (!strncmp(value, "POST", 4)) {
    request->HTTPMethod = HTTP_POST;
  } else if (!strncmp(value, "PUT", 3)) {
    request->HTTPMethod = HTTP_PUT;
  } else if (!strncmp(value, "DELETE", 6)) {
    request->HTTPMethod = HTTP_DELETE;
  } else if (!strncmp(value, "OPTIONS", 7)) {
    request->HTTPMethod = HTTP_OPTIONS;
  } else {
    request->error = HTTP_INVALID_HTTP_METHOD;
  }
}

void parseQueryArgs(Request *request, char *input) {
  char *currentLine, *currentLineEnd, *keyValueEnd;
  QueryArg *currentArg, *lastArg = NULL;
  request->queryArg = NULL;

  currentLine = strtok_r(input, "&", &currentLineEnd);
  while (currentLine != NULL) {
    char * key, * value;
    key = strtok_r(currentLine, "=", &keyValueEnd);
    value = strtok_r(NULL, "=", &keyValueEnd);

    if (key != NULL && value != NULL) {
      currentArg = malloc(sizeof(QueryArg));
      currentArg->key = calloc(strlen(key) + 2, sizeof(char));
      strcpy(currentArg->key, "name");
      /*currentArg->key[5] = '\0';*/
      currentArg->value = value;
      currentArg->next = NULL;

      request->queryArgsCount = request->queryArgsCount + 1;

      // if this is the first queryArg, then the request struct needs to be updated
      if (request->queryArg == NULL) {
        request->queryArg = currentArg;
      } else {
        lastArg->next = currentArg;
      }
      
      lastArg = currentArg;
    }
    
    currentLine = strtok_r(NULL, "&", &currentLineEnd);
  }
}

Request * getRequest(tcpsock socket) {
  char method[8], uri[URI_MAXIMUM_LENGTH];
  Request * request = malloc(sizeof(Request));

  size_t size = tcprecvuntil(socket, method, 8, " ", 1, -1);
  if (errno) {
    request->error = errno;
    return request;
  } 
  
  parseRequestMethod(request, method);
  if (request->error) {
    return request;
  }

  size = tcprecvuntil(socket, uri, URI_MAXIMUM_LENGTH, " ?", 2, -1);
  if (errno) {
    request->error = errno;
    return request;
  } else if (uri[size - 1] == '?') {
    // seek the queryArgs from the socket
    char queryArgs[QUERY_ARG_MAXIMUM_LENGTH];
    size = tcprecvuntil(socket, queryArgs, QUERY_ARG_MAXIMUM_LENGTH, " ", 1, -1);
    // parse the args into the request object
    parseQueryArgs(request, queryArgs);
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
  Request * request = getRequest(socket);
  QueryArg * current = request->queryArg;

  while (current != NULL) {
    printf("%s\n", current->key);

    current = current->next;
  }

  // parse other headers
  return request;
}

void socketHandler(tcpsock socket, Server *server) {
  // read entirety of socket into buffer
  // send to API parser
  // apiParser will handle JSON
  Request *request = parseRequest(socket);
  free(request);

  /*if (request->error) {*/
    /*[>writeErrorResponse(request);<]*/
  /*} else {*/
    /*free(request);*/
  /*}*/

  /*Response *response = */

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
    
    socketHandler(acceptedSocket, server);
    /*go(socketHandler(acceptedSocket, server));*/
  }
}



