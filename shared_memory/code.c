#include <stdio.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <unistd.h>

typedef struct Item {
  char name[100];
  char ip[32];
  int port;
} data_t;

int main() {
  int shm_id;
  key_t key = 1234;
  data_t *data[10];
  unsigned int size = sizeof(data) * 10;

  shm_id = shmget(key, size, IPC_CREAT | IPC_EXCL | 0666);

  *data = (data_t *)shmat(shm_id, 0, 0);

  data[0] = malloc(sizeof(data));
  data[1] = malloc(sizeof(data));
  strcpy(data[0]->name, "user1");
  strcpy(data[1]->name, "user2");

  printf("%s\n", data[0]->name);
  printf("%s\n", data[1]->name);

  int pid = fork();

  strcpy(data[1]->name, "user3");

  if (pid > 0) {
    sleep(1);
  }
  if (pid == 0) {
    printf("%s\n", data[0]->name);
    printf("%s\n", data[1]->name);
    exit(0);
  }

  return 0;
}