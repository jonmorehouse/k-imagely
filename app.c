#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libmill.h>

#include "app.h"

void errorHandler(tcpsock socket, Request * request) {
  // TODO: implement error handler

  printf("%s\n", "error handler goes here");
}

void routeHandler(Request * request) {
  // TODO: implement router
  // TODO: implement middleware here if its needed - IE: json parser?

  printf("%s\n", "router");
}


