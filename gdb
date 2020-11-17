http://c.biancheng.net/gdb/
main函数传入参数
  gdb main  //先启动起来
  run aaaa bb
  
运行: r 
增加断点: break(b) 11
删除全部断点: delete
删除某个断点: delete 断点id 
             clear 
查看断点所有断点: info break 
查看线程信息: info threads
查看具体某个线程信息 : thread  22(线程id)
中断进程: ctrl + c
单步执行: n
单步执行进入函数: step  s
执行直到遇到断点:c 
打印信息: print  p
          display 自动显示变量
显示源文件:l
调用堆栈: bt

attach进程:gdb attach 进程id
查看进程信息: info proc
查看系统运行的进程: ps -aux | grep (main)
改变变量的值: set variable  变量名=


info args      打印出当前函数的参数名及其值。
info locals    打印出当前函数中所有局部变量及其值。
info catch     打印出当前的函数中的异常处理信息

4）源代码的内存
你可以使用info line命令来查看源代码在内存中的地址。info line后面可以跟“行号”，“函数名”，“文件名:行号”，“文件名:函
数名”，这个命令会打印出所指定的源码在运行时的内存地址，如：
(gdb) info line tst.c:func    Line 5 of "tst.c" starts at address 0x8048456 <func+6> and ends at 0x804845d <func+13>.

info break          查看断点信息。

info threads        看正在运行程序中的线程信息

info registers      查看寄存器的情况。（除了浮点寄存器）

info all-registers  查看所有寄存器的情况。（包括浮点寄存器）

info registers <regname >  查看所指定的寄存器的情况


6 pstack 是 Linux（比如 Red Hat Linux 系统、Ubuntu Linux 系统等）下一个很有用的工具，它的功能是打印输出此进程的堆栈信息

(gdb) bt：显示所有栈帧，backtrace。
(gdb) bt 10：显示前面10个栈帧。
(gdb) bt -10：显示后面10个栈帧。
(gdb) bt full：显示栈帧以及局部变量。
(gdb) bt full 10：显示前面10个栈帧以及局部变量。
(gdb) bt full -10：显示后面10个栈帧以及局部变量。
(gdb) frame <栈帧编号>：进入指定的栈帧中，然后可以查看当前栈帧中的局部变量，以及栈帧内容等信息。
(gdb) info frame <栈帧编号>：可以查看指定栈帧的详细信息。
(gdb) up：进入上层栈帧。
(gdb) down：进入下层栈帧。
















