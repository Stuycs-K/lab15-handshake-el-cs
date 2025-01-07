#include "pipe_networking.h"

int randint() {
  int buff[1];
  int file = open("/dev/urandom", O_RDONLY, 0);
  read(file, buff, 4);
  close(file);
  return *buff;
}

//UPSTREAM = to the server / from the client
//DOWNSTREAM = to the client / from the server
/*=========================
  server_setup

  creates the WKP and opens it, waiting for a  connection.
  removes the WKP once a connection has been made

  returns the file descriptor for the upstream pipe.
  =========================*/
int server_setup() {
  printf("server making pipe\n");
  mkfifo(WKP, 0777);
  printf("server opening wkp\n");
  int from_client = open(WKP, O_RDONLY, 0777);
  printf("server removing wkp\n");
  remove(WKP);
  return from_client;
}

/*=========================
  server_handshake
  args: int * to_client

  Performs the server side pipe 3 way handshake.
  Sets *to_client to the file descriptor to the downstream pipe (Client's private pipe).

  returns the file descriptor for the upstream pipe (see server setup).
  =========================*/
int server_handshake(int *to_client) {
  int from_client = server_setup();
  char buff[100];
  printf("server reading SYN\n");
  read(from_client, buff, 100);
  printf("server opening private pipe (%s)\n", buff);
  int pp = open(buff, O_WRONLY, 0777);
  *to_client = pp;
  printf("server sending SYN_ACK\n");
  int p = randint();
  char buff2[100];
  sprintf(buff2, "%d", p);
  write(pp, buff2, 100);
  printf("server reading final ACK\n");
  char buff3[100];
  read(from_client, buff3, 100);
  int n;
  sscanf(buff3, "%d", &n);
  if (p + 1 == n) printf("handshake successful\n");
  else printf("handshake failed\n");
  return from_client;
}


/*=========================
  client_handshake
  args: int * to_server

  Performs the client side pipe 3 way handshake.
  Sets *to_server to the file descriptor for the upstream pipe.

  returns the file descriptor for the downstream pipe.
  =========================*/
int client_handshake(int *to_server) {
  char pp[100];
  sprintf(pp, "%d", getpid());
  printf("client making private pipe (%s)\n", pp);
  mkfifo(pp, 0777);
  printf("client opening WKP\n");
  int wkp = open(WKP, O_WRONLY, 0777);
  *to_server = wkp;
  printf("client writing PP to WKP\n");
  write(wkp, pp, 100);
  printf("client opening PP\n");
  int ppf = open(pp, O_RDONLY, 0777);
  int from_server = ppf;
  printf("client deleting PP\n");
  remove(pp);
  printf("client reading SYN_ACK\n");
  char buff[100];
  read(ppf, buff, 100);
  int n;
  sscanf(buff, "%d", &n);
  printf("client sending ACK\n");
  sprintf(buff, "%d", n+1);
  write(wkp, buff, 100);
  return from_server;
}


/*=========================
  server_connect
  args: int from_client

  handles the subserver portion of the 3 way handshake

  returns the file descriptor for the downstream pipe.
  =========================*/
int server_connect(int from_client) {
  int to_client  = 0;
  return to_client;
}

void server_handshake_half(int *to_client, int from_client) {
  char buff[100];
  printf("server reading SYN\n");
  read(from_client, buff, 100);
  printf("server opening private pipe (%s)\n", buff);
  int pp = open(buff, O_WRONLY, 0777);
  *to_client = pp;
  printf("server sending SYN_ACK\n");
  int p = randint();
  char buff2[100];
  sprintf(buff2, "%d", p);
  write(pp, buff2, 100);
  printf("server reading final ACK\n");
  char buff3[100];
  read(from_client, buff3, 100);
  int n;
  sscanf(buff3, "%d", &n);
  if (p + 1 == n) printf("handshake successful\n");
  else printf("handshake failed\n");
}
