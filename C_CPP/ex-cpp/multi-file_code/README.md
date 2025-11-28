#### Makefile小白

##### 学习链接
+ [自动变量](https://www.zhaixue.cc/makefile/makefile-autoval.html)
+ [Makefile简单速成](https://www.bilibili.com/video/BV1JLCyBAEKi?spm_id_from=333.788.player.switch&vd_source=b2ad62d88b80d1a56dda0e1ee63e40cf&trackid=web_related_0.router-related-2206419-kqnfh.1764310300700.196)
<br>

##### 规则
+ 隐式规则：某些编译命令可以不书写命令。如：
  ```Makefile
  blah: blah.o
  
  blah.o: blah.cpp
  ```
+ 习惯命名：
  + `CC = gcc`：默认使用`C`的编译器
  + `CFLAGS`：为`C`编译器增加拓展项
  + `CXX = g++`：默认使用`C++`编译器
  + `CXXFLAGS`：为`C++`编译器增加拓展项
  + ……
+ 过滤器：可以使用如下方法筛选列表内容进行编译
  ```Makefile
  obj_files = foo.result bar.o lose.o
  src_files = foo.raw bar.c lose.c
  
  all: $(obj_files)
  .PHONY: all
  
  $(filter %.c,$(obj_files)): %.o: %.c
    g++ -c $< -o $@

  $(filter %.result,$(obj_files)): %.result: %.raw
    g++ $< -o $@
  ```
+ 双冒号：可以将一条规则分多块进行定义（允许同名规则补充）
+ `@`：执行时不打印该行命令
+ `.PHONY`：伪目标，用于执行特殊操作，使得直接`make`时不会构建