#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <libmill.h>

typedef enum {
  INVALID_PORT,
} ERRORS;

struct Config {
  char *unparsedPort;
  int port;
};

// global config object
struct Config config = {
  .unparsedPort = "8000",
  .port = 8000,
};

int parseConfig(int argc, char **argv) {
  char ** configItem = NULL;

  for (int i=0; i < argc; ++i) {
    char *option = argv[i];

    if (configItem) {
      *configItem = option;
      configItem = NULL;
      continue;
    }

    if (strncmp(option, "--port", 5) == 0) {
      configItem = &config.unparsedPort;
    }
  }

  // check validity of port
  int parsedPort = atoi(config.unparsedPort);
  if (parsedPort) {
    config.port = parsedPort;
  } else {
    return INVALID_PORT;
  }

  return 0;
}

int main(int argc, char *argv[]) {
  int err = parseConfig(argc, argv);
  if (err) {
    return err;
  }

  /*int server = createServer(handler);*/

  return 0;
}
