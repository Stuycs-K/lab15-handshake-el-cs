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
  int from_client = open(WKP, O_WRONLY, 0777);
  close(f);
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
  read(SYN, buff, 100);
  printf("server opening private pipe\n");
  int pp = open(buff, O_RDONLY, 0777);
  *to_client = pp;
  printf("server sending SYN_ACK\n");
  long * p = &(long)randint();
  int pp2 = open(buff, O_WRONLY, 0777);
  write(pp2, (char *)p, 100);
  printf("server reading final ACK\n");
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
  int from_server;
  char pp[100];
  sprintf(pp, "%d", getpid());
  printf("client making private pipe\n");
  mkfifo(pp, 0777);
  printf("client opening WKP\n");
  int wkp = open(WKP, O_WRONLY, 0777);
  printf("client writing PP to WKP\n");
  int pp = open(pp, O_RDONLY, 0777);
  write()
  // write pp to wkp
  // open pp
  // delete pp
  // read SYN_ACK
  // send ACK
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
