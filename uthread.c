#include "types.h"
#include "user.h"
#include "x86.h"  //TODO make sure this is needed

int thread_create(void *(*start_routine)(void*), void *arg){
  //TODO 
  return 0;

}


void lock_init(lock_t *lck){
  *lck=0;
}
void lock_acquire(lock_t *lck){
  while(xchg(mlock,1)!=0)//already 1, held
    ;//spin
  return;//received lock
}

void lock_release(lock_t * lck){
  *mlock = 0;
  return;
}

