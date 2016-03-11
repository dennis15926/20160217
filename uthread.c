#include "types.h"
#include "user.h"
#include "x86.h"
#define PGSIZE (4096)

//Allocates new memory for child stack, when child returns, call
//the routine pointed by start_routine argument passed with arg.
//Then the child frees the stack and exits. The parent returns
//the pid of the child
int thread_create(void *(*start_routine)(void*), void *arg){
  void *stack = malloc(PGSIZE);
  int t_pid = clone(stack, PGSIZE);
  if(t_pid == 0){
    (*start_routine)(arg);
    free(stack);
    exit();
  }
  else
    return cthread_pid;
}


void lock_init(lock_t *lck){
  *lck=0;//1 is held, 0 is avaliable
}
void lock_acquire(lock_t *lck){
  while(xchg(mlock,1)!=0)//already 1, held
    ;//spin
  return;//received lock
}

void lock_release(lock_t * lck){
  *mlock = 0;
}

