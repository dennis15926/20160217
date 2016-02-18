#How to run the system
####Server: sledge
Open two terminal windows. In one, enter make qemu-gdb (or make qemu-nox-gdb). This starts up QEMU, but QEMU stops just before the processor executes the first instruction and waits for a debugging connection from GDB. In the second terminal, from the same directory you ran make, run gdb. (Briefly, gdb -q -iex "set auto-load safe-path /home/csprofs/nael/xv6-master/" . Change the last part to your path to the xv6 directory. You should see something like this

#Files that plan to change
- sysproc.c add the real implementation of your method here
- syscall.h define the position of the system call vector that connect to your implementation
- user.h define the function that can be called through the shell
- syscall.c external define the function that connect the shell and the kernel, use the position defined in syscall.h to add the function to the system call vector
- usys.S use the macro to define connect the call of user to the system call function
- defs.h add a forward declaration for your new system call (edited by itzhaki)

