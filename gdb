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

7.    https://blog.csdn.net/jctian000/article/details/80695747
      thread apply all bt

7.    b main    main函数设置断点

8. 
gdb attach {pid} #gdb 调试运行的进程
info thread #进入以后使用，查看线程信息

info threads 显示当前可调试的所有线程，每个线程会有一个GDB为其分配的ID，后面操作线程的时候会用到这个ID。 前面有*的是当前调试的线程。 
thread ID 切换当前调试的线程为指定ID的线程。 
break thread_test.c:123 thread all 在所有线程中相应的行上设置断点（watch也可以指定thread）
thread apply ID1 ID2 command 让一个或者多个线程执行GDB命令command。 
thread apply all command 让所有被调试线程执行GDB命令command


tbreak 临时设置一次
break，tbreak可以根据行号、函数、条件生成断点。tbreak设置方法与break相同，只不过tbreak只在断点停一次，过后会自动将断点删除



tbreak 临时设置一次

break，tbreak可以根据行号、函数、条件生成断点。tbreak设置方法与break相同，只不过tbreak只在断点停一次，过后会自动将断点删除

 

附录：gdb  常用调试命令
-------------------------------------------------
(gdb) l ：（字母l）列出源码
(gdb) b n :在第n行处设置断点
(gdb) b func：在函数func()的入口处设置断点
(gdb) 条件断点：条件可以是任何合法的c 表达式。 例如 b n if val1==val2 当已经设置了断点，可以用condition 
      命令对断点号添加条件， 例: condition 2 val1==val2 , 注意，没有if 单词当对变量的改变更感兴趣时，可以用watch 命令
(gdb) info break： 查看断点信息  （更多断点类，见下）
(gdb) r：运行程序
(gdb) n：单步执行
(gdb) s：单步调试如果有函数调用，则进入函数；与命令n不同，n是不进入调用的函数的
(gdb) c：继续运行
(gdb) p 变量 ：打印变量的值     也能够修改变量的值（用 = 赋值） // 打印寄存器值。 p $eax
(gdb) x /nfu <addr> 显示内存  // n为个数，f 为格式，u为每单元长度
      命令:x /3uh 0x54320 表示,从内存地址0x54320读取内容,h表示以双字节为一个单位,3表示输出三个单位,u表示按十六进制显示。

(gdb) bt：查看函数堆栈
(gdb) finish：退出函数
(gdb) display <var> 每次中断或单步都显示你关心的变量
(gdb)undisplay <编号>
(gdb) shell 命令行：执行shell命令行
(gdb) set args 参数:指定运行时的参数
(gdb) show args：查看设置好的参数
(gdb)info program： 来查看程序的是否在运行，进程号，被暂停的原因。 // 打印寄存器数组， info reg,  简写 i reg； info threads(注意有s)
(gdb)clear 行号n：清除第n行的断点
(gdb)delete 断点号n：删除第n个断点
(gdb)disable 断点号n：暂停第n个断点
(gdb)enable 断点号n：开启第n个断点

9  l                 显示10 行源码
   l  6 20           表示查看6-20的源码
   l  main           表示显示main函数周围10行源码
   l 文件名：数字      表示查看tst.c文件第6行周围的10行代码
   l 文件名：函数名     表示查看tst.c文件中main周围10行代码
   l -命令            表示查看上一个l命令查看的代码之前的10行

10
    gdb中跳入函数的命令是step，相当于Visual Studio中的快捷键F11
    gdb中跳出函数的命令是finish，相当于Visual Studio中的快捷键Shift+F11，函数完整执行后返回
    gdb中还有一个直接返回的命令是return，它会跳过当前函数后面的语句直接返回，返回值可以自定义，紧跟在return命令后面即可

11
print /x var 
这里可以知道，print可以指定显示的格式，这里用'/x'表示16进制的格式。 
可以支持的变量显示格式有： 
x  按十六进制格式显示变量。 
d  按十进制格式显示变量。 
u  按十六进制格式显示无符号整型。 
o  按八进制格式显示变量。 
t  按二进制格式显示变量。 
a  按十六进制格式显示变量。 
c  按字符格式显示变量。 
f  按浮点数格式显示变量。 

info source 
这样会显示当前所在的源代码文件信息,例如文件名称，程序语言等。 

*删除N号断点： 
(gdb) delete N 

*删除所有断点： 
(gdb) delete 

gdb -tui 
这样,使用了'-tui'选项，启动可以直接将屏幕分成两个部分，上面显示源代码，比用list方便多了。这时候使用上下方向键可以查看源代码,想要命令行使用上下键就用[Ctrl]n和[Ctrl]p. 

*指定程序直到退出当前循环体： 
(gdb) until 
或(gdb) u 

jump 5 
这里，可以简写为"j 5"需要注意的是，跳转到第5行执行完毕之后，如果后面没有断点则继续执行，而并不是停在那里了。 
另外，跳转不会改变当前的堆栈内容，所以跳到别的函数中就会有奇怪的现象，因此最好跳转在一个函数内部进行,跳转的参数也可以是程序代码行的地址,函数名等等类似list.


查看当前程序栈的信息: info frame----list general info about the frame
查看当前程序栈的参数: info args---lists arguments to the function
查看当前程序栈的局部变量: info locals---list variables stored in the frame


jump <location>
location 可以是程序的行号或者函数的地址，jump 会让程序执行流跳转到指定位置执行，当然其行为也是不可控制的，
例如您跳过了某个对象的初始化代码，直接执行操作该对象的代码，那么可能会导致程序崩溃或其他意外行为。jump 命令可以简写成 j，
但是不可以简写成 jmp，其使用有一个注意事项，即如果 jump 跳转到的位置后续没有断点，那么 GDB 会执行完跳转处的代码会继续执行

gdb -tui ./scsensord core

catch throw         
catch throw int    <-- 指定捕获“throw int”事件

编译器默认没有把宏定义扩展信息编译进二进制文件    需要加入-g3 和-gdwarf-2

13 where 查看调用堆栈

14 
1. until
这个用于执行完循环。
在执行完循环体内的最后一条语句之后执行 until, 就会执行完循环体到后面的一个语句停下。
2. finish
执行完当前的函数。
3. tui
是一个命令行的界面，能同时把代码显示出来







