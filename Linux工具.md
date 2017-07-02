# Linux工具

> Linux下还是有很多超棒的开发工具的。

---

## 目录

---

| Chapter 1 | Chapter 2 | Chapter 3| Chapter 4 |
| --------- | --------- | --------- | -------- |
|[开发工具](#pro)|[文件处理](#file)|[系统信息](#sysinfo)|[网络工具](#net)|

---

## 内容

---

### <span id = "pro">开发工具</span>

> 待补充

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

> 待补充

---

### <span id = "net">网络工具</span>

> 待补充
