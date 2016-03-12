#include "types.h"
#include "stat.h"
#include "user.h"
#include "uthread.h"

struct lock_t t;
int count;
int exitThread;

void* update(void* a) {
  int passNumber = (int)a;
  // printf(1, "passNumber = %d\n", passNumber);
  // printf(1, "current count = %d\n", count);
  int pid = getpid();
  printf(1, "pid %d try to update\n", pid);
  while(1){
    lock_acquire(&t, pid);
      if(count>=passNumber){
        lock_release(&t, pid);
        break;
      }
      printf(1, "pid %d gets the lock and starts to update\n", pid);
      count = count + 1;
      printf(1, "pid %d updated finish, current count = %d\n", pid, count);
    lock_release(&t, pid);
  }
  return 0;
}

int
main (int argc, char* argv[]) {
  lock_init(&t);
  int threadNumber = atoi(argv[1]);
  int passNumber   = atoi(argv[2]);
  printf(1,"%d, %d\n", threadNumber, passNumber);
  int parent = getpid();
  count = 0;
  exitThread = 0;
  int i, pid;

  if (argc != 3 || threadNumber < 1 || passNumber < 0) {
    printf(1, "Input error\nFunction Syntax: test numberOfThreads numberOfRuns\n");
    exit();
  }

  for (i = 0; i < threadNumber; i++) {
    thread_create(update, (void*)passNumber);
  }

  pid = getpid();
  if (pid == parent) {
    while(exitThread < threadNumber){
      printf(1,"Threads exited amount: %d\n", exitThread);
      if(wait()!=-1){
        exitThread++;
      }
    }
  }

  printf(1, "pid: %d exiting\n", pid);
  exitThread = exitThread + 1;
  exit();
}
