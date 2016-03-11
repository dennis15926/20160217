#include "types.h"
#include "stat.h"
#include "user.h"

lock_t* t;
int count;
int exitThread;

void update(int runs) {
  printf(1, "current count = %d\n", count);
  int pid = getpid();
  printf(1, "pid %d try to update\n", pid);
  while(count < runs){
    lock_acquire(t);
      printf(1, "pid %d gets the lock and starts to update\n", pid);
      count = count + 1;
      printf(1, "pid %d updated finish, current count = %d\n", pid, count);
    lock_release(t);
  }
}

int
main (int argc, char* argv[]) {
  lock_init(&t);
  int threadNumber = atoi(argv[1]);
  int passNumber   = atoi(argv[2]);
  int parent = getpid();
  void (*fnc)(int);
  count = 0;
  exitThread = 0;
  fnc = &update;
  int i, pid;

  if (argc != 3 || threadNumber < 1 || passNumber < 1) {
    printf(1, "Input error\nUsage: test numberOfThreads(>0) numberOfRuns(>0)\n");
    exit();
  }
  
  for (i = 0; i < threadNumber; i++) {
   thread_create((void*)fnc, &passNumber);
  }
   
  pid = getpid();
  if (pid == parent) {
    while(exitThread < threadNumber){
      wait();
    }
  }

  printf(1, "pid: %d exiting\n", pid);
  exitThread = exitThread + 1;
  exit();
}

