#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// for sleep definition
#include <unistd.h>

#include <libmill.h>

void worker(int count, const char *text) {
  int i;
  for (i = 0; i != count; ++i) {
    printf("%s\n", text);
    msleep(10);
  }
}

int main(int argc, char *argv[]) {
  go(worker(5, "a"));
  go(worker(2, "b"));
  go(worker(3, "c"));

  msleep(10000000000);
  return 0;
}

