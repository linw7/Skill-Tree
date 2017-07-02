# Linux工具

> Linux下还是有很多超棒的开发工具的。

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
2. 编译器：gcc/g++
3. 调试工具：gdb
4. 查看依赖库：ldd
5. 二进制文件分析：objdump
6. 目标文件分析：nm
7. ELF文件格式分析：readelf
8. 跟踪进程栈：pstack
9. 跟踪进程中系统调用：ptrace

---

### <span id = "file">文件处理</span>

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

4. 监控性能指标：sar

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

1. 检查网络连通性：ping
2. 转发路径：traceroute
3. 域名解析工具：dig
4. 模拟请求：curl
5. 网卡配置：ifconfig 
6. 查看路由表：route
7. 查看当前网络连接：netstat
8. 查看网络流量：iftop
9. 网络Debug分析：nc
10. 命令行抓包：tcpdump


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

2. 分析线程栈：pmap
    - 输出内存进程内存的状况
    ```shell 
    # 直接加具体进程PID

    pmap 12345
    ```
3. 修改文件权限：chmod
4. ......
