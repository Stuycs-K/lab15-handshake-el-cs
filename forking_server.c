#include "pipe_networking.h"
#include <unistd.h>
#include <signal.h>

static void sighandler(int signo) {
  if (signo == SIGINT) {
    printf("SIGINT received\n");
    remove(WKP);
    exit(0);
  }
}

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

  signal(SIGINT, sighandler);
  signal(SIGPIPE, SIG_IGN);

  while (1) {
    from_client = server_setup();

    pid_t p = fork();
    if (p < 0);
    else if (p == 0) {
      server_handshake_half(&to_client, from_client);

      while (1) {
        int n = (int)((unsigned int)randint2() % 101);
        printf("Sending %d to client(s)\n", n);
        int w = write(to_client, &n, sizeof(int));
        if (w <= 0) break;
        char buff[100];
        int r = read(from_client, buff, 100);
        if (r <= 0) break;
        printf("Received \"%s\" from client\n", buff);
        sleep(1);
      }

      exit(0);
    }

    close(from_client);
    close(to_client);
  }
}
