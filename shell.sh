1. 自动化批量系统初始化程序(update, 软件安装, 时区设置, 安全策略..)
2. 自动化批量软件部署程序(LAMP, LNMP, Tomcat, LVS, Nginx)
3. 管理应用程序(KVM, 集群管理扩容, MySql)
4. 日志分析处理程序(PV, UV, 200, !200, top 100, grep/awk) 
       PV是page view的缩写，  bai即页面浏览量  
       UV是unique visitor的简写，是指通过互联网访问、浏览这个网页的自然人。   
       状态码，
       前100访问量，

5. 自动化备份恢复程序(MySql 完全备份/ 增量备份+ Crond )
6. 自动化管理程序(批量远程修改密码, 软件升级, 配置更新)
7. 自动化信息采集及监控程序(收集系统/ 应用状态信息, cpu, mem, disk, net, tcp, status, apache, mysql)


/etc/profile
/etc/bashrc           系统级

~/.bash_profile     用户级
~/.bashrc
~/.bash_logout      离开时执行
~/.bash_history      关闭终端时执行

8 ! 数字    数字代表历史命令中顺序为数字的命令  数字可以是负数，代表倒数命令，如!-2 倒数第二个命令
   ! 字母   !find  #执行上条以find开头的命令
   !! 执行上一次命令  可以在 !! 前额外增加内容. 如上一次 vim log.txt   , 加上权限  sudo !!.
   !^ 使用上条命令的第一个参数
   !$  上一条命令的最后一个参数
   !:-  执行上条命令，但不带上最后一个参数
   !*  上一条命令的所有参数

8 $0 这个程式的执行名字
   $n 这个程式的第n个参数值，n=1..9
   $* 这个程式的所有参数,此选项参数可超过9个。
   $# 这个程式的参数个数
   $$ 这个程式的PID(脚本运行的当前进程ID号)
   $! 执行上一个背景指令的PID(后台运行的最后一个进程的进程ID号)
   $? 执行上一个指令的返回值 (显示最后命令的退出状态。0表示没有错误，其他任何值表明有错误)
   $- 显示shell使用的当前选项，与set命令功能相同
   $@ 跟$*类似，但是可以当作数组用 
    //可以看到不加引号时,二者都是返回传入的参数,但加了引号后,此时$*把参数作为一个字符串整体(单字符串)返回,
    //$@把每个参数作为一个字符串返回


9 more 命令
 分页显示文本内容  more file_name

10 Linux eject命令用于退出抽取式设备。 如 光盘 ，磁带
11 可以用分号; 分割命令，然后逐步执行  
12  &&可用于判断上一个命名是否成功，成功后执行下一个命令
13  ||无论上一个命名是否成功，都执行下一个命令
假设你的 umask 为 003 ，请问该 umask 情況下，建立的文件和目录的权限分为多少
14   command  &   后台执行
       command &>  混合重定向
       command1 && command2 逻辑判断

15 ping -c1    数字1代表ping 一次

16 shell 通配符( 和正则表达式定义不同)
  ls in*   所有以in开头的文件
  *  任意多个字符
  ？ 任意一个字符
 [ ]  匹配里面任意一个字符     ^ 代表非  shell 中不区分大小写[a-z]  [A-Z] 效果相同
      [abc] [a-z] [A-Z] [^ ]
 ( )  在子shell 中执行
 { }  集合 
      mkdir -pv /home/{33/{aa,bb},44}
      cp -rv /etc/ifcg-eth0  /etc/ifcg-eth0.old -> cp -rv /etc/ifcg-eth0{, .old}
 \  转义
       


17 umask 
    假设你的 umask 为 003 ，请问该 umask 情況下，建立的文件和目录的权限分为多少
     umask 为 003 ，所以拿掉的权限为 --------wx，因此：
     文件： (-rw-rw-rw-) - (--------wx) = -rw-rw-r--
     目录： (drwxrwxrwx) - (d-------wx) = drwxrwxr--
   
  综合 16 17
  -> (umask 007; touch 01.txt);ll 01.txt
  -> -rw------- 1 miao miao  01.txt
    
18 前景色  背景色
    前景色 30--37
    背景色  40--47 
    echo -e "\e[1;32m this is a red text. \e[0m"
     -e 代表要解释后面语句

19  printf  命令
 
20   shell 变量   用固定的字符串表示不固定的内容
       以字母 下划线开头，区分大小写

21  if 语句

 if ping -c1 192.168.0.174 &>/dev/null; then
              echo "ip is up"
      else
               echo "ip is down"

i、ping -c1 192.168.0.174 &>/dev/null
    if [$? -eq 1] ;then
              echo "ip is up"
      else
               echo "ip is down"

22 type   输出语句类型， 

23 
-eq           //等于
-ne           //不等于
-gt            //大于 （greater ）
-lt            //小于  （less）
-ge            //大于等于
-le            //小于等于

命令的逻辑关系：
在linux 中 命令执行状态：0 为真，其他为假
逻辑与： &&
第一个条件为假时，第二条件不用再判断，最终结果已经有；
第一个条件为真时，第二条件必须得判断；
逻辑或： ||
逻辑非： ！

24 $1  $2  输入参数 类似main() shell 是从0开始

25 export 
     自定义变量在当前shell 中有效
     环境变量在当前shell 和子shell中都有效

26 source filename 与 sh filename 及./filename执行脚本的区别在那里呢？
1.当shell脚本具有可执行权限时，用sh filename与./filename执行脚本是没有区别得。
  ./filename是因为当前目录没有在PATH中，所有"."是用来表示当前目录的。

2.sh filename 重新建立一个子shell，在子shell中执行脚本里面的语句，该子shell继承父shell的环境变量，
   但子shell新建的、改变的变量不会被带回父shell，除非使用export。

3.source filename：这个命令其实只是简单地读取脚本里面的语句依次在当前shell里面执行，没有建立新的子shell。
  那么脚本里面所有新建、改变变量的语句都会保存在当前shell里面

27 source 就是. 命令    source命令也称为“点命令”，也就是一个点符号（.）,是bash的内部命令

28 env  输出当前环境变量

29 单引号中内容不解释

30 basename  
     dirname

31 -f 判断是否是一个文件

32 主要 `    '  两个符号的区别 `

33 read  从键盘读入命令
    -n  需要的字符数
    -t   等待时间秒数
    -p  提示符

34  “  双引号 弱引用
       ’单引号强引用

35  date %F 完整日期格式

36   文件表达式 

-e filename 如果 filename存在，则为真
-d filename 如果 filename为目录，则为真 
-f filename 如果 filename为常规文件，则为真
-L filename 如果 filename为符号链接，则为真
-r filename 如果 filename可读，则为真 
-w filename 如果 filename可写，则为真 
-x filename 如果 filename可执行，则为真
-s filename 如果文件长度不为0，则为真
-h filename 如果文件是软链接，则为真
    
37 `  反引号
     反引号是命令替换，命令替换是指Shell可以先执行``中的命令，将输出结果暂时保存，在适当的地方输出
     ` date +%F`  等同于 $(date +%F) 

38 整数运算
     expr   +  -  \*  /  %
    num1=10
    num2=20
   echo $((num1-num2))
   echo expr 10 + 20
   echo $[ 2+ 2 ]
   echo $[ 2** 2 ]
   let 

39 awk 命令 AWK 程序设计语言 ， 三位创建者已将它正式定义为“样式扫描和处理语言”。
    它允许您创建简短的程序，这些程序读取输入文件、为数据排序、处理数据、对输入执行计算以及生成报表，还有无数其他的功能
   
    free -m |grep Mem |awk '{print $3}'

40  bash -vx  脚本   调试方式运行脚本

41 Linux三剑客（grep、sed、awk）

42 Linux bc命令详解：一款数学计算器

43 # 截取
   url=www.sina.com.cn
   echo ${url#www}  //输出 .sina.com.cn

44  ## 贪婪匹配   //从右向左开始匹配
   url=www.sina.com.cn
   echo ${url##*.}  //输出  cn 

45  % 去除 
   url=www.sina.com.cn
   echo ${url%cn}      //输出  www.sina.com.
   echo ${url%.*}        //输出  www.sina.com
   echo ${url%%.*}      //输出  www

46 索引和切片
   url=www.sina.com.cn
   echo ${url:0:5}   //www.s

47 内容的替换
   url=www.sina.com.cn
   echo ${url/sina/baidu}  //www.baidu.com.cn
   echo ${url/n/N}            //www.siNa.com.cn
   echo ${url//n/N}            //www.siNa.com.cN

48  - 
    ${新的变量名-新的变量值}
    echo ${ip-aaa}   //aaa  如果ip已经存在, 则ip的值不会被覆盖

48  :- 
    ${变量名-新的变量值}
    set ip2
    echo ${ip2:-aaa}   //aaa  如果ip2不存在或为空值, ip2的值会被覆盖

49 +	:+   	= 	:=    ?          :?
  
50 let  

51 [ -z STRING ]  “STRING” 的长度为零则为真。

52 [ -n STRING ] or [ STRING ]  “STRING” 的长度为非零 non-zero则为真。

53 ()     子shell 执行
    (())    运算
    $()    命令替换
    $(())   数值比较  运算c语言
    { }      集合
   ${}      变量的引用
   [ ]       条件测试
   [ [ ]]    条件测试   支持正则匹配
   $[ ]     整数运算


54  
 ./01.sh           需要执行权限  在子shell中执行
bash 01.sh      不需要执行权限  在子shell中执行

.  ./01.sh         不需要执行权限  在当前shell中执行
source ./01.sh      不需要执行权限  在当前shell中执行

调试脚本
sh -n ./01.sh     仅调试 syntax error  语法错误
sh -vx ./01.sh     以调试的方式进行, 查询整个执行过程

55 

shell 条件测试
test命令是shell环境中测试条件表达式的实用工具。
-b<文件>：如果文件为一个块特殊文件，则为真；
-c<文件>：如果文件为一个字符特殊文件，则为真；
-d<文件>：如果文件为一个目录，则为真；
-e<文件>：如果文件存在，则为真；
-f<文件>：如果文件为一个普通文件，则为真；
-g<文件>：如果设置了文件的SGID位，则为真；
-G<文件>：如果文件存在且归该组所有，则为真；
-k<文件>：如果设置了文件的粘着位，则为真；
-O<文件>：如果文件存在并且归该用户所有，则为真；
-p<文件>：如果文件为一个命名管道，则为真；
-r<文件>：当前用户 如果文件可读，则为真；
-s<文件>：如果文件的长度不为零，则为真；
-S<文件>：如果文件为一个套接字特殊文件，则为真；
-u<文件>：如果设置了文件的SUID位，则为真；
-w<文件>：如果文件可写，则为真；
-x<文件>：如果文件可执行，则为真。

56  [  这也是一个命令   which [     -> /usr/bin/[

57 test  条件表达式
   [ 条件表达式 ]
   [ [  条件表达式 ] ]


58 man test  查看更多信息  如  -ge  -le

59 Linux下的文件类型如下： 
- 普通文件 
d 目录 
l 链接文件 
b 块设备 
c 字符设备 

60
    前面三个表示所有者权限，中间三个表示同组用户权限，最后一组表示其他用户权限
    -rwxr-xr-x
    -代表普通文件

61  除了读写执行权限外系统还支持强制位（s权限）和粘滞位（t权限）
    s权限： 设置使文件在执行阶段具有文件所有者的权限，相当于临时拥有文件所有者的身份. 
    典型的文件是passwd. 如果一般用户执行该文件, 则在执行过程中, 该文件可以获得root权限, 
    从而可以更改用户的密码.

62 t权限
    要删除一个文档，您不一定要有这个文档的写权限，但您一定要有这个文档的上级目录的写权限。
    也就是说，您即使没有一个文档的写权限，但您有这个文档的上级目录的写权限，
    您也能够把这个文档给删除，而假如没有一个目录的写权限，也就不能在这个目录下创建文档。
    怎样才能使一个目录既能够让任何用户写入文档，又不让用户删除这个目录下他人的文档，
    t权限就是能起到这个作用。t权限一般只用在目录上，用在文档上起不到什么作用。
     在一个目录上设了t权限位后，（如/home，权限为1777)任何的用户都能够在这个目录下创建文档，
     但只能删除自己创建的文档(root除外)，这就对任何用户能写的目录下的用户文档 启到了保护的作用。

63 df  打印磁盘空间占用情况

64  grep /$  意思是从中挑出以/结尾的行 
 
65  awk  '{print $(NF-1)}'   打印倒数第二列    
      // df -Th | grep '/$' | awk '{print $(NF-1)}'
      // df -Th | grep '/$' | awk '{print $(NF-1)}' | awk -F"%" '{print $1}' 

66 crontab -e  定时任务

67  反引号代表引用命令
      被单引号括起来的字符都是普通字符，就算特殊字符也不再有特殊含义
     

68  尽量使用 $(命令) 的方式来引用命令的输出，而不要使用反引号
      echo `date`
      echo $(date)  
69  bash -vx   脚本   // 调试方式运行脚本

70  unset 

71  字符串变量使用 " "

72  判断语句中 =不是赋值

73 seq  生成序列

74 cat /etc/group  查看用户组

75 command   
    -v  查看是不是一个命令    //command -v /bin/bash

76 EOF
     Shell中通常将EOF与 << 结合使用，表示后续的输入作为子命令或子Shell的输入，
     直到遇到EOF为止，再返回到主调Shell

77  sed [-nefri] ‘command’ 输入文本  
    sed '1d' ab              #删除第一行 
     sed '$d' ab              #删除最后一行
     sed '1,2d' ab           #删除第一行到第二行
     sed '2,$d' ab           #删除第二行到最后一行
     sed -n '1p' ab           #显示第一行 
     sed -ri '/^SELINUX=/cSELINUX' 文字替换  可以自己尝试敲一敲
	 
78 数组  books= {linux shell awk } books[2]  ' `
      array2 = (`cat /etc/password`) 希望将该文件中的每一行作为一个元素赋值给数组  
	  books[@]  数组所有元素 
	  #books[@] 数组个数
	  !books[@] 数组所有索引
		
		
79 申明关联数组 declare -A 
   declare -A info
   info = ([name]= tianyun [sex] = male)   
    
80  ` ` 中的命令会在子shell中执行

81  break  可以跳出多层循环    break  3

82 shift  移位  循环中index下标移动

83  :  

84 sed
    g
	G

85  sed
    删除注释行         // 可以实现，可以自己百度查一下
	删除空行           // 可以实现，可以自己百度查一下
	给文件行添加注释   // 可以实现，可以自己百度查一下
	sed -r '1,5s/^/#/' c.txt       //c.txt 1-5行添加#
	sed -r '1,5s/^#*/#/' c.txt     //c.txt 1-5行一个或多个#换成#
	
86  sed -ri '3a$var1' c.txt     
    sed -ri "3a$var1" c.txt   //将变量var1的值添加到第三行后面，上面只会把var1添加到变量后面

87  sed -ri '$a'"$var1" c.txt   //  将变量var1的值添加文件最后一行
    sed -ri "\$a$var1" c.txt    //  将变量var1的值添加文件最后一行,效果相同

88      BEGIN{}               {}                END{}
       awk  {print1/2}    {print "ok"}      {print "..."}

89  awk  
    FS=":"   OFS="----"  //FS 分隔符, 
    OFS              间隔补充符
    NR               序号
    FNR              文件序号

90  $0  root:x:0:0:root:/root:/bin/bash
          $1 $2$3$4 $5    $6     $7

90  NF      有多少个字段
    $NF     最后一个字段
    RS    ORS    记录分割符  //行分割符  默认换行符 可参考 FS  OFS 

91  awk  %-15s       //printf 格式匹配 不换行。 print 换行 
    %s     字符
    %d     数字
    %f     浮点数
    -      左对齐  默认右对齐
    15     占用空间

92   ~       匹配
     ！~     不匹配

93   关系运算符
     <       小于 
     <=      小于等于
     ==      等于
     !=      不等于
     >=      大于等于
     >       大于

94  条件表达式
    awk -F: '{if($3 > 300){print $0}}'  /etc/passwd
    awk -F: '{if($3 > 300){print $0} else {print $1} }'  /etc/passwd
    还有三目运算符

95   算术运算   逻辑操作符

96   awk -F: '{i=1;while{i<=10} {print $0;i++}}' //每行打印10次

97   awk  数组  
     awk -F: '{user[i++]=$1}END{for(i in user){print i, user[i]}}'
     awk -F: '{user[$NF]++}END{for(i in user){print i, user[i]}}'

98   
     awk  gsub( )函数  int( )函数  -v参数
     var="bash"
     echo "unix script" |awk "gsub(/unix/, \"$var\")"
     echo "unix script" |awk 'gsub(/unix/, "'"$var"'")'
     echo "unix script" |awk  -v var="bash" 'gsub(/unix/, var)'

99  echo $USER 
    echo $LOGNAME  

100 
    假设我们定义了一个变量为：
    file=/dir1/dir2/dir3/my.file.txt
    可以用${ }分别替换得到不同的值：
    ${file#*/}：删掉第一个/ 及其左边的字符串：dir1/dir2/dir3/my.file.txt
    ${file##*/}：删掉最后一个/  及其左边的字符串：my.file.txt
    ${file#*.}：删掉第一个.  及其左边的字符串：file.txt
    ${file##*.}：删掉最后一个.  及其左边的字符串：txt
    ${file%/*}：删掉最后一个 /  及其右边的字符串：/dir1/dir2/dir3
    ${file%%/*}：删掉第一个/  及其右边的字符串：(空值)
    ${file%.*}：删掉最后一个 .  及其右边的字符串：/dir1/dir2/dir3/my.file
    ${file%%.*}：删掉第一个 .   及其右边的字符串：/dir1/dir2/dir3/my
    记忆的方法为：
    # 是 去掉左边（键盘上#在 $ 的左边）
    %是去掉右边（键盘上% 在$ 的右边）
    单一符号是最小匹配；两个符号是最大匹配
    ${file:0:5}：提取最左边的5 个字节：/dir1
    ${file:5:5}：提取第5 个字节右边的连续5个字节：/dir2
    利用${ } 还可针对不同的变数状态赋值(沒设定、空值、非空值)： 
    ${file-my.file.txt} ：假如$file 沒有设定，則使用my.file.txt 作传回值。(空值及非空值時不作处理) 
    ${file:-my.file.txt} ：假如$file 沒有設定或為空值，則使用my.file.txt 作傳回值。(非空值時不作处理)
    ${file+my.file.txt} ：假如$file 設為空值或非空值，均使用my.file.txt 作傳回值。(沒設定時不作处理)
    ${file:+my.file.txt} ：若$file 為非空值，則使用my.file.txt 作傳回值。(沒設定及空值時不作处理)
    ${file=my.file.txt} ：若$file 沒設定，則使用my.file.txt 作傳回值，同時將$file 賦值為my.file.txt 。(空值及非空值時不作处理)
    ${file:=my.file.txt} ：若$file 沒設定或為空值，則使用my.file.txt 作傳回值，同時將$file 賦值為my.file.txt 。(非空值時不作处理)
    ${file?my.file.txt} ：若$file 沒設定，則將my.file.txt 輸出至STDERR。(空值及非空值時不作处理)
    ${file:?my.file.txt} ：若$file 没设定或为空值，则将my.file.txt 输出至STDERR。(非空值時不作处理)
    ${#var} 可计算出变量值的长度：
    ${#file} 可得到27 ，因为/dir1/dir2/dir3/my.file.txt 是27个字节


101  shift
     shift命令用于对参数的移动(左移)，通常用于在不知道传入参数个数的情况下依次遍历每个参数然后进行相应处理

102  set --   //重定向输入命令参数
     https://blog.csdn.net/weixin_34415923/article/details/89834583?utm_medium=distribute.pc_relevant_t0.none-task-blog-BlogCommendFromBaidu-1.not_use_machine_learn_pai&depth_1-utm_source=distribute.pc_relevant_t0.none-task-blog-BlogCommendFromBaidu-1.not_use_machine_learn_pai

103  eval eval会对后面的命令进行两遍扫描，如果第一遍扫描后，命令是个普通命令，则执行此命令；如果命令中含有变量的间接引用，则保证间接引用的语义。
     也就是说，eval命令将会首先扫描命令行进行所有的置换，然后再执行该命令

104  =与==在[ ]中表示判断(字符串串比较)时是等价的
    s1="foo"
    s2="foo"
    [$s1=$2 ]
    [$s1==$2]

105  2>/dev/null 代表忽略掉错误提示信息。
     
106 
#! /bin/bash
#执行脚本时在终端输入　./copy.sh ./test ./copy
#其中./test为ldd所要查看的可执行程序的路径，./copy为依赖文件最终拷贝到的文件夹路径
 
#以下三个参数为终端输入
# $0 为 ./copy.sh
# $1 为 ./test
# $2 为 ./copy
 
 
# awk 后　$0,$1,$2为终端日志的字符串，以空格为分隔符，只在awk本行起作用
#将字符串重定向到dependList
dependList=$( ldd $1 | awk '{if (match($3,"/")){ print $3}}' )
 
 
#输出　./test
#echo $1
 
#拷贝依赖
cp $dependList $2
#拷贝可执行程序
cp $1 $2

107. 参数
-n 只读取shell脚本，但不实际执行
-x 进入跟踪方式，显示所执行的每一条命令
-c "string" 从strings中读取命令
"-n"可用于测试shell脚本是否存在语法错误，但不会实际执行命令。在shell脚本编写完成之后，实际执行之前，首先使用"-n"选项来测试脚本是否存在语法错误是一个很好的习惯。
    因为某些shell脚本在执行时会对系统环境产生影响，比如生成或移动文件等，如果在实际执行才发现语法错误，您不得不手工做一些系统环境的恢复工作才能继续测试这个脚本。
"-c"选项使shell解释器从一个字符串中而不是从一个文件中读取并执行shell命令。当需要临时测试一小段脚本的执行结果时，可以使用这个选项，如下所示：
    sh -c 'a=1;b=2;let c=$a+$b;echo "c=$c"'
"-x"选项可用来跟踪脚本的执行，是调试shell脚本的强有力工具。"-x"选项使shell在执行脚本的过程中把它实际执行的每一个命令行显示出来，并且在行首显示一个"+"号。
     "+"号后面显示的是经过了变量替换之后的命令行的内容，有助于分析实际执行的是什么命令。 "-x"选项使用起来简单方便，可以轻松对付大多数的shell调试任务,应把其当作首选的调试手段

108. shell中if的“-e，-d，-f”是什么意思
文件表达式
-e filename 如果 filename存在，则为真
-d filename 如果 filename为目录，则为真 
-f filename 如果 filename为常规文件，则为真
-L filename 如果 filename为符号链接，则为真
-r filename 如果 filename可读，则为真 
-w filename 如果 filename可写，则为真 
-x filename 如果 filename可执行，则为真
-s filename 如果文件长度不为0，则为真
-h filename 如果文件是软链接，则为真
filename1 -nt filename2 如果 filename1比 filename2新，则为真。
filename1 -ot filename2 如果 filename1比 filename2旧，则为真。

109
${1}  输入的第2个参数${2} 输入的第3个参数${0} 输入的第1个参数
     #====== 示例 ================./main.sh 25 43 当执行脚本main.sh时候，后面接了25 43 参数，那么$0代表第一个参数main.sh $1代表25 $2代表43 以此类推

110 typeset用于设置变量属性,如大小写,宽度,左右对齐等都可以用typeset来控制, 当用typeset改变一个变量的属性时,这种改变是永久的
    typeset的-l选项将一个变量的字符变成小写 
    typeset -l var=ABC   //  var -> abc 

111
[ -a FILE ]  如果 FILE 存在则为真。  
[ -b FILE ]  如果 FILE 存在且是一个块特殊文件则为真。  
[ -c FILE ]  如果 FILE 存在且是一个字特殊文件则为真。  
[ -d FILE ]  如果 FILE 存在且是一个目录则为真。  
[ -e FILE ]  如果 FILE 存在则为真。  
[ -f FILE ]  如果 FILE 存在且是一个普通文件则为真。  
[ -g FILE ] 如果 FILE 存在且已经设置了SGID则为真。 [ -h FILE ]  如果 FILE 存在且是一个符号连接则为真。  
[ -k FILE ]  如果 FILE 存在且已经设置了粘制位则为真。  
[ -p FILE ]  如果 FILE 存在且是一个名字管道(F如果O)则为真。  
[ -r FILE ]  如果 FILE 存在且是可读的则为真。  
[ -s FILE ]  如果 FILE 存在且大小不为0则为真。  
[ -t FD ]  如果文件描述符 FD 打开且指向一个终端则为真。  
[ -u FILE ]  如果 FILE 存在且设置了SUID (set user ID)则为真。  
[ -w FILE ]  如果 FILE 如果 FILE 存在且是可写的则为真。  
[ -x FILE ]  如果 FILE 存在且是可执行的则为真。  
[ -O FILE ]  如果 FILE 存在且属有效用户ID则为真。  
[ -G FILE ]  如果 FILE 存在且属有效用户组则为真。  
[ -L FILE ]  如果 FILE 存在且是一个符号连接则为真。  
[ -N FILE ]  如果 FILE 存在 and has been mod如果ied since it was last read则为真。  
[ -S FILE ]  如果 FILE 存在且是一个套接字则为真。  
[ FILE1 -nt FILE2 ]  如果 FILE1 has been changed more recently than FILE2, or 如果 FILE1 exists and FILE2 does not则为真。  
[ FILE1 -ot FILE2 ]  如果 FILE1 比 FILE2 要老, 或者 FILE2 存在且 FILE1 不存在则为真。  
[ FILE1 -ef FILE2 ]  如果 FILE1 和 FILE2 指向相同的设备和节点号则为真。  
[ -o OPTIONNAME ]  如果 shell选项 “OPTIONNAME” 开启则为真。  
[ -z STRING ]  “STRING” 的长度为零则为真。  
[ -n STRING ] or [ STRING ]  “STRING” 的长度为非零 non-zero则为真。  
[ STRING1 == STRING2 ]  如果2个字符串相同。 “=” may be used instead of “==” for strict POSIX compliance则为真。  
[ STRING1 != STRING2 ]  如果字符串不相等则为真。 
[ STRING1 < STRING2 ]  如果 “STRING1” sorts before “STRING2” lexicographically in the current locale则为真。  
[ STRING1 > STRING2 ]  如果 “STRING1” sorts after “STRING2” lexicographically in the current locale则为真。  
[ ARG1 OP ARG2 ] “OP” is one of -eq, -ne, -lt, -le, -gt or -ge. These arithmetic binary operators return true if “ARG1” is equal to,
                  not equal to, less than, less than or equal to, greater than, or greater than or equal to “ARG2”, respectively. 
                  “ARG1” and “ARG2” are integers.

112 复杂逻辑判断
-a 　 　　　　　 与 
-o　　　　　　　 或 
!　　　　　　　　非

113  sed 's/''"'/'\\\"''/g'`   //将匹配的 " 全部换成 /"    /g全部替换