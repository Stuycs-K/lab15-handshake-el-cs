#include "pipe_networking.h"

int main() {

  int to_server;
  int from_server;

  from_server = client_handshake( &to_server );

  while (1) {
    int n;
    read(from_server, &n, sizeof(int));
    printf("Client received int: %d\n", n);
  }
}
