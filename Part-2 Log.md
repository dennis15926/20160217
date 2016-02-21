#How to run the system
####Server: sledge
Open two terminal windows. In one, enter make qemu-gdb (or make qemu-nox-gdb). This starts up QEMU, but QEMU stops just before the processor executes the first instruction and waits for a debugging connection from GDB. In the second terminal, from the same directory you ran make, run gdb. (Briefly, gdb -q -iex "set auto-load safe-path /home/csprofs/nael/xv6-master/" . Change the last part to your path to the xv6 directory. You should see something like this

#Files that plan to change
- **sysproc.c** add the real implementation of your method here
- **syscall.h** define the position of the system call vector that connect to your implementation
- **user.h** - define the function that can be called through the shell
- **syscall.c** external define the function that connect the shell and the kernel, use the position defined in syscall.h to add the function to the system call vector
- **usys.S** use the macro to define connect the call of user to the system call function
- **defs.h** add a forward declaration for your new system call (edited by itzhaki)
- **Makefile**
- **pointer.c**: User function entry
- **proc.c**: implement function that relative to sys_new_function.
- **proc.h**: add functions that implemented in proc.c declare here.

######一些说明	
上面是添加系统调用的一些基本更改，若想改变系统调用（pointer）的实现，只需要改变proc.c里面的pointer就好（因为syscall.c里面的sys_pointer直接调用的pointer）
	
	

#Plan
1. 寻找分配内存的代码，添加null pointer监测
	- pointer地址的监测？ <- 代码的pointer执行时如何传递？ <- xv6如何执行存在memory里面的程序？<- 当运行pointer的时候，xv6发生了什么？(程序/代码是怎么执行的？)
	- exec如何申请变量空间给指针? 
	- 是否已经存在非法变量空间赋值的监测，只是因为当前0x0000为合法地址而略过？
2. 找出存储page初始分配值的变量，将其改为0x1000


##待解决的问题：
1. fork和内存分配的关系？
2. 输入一个指向非法地址的参数时如何处理？

#一些已知的条件
1. 若程序成功开始执行，fork将被调用，父进程wait，子进程执行程序的指令。 

#参考资料
1. [中文版xv6档案](https://th0ar.gitbooks.io/xv6-chinese/content/content/chapter0.html)


#Notes
	char *argv[3];
	argv[0] = "echo";
	argv[1] = "hello";
	argv[2] = 0;
	exec("/bin/echo", argv);
	printf("exec error\n");
xv6 shell 用以上调用为用户执行程序。shell 的主要结构很简单，详见 main 的代码（8001）。主循环通过 getcmd 读取命令行的输入，然后它调用 fork 生成一个 shell 进程的副本。父 shell 调用 wait，而子进程执行用户命令。举例来说，用户在命令行输入“echo hello”，getcmd 会以 echo hello 为参数调用 runcmd（7906）, 由 runcmd 执行实际的命令。对于 echo hello, runcmd 将调用 exec 。如果 exec 成功被调用，子进程就会转而去执行 echo 程序里的指令。在某个时刻 echo 会调用 exit，这会使得其父进程从 wait 返回。你可能会疑惑为什么 fork 和 exec 为什么没有被合并成一个调用，我们之后将会发现，将创建进程——加载程序分为两个过程是一个非常机智的设计。


#Try - 1
1. 根据[这个github](https://github.com/rschmukler/cs537-p3/commit/159f5e9407361a1dd9c1c33999100fe533871f9b)上面的code进行更改