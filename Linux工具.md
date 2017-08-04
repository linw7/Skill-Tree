# [Linux工具](http://man.linuxde.net/par/2)

> Linux下还是有很多超棒的开发工具的。

在Linux日常使用中，最常用的命令自然是sudo, ls, cp, mv, cat等，但作为后台开发者，上述命令远远不够。从我的理解来看，合格的C/C++开发者至少需要从开发及调试工具、文件处理、性能分析、网络工具四个方面针对性使用一些开发工具。这里我罗列了一些，大部分都是开发中经常需要使用的命令，有些功能比较简单的命令我会给出一些基本用法，有些本身自带体系（比如vim, gdb等）的命令只能附上链接了。

开发及调试工具介绍了从“编辑 -> 编译 -> 分析目标文件 -> 追踪调用过程”的全套命令，文件处理部分介绍了查找、统计、替换等基本文本操作命令，性能分析介绍了查看进程信息、CPU负载、I/O负载、内存使用情况等基本命令，网络工具介绍了可以查看“链路层 -> 网络层 -> 传输层 -> 应用层”信息的工具。除此以外，其他命令中也列出了开发者经常会用到的一些命令，基本可以满足日常开发需要。

---

# 目录

| Chapter 1 | Chapter 2 | Chapter 3| Chapter 4 |Chapter 5|
| :---------: | :---------: | :---------: | :--------: |:--------:|
|[开发及调试](#pro)|[文件处理](#file)|[性能分析](#sysinfo)|[网络工具](#net)|[其他](#other)|

- 开发及调试

    - 编辑器：vim
    - 编译器：gcc/g++
    - 调试工具：gdb
    - 查看依赖库：ldd
    - 二进制文件分析：objdump
    -  ELF文件格式分析：readelf
    - 跟踪进程中系统调用：strace
    - 跟踪进程栈：pstack
    - 进程内存映射：pmap
    
- 文件处理
    - 文件查找：find
    - 文本搜索：grep
    - 排序：sort
    - 转换：tr
    - 按列切分文本：cut
    - 按列拼接文本：paste
    - 统计行和字符：wc
    - 文本替换：sed
    - 数据流处理：awk

- 性能分析
    - 进程查询：ps
    - 进程监控：top
    -  打开文件查询：lsof
    - 内存使用量：free
    - 监控性能指标：sar

- 网络工具
    - 网卡配置：ifconfig 
    - 查看当前网络连接：netstat
    - 查看路由表：route
    - 检查网络连通性：ping
    - 转发路径：traceroute
    - 网络Debug分析：nc
    - 命令行抓包：tcpdump
    - 域名解析工具：dig
    - 网络请求：curl

- 其他
    - 终止进程：kill
    - 修改文件权限：chmod
    - 创建链接：ln
    - 显示文件尾：tail
    - 版本控制：git
    - 设置别名：alias

---

# 内容

### <span id = "pro">开发及调试</span>

> 开发工具大部分都提供了完善的功能，所以这里不一一列举用法。从技术层面来说，调试工具比开发工具更考验一个人的工程能力。

1. 编辑器：vim
    - 服务器端开发必知必会，功能强大，这里不一一列举，但基本的打开文件、保存退出要会。
    - [详见](http://coolshell.cn/articles/5426.html)

2. 编译器：gcc/g++
    - C/C++编译器，必知必会，除此以外需要了解预处理-> 编译 -> 汇编 -> 链接等一系列流程。
    - [详见](http://www.cnblogs.com/lidan/archive/2011/05/25/2239517.html)

3. 调试工具：gdb
    - 服务器端调试必备。
    - [详见](http://linuxtools-rst.readthedocs.io/zh_CN/latest/tool/gdb.html)
    
4. 查看依赖库：ldd
    - 程序依赖库查询
    ```shell
    # ldd后接可执行文件
    # 第一列为程序依赖什么库，第二列为系统提供的与程序需要的库所对应的库，第三列为库加载的开始地址
    # 前两列可以判断系统提供的库和需要的库是否匹配，第三列可以知道当前库在进程地址空间中对应的开始位置

    ldd a.out
    ```
5. 二进制文件分析：objdump
    - 反汇编，需要理解汇编语言
    - [详见](http://man.linuxde.net/objdump)

7. ELF文件格式分析：readelf
    - 可以得到ELF文件各段内容，分析链接、符号表等需要用到
    - [详见](http://linuxtools-rst.readthedocs.io/zh_CN/latest/tool/readelf.html)

8. 跟踪进程中系统调用：strace
    - [详见](http://linuxtools-rst.readthedocs.io/zh_CN/latest/tool/strace.html)

9. 跟踪进程栈：pstack
    - [详见](http://linuxtools-rst.readthedocs.io/zh_CN/latest/tool/pstack.html#)

10. 进程内存映射：pmap
    - 显示进程内存映射
    ```shell
    # -x显示扩展信息，后接进程pid
    # Address: 内存开始地址
    # 显示信息：
        Kbytes: 占用内存的字节数
        RSS: 保留内存的字节数
        Dirty: 脏页的字节数（包括共享和私有的）
        Mode: 内存的权限：read、write、execute、shared、private
        Mapping: 占用内存的文件、或[anon]（分配的内存）、或[stack]（堆栈）
        Device: 设备名 (major:minor)

    pmap -x 12345
    ```

---

### <span id = "file">文件处理</span>

> Everything is file. 在Linux环境下，对文本处理相当频繁，所以有些命令的参数还是需要记忆的。另外其他很多命令的输出信息都需要通过文件处理命令来筛选有用信息。

1. 文件查找：find
   
    按名查找：

    - 查找具体文件（一般方式）
    ```shell
    find . -name *.cpp
    ```

    - 查找具体文件（正则方式）
    ```shell
    # -regex为正则查找，-iregex为忽略大小写的正则查找 

    find -regex ".*.cpp$"
    ```

    定制查找：
    - 按类型查找
    ```shell
    # f(file)为文件，d(dictionary)为目录，l(link)为链接

    find . -type f
    ```

    - 按时间查找
    ```shell
    # atime为访问时间，x天内加参数"-atime -x"，超过x天加"-atime -x"
    # mtime为修改时间

    find . -type f -atime -7
    ```

    - 按大小查找
    ```shell
    # -size后接文件大小，单位可以为k(kb)，m(MB)，g(GB)

    find . -type f -size -1k
    ```

    - 按权限查询
     ```shell
    # -perm后接权限
    
    find . -type -perm 644
    ```

2. 文本搜索：grep
    - 模式匹配
    ```shell
    # 匹配test.cpp文件中含有"iostream"串的内容

    grep "iostream" test.cpp  
    ```

    - 多个模式匹配
    ```shell
    # 匹配test.cpp文件中含有"iostream"和"using"串的内容

    grep -e "using" -e "iostream" test.cpp  
    ```

    - 输出信息
    ```shell
    # -n为打印匹配的行号；-i搜索时忽略大小写；-c统计包含文本次数

    grep -n "iostream" test.cpp  
    ```
3. 排序：sort
    - 文件内容行排序
    ```shell
    # 排序在内存进行，不改变文件
    # -n(number)表示按数字排序，-d(dictionary)表示按字典序
    # -k N表示按各行第N列进行排序
    # -r(reverse)为逆序排序

    sort -n -k 1 test
    ```

4. 转换：tr
    - 字符替换
    ```shell
    # 转换在内存进行，不改变文件
    # 将打开文件中所有目标字符替换

    cat test | tr '1' '2'
    ```

    - 字符删除
    ```shell
    # 转换在内存进行，不改变文件
    # -d删除(delete)

    cat test | tr -d '1'
    ```

    - 字符压缩
    ```shell
    # 转换在内存进行，不改变文件
    # -s位于后部

    cat test | tr ' ' -s
    ```
5. 按列切分文本：cut
    - 截取特定列
    ```shell
    # 截取的内存进行，不改变文件
    # -b(byte)以字节为单位，-c(character)以字符为单位，-f以字段为单位
    # 数字为具体列范围

    cut -f 1,2 test
    ```

    - 指定界定符
    ```shell
    # 截取的内存进行，不改变文件
    # -d后接界定符

    cut -f 2 -d ',' new
    ```

6. 按列拼接文本：paste
    - 按列拼接
    ```shell
    # 在内存中拼接，不改变文件
    # 将两个文件按对应列拼接
    # 最后加上-d "x"会将x作为指定分隔符（paste test1 test2 -d ","）
    # 两文件列数可以不同 

    paste test1 test2
    ```
    - 指定界定符拼接
    ```shell
    # 在内存中拼接，不改变文件
    # 按照-d之后给出的界定符拼接

    paste test1 test2 -d ","
    ```

7. 统计行和字符：wc
     - 基本统计
     ```shell
     # -l统计行数(line)，-w统计单词数(word)，-c统计字符数(character)

     wc -l test
     ```
8. 文本替换：sed
    - 区别于上面的命令，sed是可以直接改变被编辑文件内容的。
    - [详见](http://coolshell.cn/articles/9104.html)

9. 数据流处理：awk
    - 区别于上面的命令，awk是可以直接改变被编辑文件内容的。
    - [详见](http://coolshell.cn/articles/9070.html)

---

### <span id = "sysinfo">系统信息</span>

> 性能监视工具对于程序员的作用就像是听诊器对于医生的作用一样。系统信息主要针对于服务器性能较低时的排查工作，主要包括CPU信息，文件I/O和内存使用情况，通过进程为纽带得到系统运行的瓶颈。

1. 进程查询：ps
    - 查看正在运行进程
    ```shell
    # 常结合grep筛选信息(e.g, ps -ef | grep xxx)

    ps -ef
    ```

    - 以完整格式显示所有进程
    ```shell
    # 常结合grep筛选信息

    ps -ajx
    ```

2. 进程监控：top
    - 显示实时进程信息
    ```shell
    # 这是个大招，都不带参数的，具体信息通过grep筛选
    # 交互模式下键入M进程列表按内存使用大小降序排列，键入P进程列表按CPU使用大小降序排列
    # %id表示CPU空闲率，过低表示可能存在CPU存在瓶颈
    # %wa表示等待I/O的CPU时间百分比，过高则I/O存在瓶颈 > 用iostat进一步分析

    top
    ```

3. 打开文件查询：lsof
   - 查看占用某端口的进程
    ```shell
    # 最常见的就是mysql端口被占用使用(lsof i:3307)
    # 周知端口(ftp:20/21, ssh:22, telnet:23, smtp:25, dns:53, http:80, pop3:110, https:443)

    lsof -i:53
    ```

    - 查看某用户打开的文件 
    ```shell
    # -u(user)为用户，后接用户名

    lsof -u inx
    ```

    - 查看指定进程打开的文件 
    ```shell
    # -p(process)为进程，后接进程PID

    lsof -p 12345
    ```

    - 查看指定目录下被进程打开的文件 
    ```shell
    # 这里是"+d"，需要注意，使用"+D"递归目录

    lsof +d /test
    ```

4. 内存使用量：free
    - 内存使用量
    ```shell
    # 可获得内存及交换区的总量，已使用量，空闲量等信息

    free
    ```

5. 监控性能指标：sar

    监控CPU
    - 监控CPU负载
    ```shell
    # 加上-q可以查看运行队列中进程数，系统上进程大小，平均负载等
    # 这里"1"表示采样时间间隔是1秒，这里"2"表示采样次数为2

    sar -q 1 2
    ```

    - 监控CPU使用率
    ```shell
    # 可以显示CPU使用情况
    # 参数意义同上

    sar -u 1 2
    ```

    监控内存
    - 查询内存
    ```shell
    # 可以显示内存使用情况
    # 参数意义同上 

    sar -r 1 2
    ```

    - 页面交换查询
     ```shell
     # 可以查看是否发生大量页面交换，吞吐率大幅下降时可用
     # 参数意义同上

    sar -W 1 2
    ```

---

### <span id = "net">网络工具</span>
> 网络工具部分只介绍基本功能，参数部分一笔带过。这部分重点不在于工具的使用而是对反馈的数据进行解读，并且这部分命令功能的重合度还是比较高的。

 1. 网卡配置（链路层）：ifconfig 
    - 显示设备信息
    ```shell
    # 可以显示已激活的网络设备信息

    ifconfig
    ```
    - 启动关闭指定网卡
    ```shell
    # 前一个参数为具体网卡，后一个为开关信息
    # up为打开，down为关闭

    ifconfig eth0 up
    ```

    - 配置IP地址
    ```shell
    # 前一个参数为具体网卡，后一个为配置的IP地址

    ifconfig eth0 192.168.1.1
    ```

    - 设置最大传输单元
    ```shell
    前一个参数为具体网卡，后面为MTU的大小
    # 设置链路层MTU值，通常为1500

    ifconfig eth0 mtu 1500
    ```

    - 启用和关闭ARP协议
    ```
    # 开启arp如下，若关闭则-arp

    ifconfig eth0 arp
    ```

2. 查看当前网络连接（链路层/网络层/传输层）：netstat
    - 网络接口信息
    ```shell
    # 显示网卡信息，可结合ifconfig学习

    netstat -i
    ```

    - 列出端口
    ```shell
    # -a(all)表示所有端口，-t(tcp)表示所有使用中的TCP端口
    # -l(listening)表示正在监听的端口
    
    netstat -at
    ```

    - 显示端口统计信息
    ```shell
    # -s(status)显示各协议信息
    # -加上-t(tcp)显示tcp协议信息，加上-u(udp)显示udp协议信息

    netstat -s
    ```

    - 显示使用某协议的应用名
    ```shell 
    # -p(progress)表示程序，可以显示使用tcp/udp协议的应用的名称

    netstat -pt
    ```

    - 查找指定进程、端口
    ```shell
    # 互逆操作第一个显示某程序使用的端口号，第二个显示某端口号的使用进程
    # 第二个操作可以用lsof替代

    netstat -ap | grep ssh
    netstat -an | grep ':80'
    ```

3. 查看路由表（网络层IP协议）：route
    - 查看路由信息
    ```shell
    # 得到路由表信息，具体分析路由表工作需要网络知识
    # 可以通过netstat -r(route)得到同样的路由表

    route
    ```

4. 检查网络连通性（网络层ICMP协议）：ping
    - 检查是否连通
    ```shell
    # 主要功能是检测网络连通性
    # 可以额外得到网站的ip地址和连接最大/最小/平均耗时。

    ping baidu.com
    ```

5. 转发路径（网络层ICMP协议）：traceroute
    - 文件包途径的IP
    ```shell
    # 
    # 可以打印从沿途经过的路由器IP地址

    traceroute baidu.com
    ``` 

6. 网络Debug分析（网络层/传输层）：nc
    - 端口扫描
    ```shell
    # 黑客很喜欢
    # 扫描某服务器端口使用情况
    # -v(view)显示指令执行过程，-w(wait)设置超时时长
    # -z使用输入输出模式（只在端口扫描时使用）
    # 数字为扫描的端口范围 

    nc -v -w 1 baidu.com  -z 75-1000
    ```

    - [其他详见](https://www.oschina.net/translate/linux-netcat-command)

7. 命令行抓包（网络层/传输层）：tcpdump
    - 抓包利器，没有什么比数据更值得信赖。可以跟踪整个传输过程。
    - [详见](http://www.cnblogs.com/ggjucheng/archive/2012/01/14/2322659.html)

8. 域名解析工具（应用层DNS协议）：dig
    ```shell
    # 应用层，DNS
    # 打印域名解析结果
    # 打印域名解析过程中涉及的各级DNS服务器地址

    dig baidu.com
    ```

9. 网络请求（应用层）：curl
    - [详见](http://www.cnblogs.com/gbyukg/p/3326825.html)

---

### <span id = "other">其他</span>

> 这里都是日常开发中高频命令。

1. 终止进程：kill
    - 杀死具体进程
    ```shell
    # 加具体进程PID

    kill 12345
    ```

    - 杀死某进程相关进程
    ```shell 
    # 加上"-9"杀死某进程相关进程

    kill -9 12345
    ```

2. 修改文件权限：chmod
    - 更改文件权限
    ```shell
    # 可以对三种使用者设置权限，u(user, owner)，g(group)，o(other)
    # 文件可以有三种权限，r(read)，w(write)，x(execute)
    # 这里u+r表示文件所有者在原有基础上增加文件读取权限
    # 这里777分别对应，u=7，g=7，o=7，具体数字含义自行google

    chmod u+r file
    chmod 777 file
    ```

3. 创建链接：ln
    - 创建硬链接
    ```shell
    # 文件inode中链接数会增加，只有链接数减为0时文件才真正被删除

    ln file1 file2
    ```

    - 创建软（符号链接）链接
    ```shell
    # -s(symbol)为符号链接，仅仅是引用路径
    # 相比于硬链接最大特点是可以跨文件系统
    # 类似于Windows创建快捷方式，实际文件删除则链接失效

    ln -s file1 file2
    ```

4. 显示文件尾：tail
    - 查看文件尾部
    ```shell
    # -f参数可以不立即回传结束信号，当文件有新写入数据时会及时更新
    # 查看日志时常用

    tail -f test
    ```

5. 版本控制：git
    - 版本控制最好用的软件，没有之一。至少要知道"git init"，"git add"，"git commit"，"git pull"，"git push"几个命令。
    - [详见](http://www.liaoxuefeng.com/wiki/0013739516305929606dd18361248578c67b8067c8c017b000/)

6. 设置别名：alias
    - 常用命令添加别名
    ```shell
    # ".bashrc"文件中配置常用命令别名，生效后在命令行只需要使用别名即可代替原先很长的命令

    alias rm='rm -i'
    ```

--- 

### 实战 

假设已经通过vim编辑，gcc编译得到可执行文件server，这时就可以使用一些开发者常用的工具来进行后期调试。这里都是给出最简单的用法，意在快速掌握一些基本开发工具。

先clone这个项目，然后使用src_code下代码编译通过后通过下面命令调试。[代码](https://github.com/linw7/TKeed)

1. 单步调试：gdb

- 运行得不到正确结果可以通过gdb设置断点来查看每个中间变量值，以此来确定哪里出了问题。因为gdb调试内容较多，这里不详细说明。另外，gdb出了可以单步查看变量值，还可以分析coredump文件来排查错误。

2. 动态库依赖：ldd

- 命令：ldd ./server

- 可以查看可执行文件server所需的所有动态库，动态库所在目录及其被映射到的虚拟地址空间。

3. 性能分析：top

- top可以查看当前系统很多信息，比如1,5,15分钟内负载，运行、休眠、僵尸进程数，用户、内核程序占CPU百分比，存储信息等。top可以定位具体哪个进程CPU占用率高和内存使用率高。我们可以以此定位性能问题出在什么程序上（比如你后台执行TKeed server之后，可以看到CPU占用率为99%，这时候我们就需要从这个程序入手了）。

4. 系统调用：strace

- 命令：strace ./server

- 上面已经提到TKeed server的CPU占用率为99%，那么问题通常一定是出在了死循环上。我们接下来在代码中找到死循环位置。因为程序中epoll_wait需要阻塞进程，我们怀疑是不是这里没有阻塞，这时就可以通过上面的方式运行server程序。此时可以打印出没次系统调用及其参数等，我们也可以加-o filename将系统调用信息保存下来。

5. 打印进程：ps

- 命令：ps -ejH

- 我们在命令行下打开的程序的父进程是shell程序，之前用strace打开server程序，strace也是server的父进程。我们有时候需要知道进程间的层级关系就需要打印进程树，上面的ps命令可以做到。当出现僵尸进程时就可以通过进程树定位具体是哪个进程出了问题。另外当想要知道进程pid时，ps -el | grep XXX也是很常用的。

6. 打开文件：lsof

- lsof -i:3000

- 比如在运行server时发现端口被占用了，可以通过lsof -i:port来查看对应端口号正在被哪个进程所占用。端口占用是非常常见的问题，比如3306被占用我遇到过好几次，要么是某个程序正好占用了要么是之前没能结束进程，这些都可以借助lsof帮助查看端口。

7. 修改权限：chmod

- chmod 000 ./index.html

- 可以修改文件权限，这里设为000，这样任何人都无法访问，重新在浏览器请求127.0.0.1:3000/index.html就会因为文件权限不够而无法展示，服务器返回状态码为403，符合我们预期。修改权限后再请求一次可得到状态码200。

8. 网卡信息：ifconfig

- ifconfig

- 如果想看一下整个传输过程，可以使用tcpdump来抓包，但是抓包时参数需要加上网卡信息，这时候可以通过ifconfig来获得网卡信息。

9. 抓包分析：tcpdump

- tcpdump -i eth0 port 3000

- 可以用tcpdump来抓包分析三次握手及数据传输过程，-i之后加上上一步得到的网卡地址，port可以指定监听的端口号。