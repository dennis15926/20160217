#include "types.h"
#include "stat.h"
#include "user.h"

int main(int argc, char *argv[]){
  int* p = 0;
  printf(1, "%d\n", *p);
  *p = 5;
  printf(1, "%d\n", *p);
  exit();
}
