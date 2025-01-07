#include "pipe_networking.h"

int main() {

  int to_server;
  int from_server;

  from_server = client_handshake( &to_server );

  while (1) {
    int n;
    int r = read(from_server, &n, sizeof(int));
    if (r <= 0) break;
    printf("Client received int: %d\n", n);

    char buff[100];
    sprintf(buff, "%d", n * 2 + 1);
    int w = write(to_server, buff, 100);
    if (w <= 0) break;
    printf("Client sent string: %s\n", buff);
  }
}
