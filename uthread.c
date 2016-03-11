#include "types.h"
#include "user.h"
#include "x86.h"  //TODO make sure this is needed

int thread_create(void *(*start_routine)(void*), void *arg){
  //TODO 
  return 0;

}


void lock_init(lock_t *mlock){
  //TODO
}
void lock_acquire(lock_t * mlock){
  //TODO
}

void lock_release(lock_t * mlock){
//TODO
}

