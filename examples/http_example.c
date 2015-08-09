#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

/*
 * https://en.wikipedia.org/wiki/Berkeley_sockets
 * https://en.wikipedia.org/wiki/Reentrancy_(computing)
*/

int main() {
  int create_socket, new_socket;
  socklen_t addrlen;
  int bufsize = 1024;
  char *buffer = malloc(bufsize);
  struct sockaddr_in address;

  if ((create_socket = socket(AF_INET, SOCK_STREAM, 0)) > 0) {
    printf("The socket was created\n");
  }

  address.sin_family = AF_INET;
  address.sin_addr.s_addr = INADDR_ANY;
  address.sin_port = htons(15000);

  if (bind(create_socket, (struct sockaddr *) &address, sizeof(address)) == 0) {
    printf("Binding Socket\n");
  }

  while (1) {
    if (listen(create_socket, 10) < 0) {
      perror("Server: unable to listen on created socket");
      exit(1);
    }

    if ((new_socket = accept(create_socket, (struct sockaddr *) & address, &addrlen)) < 0) {
      perror("Server: unable to accept connections on created socket");
      exit(1);
    }

    if (new_socket > 0) {
      printf("Server: client connection successful\n");
    }

    recv(new_socket, buffer, bufsize, 0);
    printf("%s\n", buffer);
    write(new_socket, "hello world\n", 12);
    close(new_socket);
  }

}
