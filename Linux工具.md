# Linux工具

> Linux下还是有很多超棒的开发工具的。

> 在Linux日常使用中，最常用的命令自然是sudo, ls, cp, mv, cat等，但作为后台开发者，上述命令远远不够。从我的理解来看，合格的C/C++开发者至少需要从开发及调试工具、文件处理、性能分析、网络工具四个方面针对性使用一些开发工具。这里我罗列了一些，大部分都是开发中经常需要使用的命令，有些功能比较简单的命令我会给出一些基本用法，有些本身自带体系（比如vim, gdb等）的命令只能附上链接了。</br>
> 开发及调试工具介绍了从“编辑->编译 -> 分析目标文件 -> 追踪调用过程”的全套常用命令，文件处理部分介绍了查找、统计、替换等基本文本操作命令，性能分析介绍了查看进程信息、CPU负载、I/O负载、内存使用情况等基本命令，网络工具介绍了可以查看“链路层 -> 网络层 -> 传输层 -> 应用层”信息的工具。除此以外，其他命令中也列出了开发者经常会用到的一些命令，基本可以满足日常开发需要。

---

## 目录

---

| Chapter 1 | Chapter 2 | Chapter 3| Chapter 4 |Chapter 5|
| :---------: | :---------: | :---------: | :--------: |:--------:|
|[开发及调试](#pro)|[文件处理](#file)|[性能分析](#sysinfo)|[网络工具](#net)|[其他](#other)|

---

## 内容

---

### <span id = "pro">开发及调试</span>

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
5. 二进制文件分析：objdump
6. 目标文件分析：nm
7. ELF文件格式分析：readelf
8. 跟踪进程栈：pstack
9. 跟踪进程中系统调用：ptrace

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
9. 数据流处理：awk

---

### <span id = "sysinfo">系统信息</span>
> 系统信息主要针对于服务器性能较低时的排查工作，主要包括CPU信息，文件I/O和内存使用情况，通过进程为纽带得到系统运行的瓶颈。

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

    lsof i:53
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

5. 内存使用量：free
    - 内存使用量
    ```shell
    # 可获得内存及交换区的总量，已使用量，空闲量等信息

    free
    ```

6. 监控性能指标：sar

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

7. 网络Debug分析：nc
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

8. 命令行抓包（网络层/传输层）：tcpdump

9. 域名解析工具（应用层DNS协议）：dig
    ```shell
    # 应用层，DNS
    # 打印域名解析结果
    # 打印域名解析过程中涉及的各级DNS服务器地址

    dig baidu.com
    ```

10. 模拟请求（应用层）：curl


### <span id = "other">其他</span>

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
3. 改变文件所有者：chown
4. 创建链接：ln
5. 显示文件尾：tail
6. 版本控制：git
7. 设置别名：alias