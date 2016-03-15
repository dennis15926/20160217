#include "types.h"
#include "user.h"
#include "x86.h"
#include "uthread.h"
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
    return t_pid;
}


void lock_init(struct lock_t *lck){
  int i;
  for(i=0; i<threadAmount; ++i){
    (lck->lock)[i] = 0;   //0: no request, 1: request waiting
    lck->lockState = -1;  //-1 no lock, other is current lock.
  }
}

//Distribute initial lock
void get_current_lock(struct lock_t *lck){
  int i;
  if(lck->lockState == -1)
    for(i=0; i<threadAmount; ++i)
      if(lck->lock[i]){
        lck->lockState = 1;
        lck->lock[i] = 0;
        return ;
      }
}

void lock_acquire(struct lock_t *lck, int pid){
  int posi = pid%threadAmount;
  lck->lock[posi] = 1;
  get_current_lock(lck)
  while((lck->lock)[posi] == 1);
  return ; //get the lock

  // if(!(lck->lock)[lck->currentLock]){
  //   //if no lock now, place pid on the first of the line.
  //   (lck->lock)[lck->currentLock] = pid;
  //   return ;
  // }
  // else {
  //   //find the next available place to wait
  //   int i;
  //   for(i=(lck->currentLock+1)%threadAmount; i != lck->currentLock; i = (i+1)%threadAmount)
  //     if(!(lck->lock[i])){
  //       (lck->lock)[i] = pid;  //wait in line
  //       return;
  //     }
  // }
}

void lock_release(struct lock_t * lck, int pid){
  int posi = pid % threadAmount, i;
  lck->lock[posi] = 0;
  for(i = (posi+1) % threadAmount; i != posi; i = (i+1) % threadAmount)
  {
    if(lck->lock[i]){
      lck->lock[i] = 0;
      return ;
    }
  }
  //no request;
  lck->lockState = -1;
  // int temp = lck->currentLock;    //mark current lock place (to avoid 0 -> -1);
  // lck->currentLock = (lck->currentLock + 1) % threadAmount; //pass lock right first;
  // (lck->lock)[temp] = 0; //release lock;
}
