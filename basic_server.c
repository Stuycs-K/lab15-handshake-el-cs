#include "pipe_networking.h"
#include <unistd.h>

int randint2() {
  int buff[1];
  int file = open("/dev/urandom", O_RDONLY, 0);
  read(file, buff, 4);
  close(file);
  return *buff;
}

int main() {
  int to_client;
  int from_client;

  from_client = server_handshake( &to_client );
  close(to_client);

  while (1) {
    int n = (int)((unsigned int)randint2() % 101);
    printf("Sending %d to client(s)\n", n);
    write(to_client, &n, sizeof(int));
    sleep(1);
  }
  close(to_client);
  close(from_client);
}
