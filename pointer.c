#include "types.h"
#include "user.h"
#include "syscall.h"

int
main(int argc, char *argv[]){
	int *p = 0;
	printf(1, "before\n");
	*p = 5;
	printf(1, "after:%d\n", *p);	
	return 0;
}