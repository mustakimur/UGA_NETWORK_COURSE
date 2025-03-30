#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include <string.h>

#define SHM_SIZE 1024 // Shared memory size

int main() {
  int shmid;
  char *shared_memory;
  key_t key = 1234; // Unique key for shared memory

  // Create shared memory
  shmid = shmget(key, SHM_SIZE, IPC_CREAT | IPC_EXCL | 0666);
  if (shmid == -1) {
    perror("shmget failed");
    exit(1);
  }

  // Attach shared memory
  shared_memory = (char *)shmat(shmid, NULL, 0);
  if (shared_memory == (char *)-1) {
    perror("shmat failed");
    exit(1);
  }

  // Initialize shared memory
  strcpy(shared_memory, "Initial Data from Parent");

  pid_t pid = fork(); // Create child process

  if (pid < 0) {
    perror("fork failed");
    exit(1);
  }

  if (pid == 0) { // Child process
    sleep(2);     // Delay to let parent write first
    printf("Child reads: %s\n", shared_memory);
    strcpy(shared_memory, "Updated Data from Child");
    printf("Child updates shared memory.\n");
    shmdt(shared_memory); // Detach
    exit(0);
  } else { // Parent process
    sleep(1);
    printf("Parent wrote: %s\n", shared_memory);
    sleep(3);
    printf("Parent sees after child update: %s\n", shared_memory);
    shmdt(shared_memory); // Detach

    // Remove shared memory after child finishes
    shmctl(shmid, IPC_RMID, NULL);
  }

  return 0;
}
