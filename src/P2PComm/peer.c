// C program to demonstrate peer to peer chat using Socket Programming
#include <arpa/inet.h>
#include <netinet/in.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

void sending();
void receiving(int client_fd);
void *receive_thread(void *client_fd);
void DieWithError(char *errorMessage); /* Error handling function */

char *cName;
unsigned short cPort;
char *cIP;

int main(int argc, char const *argv[]) {

  cName = (char *)malloc(20);
  cIP = (char *)malloc(20);

  if (argc < 3) /* Test for correct number of arguments */
  {
    fprintf(stderr, "Usage: %s <Client Name> <Client IP> <Cleint Port>\n",
            argv[0]);
    exit(1);
  }

  strcpy(cName, argv[1]);
  strcpy(cIP, argv[2]);
  cPort = atoi(argv[3]);

  int client_fd, new_socket, valread;
  struct sockaddr_in address;
  int k = 0;

  // Creating socket file descriptor
  if ((client_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0) {
    DieWithError("socket() failed");
  }
  // Forcefully attaching socket to the port

  address.sin_family = AF_INET;
  address.sin_addr.s_addr = inet_addr(cIP);
  address.sin_port = htons(cPort);

  if (bind(client_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
    DieWithError("bind failed");
  }
  if (listen(client_fd, 5) < 0) {
    DieWithError("listen");
  }
  int ch;
  pthread_t tid;
  pthread_create(
      &tid, NULL, &receive_thread,
      &client_fd); // Creating thread to keep receiving message in real time
  printf("\n*****At any point in time press the following:*****\n1.Send "
         "message\n0.Quit\n");
  printf("\nEnter choice:");
  do {

    scanf("%d", &ch);
    switch (ch) {
    case 1:
      sending();
      break;
    case 0:
      printf("\nLeaving\n");
      break;
    default:
      printf("\nWrong choice\n");
    }
  } while (ch);

  close(client_fd);

  return 0;
}

// Sending messages to port
void sending() {

  char buffer[2000] = {0};
  // Fetching port number
  char ip_send[40];
  int port_send;

  // IN PEER WE TRUST
  printf("Enter the IP address to send message:");
  scanf("%s", ip_send);
  printf("Enter the port to send message:");
  scanf("%d", &port_send);

  int sock = 0, valread;
  struct sockaddr_in send_addr;
  char hello[1024] = {0};
  if ((sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0) {
    DieWithError("Socket creation error");
  }

  send_addr.sin_family = AF_INET;
  send_addr.sin_addr.s_addr = inet_addr(ip_send);
  send_addr.sin_port = htons(port_send);

  if (connect(sock, (struct sockaddr *)&send_addr, sizeof(send_addr)) < 0) {
    DieWithError("Connection Failed");
  }

  char dummy;
  printf("Enter your message:");
  scanf("%c", &dummy); // The buffer is our enemy
  scanf("%[^\n]s", hello);
  sprintf(buffer, "%s[PORT:%d] says: %s", cName, cPort, hello);
  send(sock, buffer, sizeof(buffer), 0);
  printf("\nMessage sent\n");
  close(sock);
}

// Calling receiving every 2 seconds
void *receive_thread(void *client_fd) {
  int s_fd = *((int *)client_fd);
  while (1) {
    sleep(2);
    receiving(s_fd);
  }
}

// Receiving messages on our port
void receiving(int client_fd) {
  struct sockaddr_in address;
  int valread;
  char buffer[2000] = {0};
  int addrlen = sizeof(address);
  fd_set current_sockets, ready_sockets;

  // Initialize my current set
  FD_ZERO(&current_sockets);
  FD_SET(client_fd, &current_sockets);
  int k = 0;
  while (1) {
    k++;
    ready_sockets = current_sockets;

    if (select(FD_SETSIZE, &ready_sockets, NULL, NULL, NULL) < 0) {
      DieWithError("Error");
    }

    for (int i = 0; i < FD_SETSIZE; i++) {
      if (FD_ISSET(i, &ready_sockets)) {

        if (i == client_fd) {
          int client_socket;

          if ((client_socket = accept(client_fd, (struct sockaddr *)&address,
                                      (socklen_t *)&addrlen)) < 0) {
            DieWithError("accept");
          }
          FD_SET(client_socket, &current_sockets);
        } else {
          valread = recv(i, buffer, sizeof(buffer), 0);
          printf("\n%s\n", buffer);
          FD_CLR(i, &current_sockets);
        }
      }
    }

    if (k == (FD_SETSIZE * 2))
      break;
  }
}