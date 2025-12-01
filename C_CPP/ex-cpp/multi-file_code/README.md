### 构建一种新东西
<br>

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
<br>

#### CMakeLists脑残
##### 入门如入坟
+ 参考链接
  + [CMake Tutorial](https://cmake.org/cmake/help/latest/guide/tutorial/index.html)
+ 编译基本指令：
  + `cmake -S <dir>`：指定项目的根目录，针对存在多个`CMakeLists.txt`的情况
  + `cmake -B <dir>`：指定项目的输出目录，当未创建此项目的`build`文件夹时，会自动创建，此时还未编译文件
  + `cmake --build <dir>`：在`build`文件夹中查找构建项目所需的文件，形成可执行文件
  + `cmake -G <Ninja/...> -B build`：选择特定的编译器
  + 构建过程：
  ```sh
  > cmake -B build
  ... # 构建build文件夹内容
  > cmake --build build # 找到build文件夹，进行可执行文件编译
  ```
+ 形成结构：
  + 最小版本与项目名称：
    ```cmake
    cmake_minimum_required(VERSION 3.23)
    
    project(MyProjectName)
    ```
  + 生成项目可执行文件：
    ```cmake
    add_executable(MyProgram)
    
    target_source(MyProgram
      PRIVATE
        main.cxx  # 构建项目所需的源码
    )
    ```
  + 目标生成（`target`命令）：
    + `PRIVATE`：当使用构建时调用它，需要手动包含
    + `PUBLIC`：当调用库以及构建都会调用【明确会使用到】
    + `INTERFACE`：接口文件，不参与构建过程
<br>

##### 进阶1
+ `CMake`语言基础
  + 阶段0
    + `set(var "World")`：设置变量转换
      + 展开变量`${var}`为`"World"`
      + 许多字符串充当了`CMake`中的布尔值
    + `cmake -P`称之为“脚本模式”，不进行构建任何可执行文件，因此不会发生构建错误
  + 阶段1：宏、函数以及列表
    + 宏