### Rust笔记
+ 参考资源：
  + [Rust 语言圣经](https://course.rs/advance/intro.html)
  + [Linux上安装rust](https://zhuanlan.zhihu.com/p/308452799)
<br>

#### 圣经之言
##### 避免入门到放弃
+ 画个饼给自己：Rust 是一门全新的语言，会带给你前所未有的体验，提升你的通用编程水平，甚至于赋予你全新的编程思想
+ 避免试一试的心态：开始接触 Rust 核心概念时（所有权、借用、生命周期、智能指针等），难度会陡然提升，此时就需要认真对待起来，否则会为后来埋下难以填补的坑，结果只有两个选择 - 重新学 or 放弃
<br>

##### 认识 Cargo
+ 包管理器工具最重要的意义就是**任何用户拿到代码都可以运行起来**，而不会被各种包依赖搞得焦头烂额
+ 而`cargo`提供了一系列工具，从项目建立、构建到测试、运行直至部署，为 Rust 项目管理提供了尽可能完整的手段。同时，与 Rust 语言及其编译器 `rustc` 紧密结合
+ 创建一个`world_hello`项目：
  ```sh
  $ cargo new <项目名>
  $ cd <项目名>
  $ cargo run   # 编译项目
  ```
  这其中的`cargo run`实际上相当于执行了两部：编译和运行
  ```sh
  $ cargo build
  $ ./target/debug/<项目名>
  ```
  值得注意的是，此时的项目仍然是`debug`模式，此时编译器不进行任何优化，编译速度会很快，但是运行速度慢。
  此时可以考虑`release`进行编译：
  ```sh
  $ cargo run --release
  $ cargo build --release
  ```
+ `cargo check`：这个命令可以帮助快速检查一下代码能否编译通过
+ 两种核心文件：
  + `cargo.toml`：这是**项目数据描述文件**。它存储了项目的所有元配置信息，如果 Rust 开发者希望 Rust 项目能够按照期望的方式进行构建、测试和运行，那么，必须按照合理的方式构建 `Cargo.toml`。
  + `Cargo.lock` 文件是 cargo 工具根据同一项目的 `toml` 文件生成的项目依赖详细清单，因此我们一般不用修改它，只需要对着 `Cargo.toml` 文件撸就行了。
+ package 配置段落
  + package 中记录了项目的描述信息，典型如下：
    ```makefile
    [package]
    name = "world_hello"
    version = "0.1.0"
    edition = "2021"
    ```
+ 定义项目依赖：
  + 在`cargo.toml`中，主要通过各种依赖段落来描述该项目的各种依赖项：
    + 基于 Rust 官方仓库`crates.io`，通过版本说明来描述
    + 基于项目源代码的`git`仓库地址，通过 URL 来描述
    + 基于本地项目的绝对路径或者相对路径，通过类 Unix 模式的路径来描述
  + 具体写法如下：
    ```makefile
    [dependencies]
    rand = "0.3"
    hammer = { version = "0.5.0"}
    color = { git = "https://github.com/bjz/color-rs" }
    geometry = { path = "crates/geometry" }
    ```
<br>

#### Rust 基础
##### Rust 初印象
~`world_hello.rs`中的`greet_world()`~
+ 首先，Rust 原生支持 UTF-8 编码字符串
+ 其次，`println!`的`!`，在 Rust 中，这是 `macro`（宏）操作符；另外因为没有`%s`、`%d`等占位符，而使用`{}`进行相应操作
+ 最后，和其它语言不同，Rust 的集合类型不能直接进行循环，需要变成迭代器（这里通过`.iter*()`方法），才能用于迭代循环
  + 在`2021 edition`及之后，`for region in regions`中的`regions`隐式转换成迭代器
<br>

~`world_hello.rs`中的`test()`~
+ 方法语法：Rust 没有继承，但是却又具备成员方法的使用
+ 高阶函数编程：函数可以作为参数也能作为返回值。例如：`map(|field| field.trim())`，这里`map`方法中使用匿名函数作为参数
+ 条件编译：`if cfg!(debug_assertions)`说明紧跟其后的输出只在`debug`模式下生效
+ 隐式返回：`return`关键字用于函数返回，但是在很多时候可以被忽略，因为 Rust 是 **基于表达式的语言**
<br>

##### 变量
+ 变量绑定：类似于赋值，只不过 Rust 要求分配的内存对象都有主人（所有权），因此所谓的“绑定”，就是将这个对象绑定给一个变量，使其成为它的主人
+ 变量可变性：Rust 变量在默认情况下是**不可变的**，但是也可以通过`mut`关键字让变量变为**可变的**【项目`variables`】
+ 忽略未使用变量：告诉 Rust 不要警告未使用变量，为此可以使用下划线作为变量名的开头
  + `_<var>`仍会绑定内容到变量上，但是`_`直接不会进行绑定
+ 变量解构：`let`表达式可以用于变量的绑定，也能类似`Python3`那样进行多个绑定
  + 在 `Rust 1.59` 版本后，可以在赋值语句的左值中使用元组、切片和结构体模式
+ 变量与常量的差异：
  + 常量不允许使用`mut`，**不仅仅默认不可变，而且自始至终不可变**，因为编译之后，已经确定它的值
  + 常量使用`costant`关键字，而不是`let`关键字来声明，并且值的类型**必须标注**
    ```rust
    const MAX_POINTS: u32 = 100_000;
    ```
+ 变量遮蔽（shadowing）：Rust 允许声明相同的变量名，后面声明的变量会遮蔽掉前面声明的
  + 这和`mut`变量的使用不同，第二个`let`生成了完全不同的新变量，只是刚好重名，涉及到内存对象的再分配【要求类型要相同】
    ```rust
    // 一个类型错误的例子
    let mut spaces = "   ";
    spaces = spaces.len();  // 类型错误：`&str`被分配了`usize`类型
    ```
  + 而`mut`会更改同一内存地址上的值，并不会发生内存再分配，性能更好
<br>

##### 基本类型
+ Rust 每个值都有其确切的数据类型，基本分为基本类型与复合类型
  + 基本类型意味着它们往往是一个最小化的原子类型（无法解构为其他类型）
    + 数值类型：有符号整数 (i8, i16, i32, i64, isize)、 无符号整数 (u8, u16, u32, u64, usize) 、浮点数 (f32, f64)、以及有理数、复数
    + 字符串：字符串字面量和字符串切片 &str
    + 布尔类型：true 和 false
    + 字符类型：表示单个 Unicode 字符，存储为 4 个字节
    + 单元类型：即 () ，其唯一的值也是 ()
+ 类型推导与标注：
  + Rust 编译器可以根据变量的值和上下文的使用方式来自动推导出变量类型
  + 但有时候无法推导出，这时就需要手动进行类型标注【一个例子】
      ```rust
      let guess = "42".parse.expect("Not a number!");
      // 无法推导出 guess 的类型
      ```
<br>

###### 数值类型
+ 整数类型：没有小数部分的数字，内置了`i<size>`与`u<size>`两种（有符号与无符号）【一般`<size>`对应到 `8~128`（每次增长一倍）】
  + 有符号数规定范围为 $-(2^{n-1})\sim 2^{n-1}-1$
  + 另外，还具有一个`isize`与`usize`类型，其中的`size`与计算机 CPU 类型有关
  + 不同进制的内容实际上类似`C/C++`等语言的表示方式，使用`_`进行连接处理，字节量类似`b'A'`
+ 整型溢出：
  + 在 debug 模式编译时，Rust 会检查整型溢出，若存在此类问题，编译时会发生`panic`（崩溃，Rust 使用此术语表明程序因错误而退出）
  + 但在使用`--release`参数运行进行`release`模式构建时，Rust 不检测溢出。当出现溢出情况时，会按照**补码循环溢出**（`two's complement wrapping`）规则处理。【转换为这一范围的值】
  + 要显式处理可能的溢出，可以用标准库针对原始数字类型提供的这些方法：
    + 使用`wrapping_*`方法在**所有模式下都按照补码循环溢出规则处理**，例如`wrapping_add`
    + 使用`check_*`方法溢出时，则返回`None`值
    + 使用`overflowing_*`方法返回该值和判断溢出结果的布尔值
    + 使用`saturating_*`可以限定计算后结果不超过目标类型的最大值或低于最小值，形式如`<tar>.saturating_<op>(<num>)`
+ 浮点类型：Rust 中的浮点数具有两种基本类型`f32`与`f64`，默认使用后者，在现代的 CPU 中两者速度几乎相同（使用`IEEE-754`标准实现）
  + 浮点数陷阱：
    + **浮点数只是某个数字的近似表达**，因为其实现基于二进制，因此无法表示许多小数
    + **浮点数在某些特性上是反直觉的**，`f32`与`f64`上的比较运算实现的是`std::cmp::PartialEq`而非`std::cmp::Eq`特征（部分相等）
  + 避免这两个陷阱，需要遵守两个准则：
    + 避免在浮点数上测试相等性
      ```rust
      fn main() {
        assert!(0.1 + 0.2 == 0.3);  // 导致错误
        assert!((0.1_f64 + 0.2 -0.3).abs() < 0.00001);  // 判断正常
      }
      ```
    + 当结果在数学上可能存在未定义时，需要格外小心
      + 对于数学上未定义的结果，会产生浮点数`NaN`，但是`NaN`不能用于比较
      + 可以使用`is_nan()`等方法，用于判断一个数值是否为`NaN`
<br>

##### 数字运算
+ 基本数学运算：Rust 支持所有数字类型的加法、减法、乘法、除法与取模运算
+ 位运算：基本与其它语言一样
  + 移位运算：Rust 会检查移位内容是否会超过该整型的位数范围，若超出则报错`overflow`
+ 序列：Rust 提供了类似`1..5`这样的表达，用于生成1到4的连续数值
  + 序列只能使用数字或字符类型，如`'a'..='z'`
+ 类型转换：Rust 可以使用`as`来完成类型转换
  + 需要注意应当转换到更大范围，这也就牵涉到“传递性”问题，类型转换不具备传递性，`e as U1 as U2`合法不代表`e as U2`合法
  + 内存地址转换为指针
    ```rust
    let mut values: [i32; 2] = [1, 2];
    let p1: *mut i32 = values.as_mut_ptr();
    let first_address = p1 as usize;  // 将p1内存地址转换为一个整数
    let second_address = first_address + 4; // 4 == std::mem::size_of::<i32>()  i32类型占用4个字节
    let p2 = second_address as *mut i32;  // 访问该地址指向的下一个整数p2
    unsafe {
      *p2 += 1;
    }
    assert_eq!(values[1], 3);
    ```
+ 有理数和复数：这两种类型未包含在标准库中，依赖于社区的`num`库
  + 复数包含实部`.re`和虚部`.im`
<br>

##### 字符、布尔、单元类型
+ 字符类型：基本使用`Unicode`值的范围从`U+0000~U+D7FF`和`U+E000~U+10FFFF`，因此字符类型也是占用 4 个字节。另外，也只能用`''`
+ 布尔：占用1字节
+ 单元类型：`unit`或者说`()`（唯一的值）
  + `fn main(), println!()`返回值就是单元类型，而并非无返回值的【无返回值的是发散函数（diverging functions），无法收敛的函数】
  + 其中的字节数基本为0，基本就是外套别名
<br>

##### 语句和表达式
+ Rust 的函数体是由一系列语句组成的，最后一个表达式代表返回值（无需`return`）
  + 对于 Rust 而言，区分语句（statement）和表达式（expression）非常重要，后者总会返回值
<br>

###### 语句
+ 语句完成了一个具体的操作，但是并没有返回值
+ 因此，语句不能作为左值的赋值内容
  + 不过`let`语句作为表达式已经是实验功能了，可能之后就可以作为表达式内容了
<br>

###### 表达式
+ 表达式会进行求值，然后返回一个值（不包括`;`以及`=`等赋值语句）
  + 满足这样类似情况的有：函数调用、宏的调用以及花括号包裹的部分
  + **表达式不包含分号**
  + 假如表达式不返回任何值，则会隐式返回一个`()`
+ 由于表达式的特性，便可以与`if`语句结合
  ```rust
  fn main() {
    assert_eq!(ret_unit_type(), ())
  }
  
  fn ret_unit_type() {
    let x = 1;
    
    // if语句块构成的表达式（类似三元运算符）
    let y = if x % 2 == 1 {
      "odd"
    } else {
      "even"
    };
    
    // 单行
    let z = if x % 2 == 1 { "odd" } else { "even" };
  }
  ```
<br>

##### 函数
+ 一个例子：
  ```rust
  fn add(i: i32, j: i32) -> i32 {
    i + j
  }
  ```
+ 函数要点：
  + 函数名和变量名使用**蛇形命名法**（例如：`fn add_two() {}`）
  + 函数的位置可以随意摆放，Rust 不关心在哪里定义的函数
  + 每个函数参数**都应标记类型**，否则会报错
+ 函数返回：
  + 可以在最后一条以表达式方式返回
  + 也可以使用`return`提前返回（没有`;`）
+ 永不返回的发散函数：使用`!`作为返回类型，这种语法往往用作会导致程序崩溃的函数：
  ```rust
  fn dead_end() -> ! {
    panic!("You have no way! ");
  }
  ```
  下面的无限循环也不会返回：
  ```rust
  use std::thread;
  use std::time;
  
  fn forever() -> ! {
    loop {
      // ...
      thread::sleep(time::Duration::from_secs(1));
    };
  }
  ```
  + 一些可以用于前者的函数：`panic!()`、`unimplemented!()`以及`todo!()`
  + 另外，发散函数可以替代任意返回值
<br>

##### 所有权
> 所有的程序都必须与计算机内存打交道，如何从内存中申请空间存放内容，如何在不需要时释放这些空间，便是编程语言设计的难点和重点
+ 在计算机语言不断地演化过程中，出现了三种流派：
  + **垃圾回收机制（GC）**：在程序运行时不断寻找不再使用的内存，典型代表：Java、Go
  + **手动管理内存的分配和释放**：在程序中，通过函数调用的方式来申请和释放内存，典型代表：C++
  + **通过所有权来管理内存**：编译器在编译时会根据一系列规则进行检查
+ Rust 选择了第三种方式，这种检查只发生在编译期，因此不会影响程序运行期，不会有任何性能损失
<br>

###### 一段不安全的代码
+ 一段糟糕的C语言代码：
  ```c
  int* foo() {
    int a;
    a = 100;
    char* c = "xyz";
    return &a;
  }
  ```
  + 这段代码虽然可以通过编译，但是十分糟糕，首先是`a`：
    + 因为变量`a`与变量`c`都是局部变量，函数结束会返回局部变量`a`的地址
    + `a`存在于栈中（不是`malloc`分配），而在离开函数体时内存便会被回收，从而返回一个`悬空指针 (Dangling Pointer)`
  + 另外来看变量`c`：
    + 它是个常量字符串，存储在常量区，可能这个函数只调用一次就不再使用这个字符串，但是`"xyz"`占用的区域只有整个程序结束后，系统才能回收这片内存
<br>

###### 栈(Stack)和堆(Heap)
+ 栈：由于其实现原因，储存的所有的数据都必须占用已知且固定大小的内存空间
  + 储存或移出数据时，进行“入栈”或“出栈”操作
  + 其“先进后出”的结构决定了，先储存数据后取出
+ 堆：与栈不同，它可以储存大小未知或者可能变化的数据
  + 当存储大小未知或者可能变化的数据时，将它存储在堆上
  + 分配(allocating)：操作系统会在内存中找到一块足够大的空位标记为已使用，并返回一个表示该位置地址的**指针**，该过程被称为**在堆上分配内存**
  + 但这还没有结束，该指针之后会被推入栈中，因为指针大小是已知且固定的，在后续使用过程中可以通过栈上的**指针**，来获取实际数据在堆上所储存的位置
+ 性能区别：
  + 在栈上分配内存比在堆上分配内存快，因为前者入栈时无需操作函数调用（或更慢的系统调用）；
  + 但是后者不仅需要考虑分配内存空间是否足够大，在进程分配的内存页不足时，还需要进行**系统调用**来申请更多内存
+ 所有权与堆栈：
  + 由于栈是先入后出的，因此当函数调用结束后，这些值将从栈顶逐个移除
  + 可是堆上的数据缺乏组织，因此较难跟踪这些数据是何时分配和释放的，内存无法正常回收会导致内存泄漏
<br>

###### 所有权原则
+ 谨记以下规则：
  + Rust 中每一个值都被一个变量所拥有，该变量称为值的所有者
  + 一个值同时只能被一个变量所拥有，或者说一个值只能拥有一个所有者
  + 当所有者（变量）离开作用域范围时，这个值将被丢弃(drop)
+ 变量作用域：这个变量在程序中生效的范围（与其他语言类似）
+ 简单介绍 `String` 类型：
  + Rust 中字面值（`let s = "hello";`）不适用于所有场景，原因如下：
    + 字符串的字面值是不可变的
    + 并非所有字符串的值都能在编写代码时得知
  + 而`String`可以应付这样的内容，因为它在堆上分配的，这意味着它可以动态存储可变内容
    + 创建`String`类型：
      ```rust
      let s = String::from("hello");
      ```
      `::`是一种调用操作符，这里表示调用`String`类型中的`from`关联函数，由于`String`类型存储在堆上，可以进行修改内容：
      ```rust
      let mut s = String::from("hello");
      s.push_str(", world!"); // 在字符串后追加字面值
      println!("{}", s);
      ```
<br>

###### 变量绑定背后的数据交互
+ 转移所有权
  + 未发生所有权转移的例子：下面的代码中通过**自动拷贝**方式来赋值，因此没有进行所有权转移
    ```rust
    let x = 5;
    let y = x;
    ```
  + 针对非基本类型的内容：
    ```rust
    let s1 = String::from("hello");
    let s2 = s1;
    ```
    由于这个类型是建立在堆上的，因此不能自动拷贝，这里需要区分两部分考虑（复合类型中的基本类型与堆指针）
    + 其中的基本类型部分（如字符串长度、容量等），直接使用自动拷贝可以完成赋值
    + 但是针对堆指针这一内容，需要单独分配空间复制内容（深拷贝）或者拷贝指针内容指向对应内存（浅拷贝），前者性能会面临较大影响，但后者在释放资源时可能会出现**二次释放**的问题
    + 而 Rust 认为的是所有权仅持有在最新被赋值者手中，也就是说`s2`持有了原本`s1`内容的所有权，而`s1`的所有权就丧失了，这种类似浅拷贝的方式被称为**移动(move)**（移交栈上的数据块，堆上不变）
  + 不过还有下述方式进行所有权的绑定：
    ```rust
    fn main() {
      let x: &str = "hello, world";
      let y = x;
      println!("{},{}",x,y);
    }
    ```
    + 这段代码能正常运行，这是因为其与之前的`String`有一个本质上的区别
      + 第一个例子中，`s1`持有了通过`String::from("hello")`创建值的所有权
      + 而这个例子中，`x`只是引用了存储在二进制文件中的字符串，并不持有所有权
      + 因此所谓的`let y = x`中，仅仅是对该引用进行了拷贝，此时二者都引用了同一字符串
+ 克隆（深拷贝）
  + 首先，**Rust 永远也不会自动创建数据的“深拷贝”**
  + 如果**确实**需要深度复制`String`中堆上的数据，可以使用`clone`方法
    ```rust
    let s1 = String::from("hello");
    let s2 = s1.clone();
    
    println!("s1 = {}, s2 = {}", s1, s2);
    ```
    `clone`会极大的降低程序性能，需要小心使用
+ 拷贝（浅拷贝）
  + 浅拷贝仅发生在栈上，因此性能会很高
  + 为了避免在赋值时发生所有权转移的情况，Rust 中的`Copy`特征就起了作用，以下可以发生`Copy`的类型有：
    + 所有整数类型
    + 布尔类型
    + 所有浮点数类型
    + 字符类型（`char`）
    + 元组，这个要求其中的元素也是可以`Copy`的
    + 不可变引用`&T`，但是注意可变引用`&mut T`是不可`Copy`的
  + 移交所有权时，假如原对象是可变的，且之后需要修改内容，移交所有权时需要标明`mut`
  + 部分`move`：有时变量结构中的部分变量的所有权会被移交给其它变量，此时，原本结构中的内容就变为不可用，因为所有权已经被移交了
    ```rust
    fn main() {
      #[derive(Debug)]
      struct Person {
        name: String,
        age: Box<u8>,
      }

      let person = Person {
        name: String::from("Alice"),
        age: Box::new(20),
      };

      // 通过这种解构式模式匹配，person.name 的所有权被转移给新的变量 `name`
      // 但是，这里 `age` 变量却是对 person.age 的引用, 这里 ref 的使用相当于: let age = &person.age 
      let Person { name, ref age } = person;

      println!("The person's age is {}", age);

      println!("The person's name is {}", name);

      // Error! 原因是 person 的一部分已经被转移了所有权，因此我们无法再使用它
      //println!("The person struct is {:?}", person);

      // 虽然 `person` 作为一个整体无法再被使用，但是 `person.age` 依然可以使用
      println!("The person's age from person struct is {}", person.age);
    }
    ```
<br>

##### 函数传值与返回
+ 将值传递给函数，也会发生`move`或者`Copy`，就和`let`语句类似
  + 因此对于复合对象来说，很容易出现调入函数之后，这个变量就不具备对这一对象的所有权了
  + 但是基本类型的对象由于具备`Copy`特征，就不需要担心这点
<br>

##### 引用与借用
+ 上述介绍的转移所有权方式获取一个值虽然安全，但是那会让程序变得复杂
+ 因此，Rust 通过`借用(Borrowing)`这个概念来达成上述目的，**获取变量的引用，称之为借用**
<br>

###### 引用与解引用
+ 常规引用是一个指针类型，可以通过`&<var>`创建引用，使用`*<var>`进行解引用，访问原值
  ```rust
  fn main() {
    let x = 5;
    let y = &x;
    let ref z = x;  // 引用符号
    
    assert_eq!(5, x);
    assert_eq!(5, *y);
    assert_eq!(y, z);
  }
  ```
<br>

###### 不可变引用
+ 一个引用的例子：
  ```rust
  fn main() {
    let s1 = String::from("hello");
    
    let len = calculate_length(&s1);
    println!("The length of '{}' is {}.", s1, len);
  }
  
  fn calculate_length(s: &String) -> usize {
    s.len()
  }
  ```
  可以注意到两点：
  + 无需像之前一样传入所有权之后再返回来传出所有权
  + 改变就是传入参数变为了`&String`
+ 但是引用只是允许使用值，但是不获取所有权，这也就意味着**引用指向的值默认不可变**
+ 另外，不可变引用是可以多个同时存在的，相当于`读操作`
<br>

###### 可变引用
+ 为了安全起见，要引用值可变，需要原本指向的变量可变，也就是：
  ```rust
  fn main() {
    let mut s = String::from("hello");

    change(&mut s); // 可变引用必须标注明
  }

  fn change(some_string: &mut String) {
    some_string.push_str(", world");
  }
  ```
  应该注意到以下几点：
  + 不过，可变引用只能存在一个（同一作用域，特定数据只能有一个可变引用），毕竟`写操作`是不能两者同时操作的，就如这里的：
    ```rust
    let mut s = String::from("hello");

    let r1 = &mut s;  // 这里的数据借用持续到最后一次使用位置
    let r2 = &mut s;  // 因此

    println!("{}, {}", r1, r2);
    ```
  + 另外，可变引用与不可变引用不能同时存在
+ NLL(Non-Lexical Lifetimes)：原本上述代码的引用要直至作用域结束才会结束，但编译器做了优化，使其在最后一次使用处结束，这种编译器的优化被称为 NLL
+ 悬垂引用（Dangling References）：指针指向某个值后，这个值被释放了，但指针仍然存在
  + Rust 编译器内确保了数据不会在引用结束前释放，只有引用停止使用才会释放数据
<br>

###### 借用规则总结
+ 借用规则如下：
  + 同一时刻，只能拥有一个可变引用或是任意多个不可变引用
  + 引用必须总是有效的
<br>

##### 复合类型
+ 复合类型是由其它类型组合而成的，较典型的就是`struct`和`enum`
<br>

###### 字符串
+ 切片(slice)：使用如下的方式进行切片，其中的索引也是左闭右开区间，类型为`&str`
  ```rust
  let s = String::from("hello world");
  
  let hello = &s[0..5];
  let world = &s[6...11];
  ```
  + 其中的两个序列可以等效为`[..5]`以及`[6..]`，截取完整切片可以使用序列`[..]`
  + 但需要注意的是，切片时必须保证切的字符是完整的，譬如一个中文字符为3字节，当截取`[0..2]`时就会崩溃
  + 另外需要注意，**切片操作是不可变借用`&str`（字符串字面量）类型**，因此改变原字符串的可变操作会导致编译出错
  + 其它类型的切片：
    ```rust
    let a = [1, 2, 3, 4, 5];
    let slice = &a[1..3];
    assert_eq!(slice, &[2, 3]);
    ```
    这里的数组切片类型是`&[i32]`
  + 和数组区别：
    ```rust
    // 数组类型为 [<T>; <len>]
    let arr: [char; 3] = ['中', '国', '人'];
    let slice: [&char] = &arr[..2]; // 引用类型为 [&<T>]
    ```
+ 字符串：虽然 `String` 的底层是 `Vec<u8>` 也就是字节数组的形式存储的，但是它是基于 UTF-8 编码的字符序列
  + Rust 的字符是 Unicode 类型，因此每个字符占据4个字节内存空间
  + 但是字符串中不一样，字符串是 UTF-8 编码，也就是字符串中的字符所占的字节数是变化的 1$\sim$4，大幅降低了字符串所占用的内存空间
  + `String` 分配在堆上、可增长且不是以`null`结尾
+ `String`与`&str`的转换：
  + `&str`转换为`String`：以下两种方式都可以将字符串字面量转换为字符串
    ```rust
    String::from("hello, world")
    "hello, world".to_string()
    ```
  + `String`转换为`&str`：只需要进行取引用
    ```rust
    fn main() {
      let s = String::from("hello, world");
      say_hello(&s);
      say_hello(&s[..]);
      say_hello(s.as_str());
    }
    
    fn say_hello(s: &str) {
      println!("{}", s);
    }
    ```
    这种灵活用法是因为`deref`隐式强制转换
+ 字符串索引：在字符串不能使用`s[0]`这样的方式直接访问字符，需要使用引用`&s[<range>]`
  + 字符串内部：字符串底层的数据存储格式实际上是`[u8]`（一个字节数组），而不同的字符对应的字节数不同，于是进行引用切片时也需要相当小心
  + 字符串的不同表现形式：由于上述原因以及性能的考虑，Rust 中不允许去索引字符串
+ **操作字符串**
  + 追加 (Push)：下面的方法都是**在原有的字符串上追加，并不会返回新的字符串**（所以原字符串必须由`mut`修饰）
    + 在字符串尾部可以使用`push()`方法追加字符`char`
    + 也可以使用`push_str()`方法追加字符串字面量
  + 插入 (Insert)：下面的方法都需要传入两个参数，第一个是插入位置的索引，第二个是要插入的内容
    + 可以使用`insert()`方法插入单个字符`char`
    + 也可以使用`insert_str()`方法插入字符串字面量
  + 替换 (Replace)：前两个方法都会返回新字符串
    + `replace`，可以将字符串中的所有`目标字符串`替换为`新字符串`，接收的参数有两个，一个是要被替换的字符串，另一个是替换的新字符串
    + `replacen`：承接`replace`，添加了一个新参数确定替换的次数
    + `replace_range`：该方法是直接操作原来的字符串（需要`mut`修饰），不返回新的字符串；第一个参数是要替换字符串的范围 (range)，第二个参数是用于替换的新字符串
  + 删除 (Delete)：这些方法仅适用于`String`，均是**直接操作原字符串**
    + `pop`：删除并返回字符串的最后一个字符（若字符串为空，则返回`None`）
    + `remove`：删除并返回字符串中指定位置的字符，仅接收一个参数表示起始索引位置（字节）
    + `truncate`：删除字符串中从指定位置开始到结尾的全部字符，也要求参数是字符的合法边界
    + `clear`：清空字符串
  + 连接 (Concatenate)：
    + `+`以及`+=`连接字符串，但是第二个加数必须使用`&str`，`+=`需要第一个参数标注`mut`，`+`不需要
      + 进行运算后，第一个参数所有权会被移交（需要注意）
    + 使用`format!`连接字符串，返回新字符串，用法类似`print!`
+ 字符串转义：
  + 字符转义：可以通过转义的方式`\`输出`ASCII`和`Unicode`字符
    + Unicode 字符：`let c = "\u{211D}";`
    + 字节码：`let c = "\x52";`
  + 其它编码字符串：
    + `r"<str>"`：raw 字符串，不进行转义
    + `b"<str>"`：字节数组字符串
      + 不支持 Unicode
      + 只能在`Debug`情况下打印（因为没有`Display`特征）
      + 转换至`str`时可能会失败
      + 字节数组可以不是 UTF-8 形式
  + 保持原样，不进行转义：
    ```rust
    fn main() {
      println!("{}", "hello \\x52\\x75\\x73\\x74");
      let raw_str = r"Escapes don't work here: \x3F \u{211D}";
      println!("{}", raw_str);

      // 如果字符串包含双引号，可以在开头和结尾加 #
      let quotes = r#"And then I said: "There is no escape!""#;
      println!("{}", quotes);

      // 如果字符串中包含 # 号，可以在开头和结尾加多个 # 号，最多加255个，只需保证与字符串中连续 # 号的个数不超过开头和结尾的 # 号的个数即可
      let longer_delimiter = r###"A string with "# in it. And even "##!"###;
      println!("{}", longer_delimiter);
    }
    ```
+ 操作 UTF-8 字符串
  + 字符：如果希望使用 Unicode 字符的方式遍历字符串，最好使用`chars()`，例如：
    ```rust
    for c in "中国人".chars() {
      println!("{}", c);
    }
    ```
  + 字节：返回字符串底层字节数组表现形式`bytes()`
  + 获取子串：这里需要使用到`utf8_slice`这个库
    ```rust
    // 截取字符串切片[begin..end]
    let sl: &str = utf8_slice::slice(s: &str, begin: usize, end: usize);
    
    // 截取字符串切片[begin..]
    let sl: &str = utf8_slice::from(s: &str, begin: usize);
    
    // 截取字符串切片[..end]
    let sl: &str = utf8_slice::till(s: &str, end: usize);
    
    // 计算UTF-8的长度
    let sl: usize = utf8_slice::len(s: &str);
    ```
+ 字符串中的内存管理哲学
  + 字符串字面量 (`str`) 不可变，而字符串 (`String`) 的原因在于内存回收方式
    + 前者编码时就确定了空间大小
    + 而后者需要向操作系统请求内存存放`String`对象，在使用完成后释放内存，归还操作系统
      + Rust 实现时采取了`RAII`的管理思想，实现了类似 C++ 的智能指针方式
      + 分配字符串的空间：
        ```rust
        let mut s = String::new();  // 分配0字节的空间
        let mut s = String::with_capacity(len: usize);  // 分配len字节的空间
        
        s.as_mut_ptr(); // 查看对应的指针
        s.len();  // 查看s对应的长度
        s.capacity(); // 查看分配的空间
        ```
  + 字符切片：
    + 一个切片引用占用了2个字大小的内存空间( 从现在开始，为了简洁性考虑，如无特殊原因，我们统一使用切片来特指切片引用 )
    + 该切片的第一个字是指向数据的指针，第二个字是切片的长度。字的大小取决于处理器架构，例如在 x86-64 上，字的大小是 64 位也就是 8 个字节，那么一个切片引用就是 16 个字节大小
<br>

###### 元组
+ 第一印象：
  + 元组允许多种类型组合到一起
  + 可以通过以下方式创建一个元组：
    ```rust
    fn main() {
      let tup: (i32, f64, u8) = (500, 6.4, 1);
    }
    ```
+ 通过使用模式匹配解构元组：
  ```rust
  fn main() {
    let tup = (500, 6.4, 1);

    let (x, y, z) = tup;

    println!("The value of y is: {}", y);
  }
  ```
  + 元组中对应的值会绑定到变量`x, y, z`上。
  + 这就是解构：用同样的形式把一个复杂对象中的值匹配出来
+ 使用`.`解构元组：
  ```rust
  fn main() {
    let x: (i32, f64, u8) = (500, 6.4, 1);

    let five_hundred = x.0;

    let six_point_four = x.1;

    let one = x.2;
  }
  ```
  + 索引从`0`开始
+ 函数场景下，元组可以作为函数返回结构，从而返回多个值
  ```rust
  fn main() {
    let s1 = String::from("hello");

    let (s2, len) = calculate_length(s1);

    println!("The length of '{}' is {}.", s2, len);
  }

  fn calculate_length(s: String) -> (String, usize) {
    let length = s.len(); // len() 返回字符串的长度

    (s, length)
  }
  ```
  + 不过这样组织结构的缺陷是，无法表明某个返回值的具体含义
  + 这个缺陷在`元组结构体`中会得以解决
+ 需要注意：
  + 过长的元组无法被打印输出
<br>

###### 结构体
+ 结构体语法：
  + 结构体组成和元素类似，但是与元组不同的是，结构体可以为内部每个字段起一个富有含义的名称
  + 结构体定义：
    ```rust
    struct User {
      active: bool,
      username: String,
      email: String,
      sign_in_count: u64,
    }
    ```
  + 创建结构体实例：
    ```rust
    let user1 = User {
      email: String::from("someone@example.com"),
      username: String::from("someusername123"),
      active: true,
      sign_in_count: 1,
    };
    ```
    由于没有构造函数一说，所以使用下面的方式也可以进行对应赋值：
    ```rust
    struct Person {
      name: String,
      age: u8,
      hobby: String
    }
    fn main() {
      let age = 30;
      let p = Person {
        name: String::from("sunface"),
        age,
        hobby: String::from("study"),
      };
    } 
    ```
    需要注意：
    + 初始化实例时，**每个字段**都需要进行初始化
    + 初始化时某字段顺序**不需要**和结构体定义顺序一致
  + 访问结构体字段：
    + 通过`.`可以访问结构体实例内部的字段值
    + 结构体不支持部分`mut`，只能设置全`mut`
    ```rust
    let mut user1 = User {
      email: String::from("someone@example.com"),
      username: String::from("someusername123"),
      active: true,
      sign_in_count: 1,
    };

    user1.email = String::from("anotheremail@example.com");
    ```
  + 简化结构体创建：
    ```rust
    fn build_user(email: String, username: String) -> User {
      User {
        email: email,
        username: username,
        active: true,
        sign_in_count:1,
      }
    }
    ```
    当函数参数与结构体字段同名时，可以直接使用缩略方式进行初始化
    ```rust
    fn build_user(email: String, username: String) -> User {
      User {
        email,
        username,
        active: true,
        sign_in_count:1,
      }
    }
    ```
  + 结构体更新语法：在实际场景中，根据已有结构体实例，创建新的结构体实例，例如根据已有的`user1`实例来构建`user2`：
    ```rust
    let user2 = User {
      active: user1.active,
      username: user1.username,
      email: String::from("another@example.com"),
      sign_in_count: user1.sign_in_count,
    };
    ```
    这样的内容也提供了`结构体更新语法`：
    ```rust
    let user2 = User {
      email: String::from("another@example.com"),
      ..user1
    };
    ```
    + `..`使得凡是没有显式声明的字段，都从`user1`中自动获取了，但是`..user1`这样的内容只能在结构体尾部使用
    + 这一用法和赋值语句类似，因此`user1`中的`username`字段的所有权也被移交了，所以`user1`也无法再被使用
+ 结构体的内存排序：
  ```rust
  let user1 = User {
    email: String::from("someone@example.com"),
    username: String::from("someusername123"),
    active: true,
    sign_in_count: 1,
  };
  let user2 = User {
      active: user1.active,
      username: user1.username,
      email: String::from("another@example.com"),
      sign_in_count: user1.sign_in_count,
  };
  println!("{}", user1.active);
  // 下面这行会报错
  println!("{:?}", user1);
  ```
  上面定义的`File`结构体在内存中的排序如下图所示：
  ![](https://pic3.zhimg.com/80/v2-8cc4ed8cd06d60f974d06ca2199b8df5_1440w.png)
  + 从图中可以清晰地看出 `File` 结构体两个字段 `name` 和 `data` 分别拥有底层两个 `[u8]` 数组的所有权（`String` 类型的底层也是 `[u8]` 数组），通过 `ptr` 指针指向底层数组的内存地址，这里你可以把 `ptr` 指针理解为 Rust 中的引用类型。
  + 该图片也侧面印证了：**把结构体中具有所有权的字段转移出去后，将无法再访问该字段，但是可以正常访问其它的字段**。
+ 元组结构体 (Tuple Struct)：结构体必须要有名称，但是结构体的字段可以没有名称（元组结构体）
  ```rust
  struct Point(i32, i32, i32);
  
  let origin = Point(0, 0, 0);
  ```
  + 拆解值时，应当进行如下操作：
    ```rust
    struct Color(i32, i32, i32);
    struct Point(i32, i32, i32);
    fn main() {
      let v = Point(0, 127, 255);
      check_color(v);
    }   

    fn check_color(p: Point) {
      let Point(x, _, z) = p;
      assert_eq!(x, 0);
      assert_eq!(p.1, 127);
      assert_eq!(z, 255);
    }
    ```
+ 单元结构体 (Unit-like Struct)：如果你定义一个类型，但是不关心该类型的内容，只关心它的行为时，就可以使用`单元结构体`：
  ```rust
  struct AlwaysEqual;
  
  let subject = AlwaysEqual;
  
  impl SomeTrait for AlwaysEqual {
    ...
  }
  ```
+ 结构体数据的所有权：
  + 在之前的结构体定义中，使用了`String`类型而不是基于引用的`&str`字符串切片类型，因为需要这个结构体拥有它所有的数据，而不是从其它地方借用数据
  + 也可以让 User 结构体从其它对象借用数据，不过这么做，就需要引入**生命周期(lifetimes)** 这个新概念（也是一个复杂的概念），简而言之，生命周期能确保结构体的作用范围要比它所借用的数据的作用范围要小【假如说不添加生命周期，那么会发生报错】
  + 当然，使用引用`ref`可以引用（而非转移所有权）：
    ```rust
    fn main() {
      #[derive(Debug)]
      struct Person {
          name: String,
          age: Box<u8>,
      }

      let person = Person {
          name: String::from("Alice"),
          age: Box::new(20),
      };

      // 通过这种解构式模式匹配，person.name 的所有权被转移给新的变量 `name`
      // 但是，这里 `age` 变量却是对 person.age 的引用, 这里 ref 的使用相当于: let age = &person.age 
      let Person { name, ref age } = person;

      println!("The person's age is {}", age);

      println!("The person's name is {}", name);

      // Error! 原因是 person 的一部分已经被转移了所有权，因此我们无法再使用它
      //println!("The person struct is {:?}", person);

      // 虽然 `person` 作为一个整体无法再被使用，但是 `person.age` 依然可以使用
      println!("The person's age from person struct is {}", person.age);
    }
    ```
+ 使用`#[derive(Debug)]`来打印结构体信息
  + 结构体是不具有`Display`属性的，这也就意味着无法使用`println!`直接打印
  + 不过 Rust 仍然保留了后路：
    ```rust
    #[derive(Debug)]
    struct Rectangle {
      width: u32,
      height: u32,
    }

    fn main() {
      let rect1 = Rectangle {
        width: 30,
        height: 50,
      };

      println!("rect1 is {:?}", rect1);
    }
    ```
    当结构体较大时，我们可能希望能够有更好的输出表现，此时可以使用 `{:#?}`（进行每个部分换行） 来替代 `{:?}`
  + 使用`dbg!宏`来输出`debug`信息：
    + 它会拿走表达式的所有权，然后打印出相应的文件名、行号等 debug 信息，当然还有需要的表达式求值结果
    + 除此之外，它还会把表达式值的所有权返回
      ```rust
      #[derive(Debug)]
      struct Rectangle {
        width: u32,
        height: u32,
      }

      fn main() {
        let scale = 2;
        let rect1 = Rectangle {
          width: dbg!(30 * scale),
          height: 50,
        };

        dbg!(&rect1);
      }
      ```
      输出以下结果：
      ```sh
      $ cargo run
      [src/main.rs:10] 30 * scale = 60
      [src/main.rs:14] &rect1 = Rectangle {
        width: 60,
        height: 50,
      }
      ```
<br>

###### 枚举
+ 枚举(enum 或 enumeration)：允许你通过列举可能的成员来定义一个**枚举类型**，例如扑克牌花色：
  ```rust
  enum PokerSuit {
    Clubs,
    Spades,
    Diamonds,
    Hearts,
  }
  ```
  + 枚举类型：这个类型包含了所有可能的枚举成员，而枚举值是该类型中的具体某个成员的实例:
    ```rust
    let heart = PokerSuit::Hearts;
    let diamond = PokerSuit::Diamonds;
    ```
    + 可以通过`::`操作符来访问`PokerSuit`下具体成员，可以定义一个函数来使用它们
      + 类型为`PokerSuit`
      + 另外需要在定义前添加`#[derive(Debug)]`才能正常打印
  + 枚举带值：枚举其中的类型不一定完全相同，而且可以带值
    ```rust
    enum Message {
      Quit,
      Move { x: i32, y: i32 },
      Write(String),
      ChangeColor(i32, i32, i32),
    }
    
    // 可以使用整数值直接初始化枚举类型
    enum Exam {
      Zero = 0,
      One = 1,
      Two,
    }

    fn main() {
      let m1 = Message::Quit;
      let m2 = Message::Move{x:1,y:1};
      let m3 = Message::ChangeColor(255,255,0);
    }
    ```
    该枚举类型代表一条消息，这样的操作保证了可以实现某一函数需要选择上述的一种类型时均可以接纳的情况（**同一化类型**），包含四个不同成员：
    + `Quit`没有任何关联数据
    + `Move`包含一个匿名结构体
    + `Write`包含一个`String`字符串
    + `ChangeColor`包含三个`i32`
+ Option 枚举用于处理空值：Rust 抛弃了`null`，改用`Option`枚举变量来表述空值结果 [[官方文档](https://doc.rust-lang.org/std/option/enum.Option.html)]
  + `Option`枚举包含两个成员，一个成员表示含有值`Some(T)`，另一个为`None`，定义如下：
    ```rust
    enum Option<T> {
      Some(T),
      None,
    }
    ```
    + 其中的`T`是泛型参数，`Some(T)`表示该成员的数据类型为`T`
    + `Option`被包含在了`prelude`（属于 Rust 标准库）
    ```rust
    let some_number = Some(5);
    let some_string = Some("a string");
    
    let absent_number: Option<i32> = None;
    ```
    如果使用`None`而不是`Some`，需要显式表示`Some`表示的成员值类型；这有一个显著优势：
    + 由于`Option<T>`与`T`是不同类型，因此两者无法直接进行相互操作
    + 也就是说，想要前者与`T`类型进行运算，必须进行类型转换
<br>

###### 数组
+ 初印象
  + 在 Rust 中，最常用的数组有两种：
    + 第一种是速度很快但是长度固定的`array`（存储在栈上）
    + 第二种可动态增长但是又性能损耗的`Vector`（存储在堆上）
  + 本节中，重点放在`array`，数组的三要素：
    + 长度固定
    + 元素必须有相同类型
    + 依次线性排列
+ 创建数组（数组元素类型要统一，长度固定）
  + 创建：
    可以直接进行创建
    ```rust
    let a = [1, 2, 3, 4, 5];
    ```
    可以声明类型
    ```rust
    let a: [i32, 5] = [1, 2, 3, 4, 5];
    ```
    初始化一个**重复N次值的数组**
    ```rust
    let a = [3; 5]; // 前者为值，后者为数量
    ```
    也可创建多维数组
    ```rust
    let one = [1, 2, 3];
    let two: [u8; 3] = [1, 2, 3];
    let blank1 = [0; 3];
    let blank2: [u8; 3] = [0; 3];
    let arr: [[u8; 3]; 4] = [one, two, blank1, blan2];
    ```
  + 访问数组元素
    + 如同许多语言一样，可以使用索引访问，如`arr[0]`
    + 越界访问：当尝试使用索引访问元素时，Rust 将检查指定的索引是否小于数组长度（检查只能在运行时进行）
      + 可以使用`.get(<index>)`来获得`Option<T>`类型的对应值，就不会发生越界，之后再进行`.unwrap()`获得对应值
      + 而直接使用索引就会有越界风险
  + 数组元素为非基础类型：
    + 一个错误例子：这样的代码会发生报错，原因在于进行多次同值初始化时使用的是`Copy`，而复杂类型无法通过浅拷贝完成（期间可能发生所有权移交）
      ```rust
      let array = [String::from("rust is good!"); 8];
      println!("{:#?}", array);
      ```
    + 正确的简明写法：调用`std::array::from_fn`
      ```rust
      let array: [String; 8] = std::array::from_fn(|_i| String::from("rust is good!"));
      println!("{:#?}", array);
      ```
+ 数组切片：`T`数组切片的类型通常是`&[T]`，主要包含以下特点
  + 切片的长度可以与数组不同，并不固定
  + 创建切片的代价非常小，只是针对底层数组的一个引用
  + 切片类型`[T]`拥有不固定大小，而切片引用类型`&[T]`则具有固定大小
+ 总结：综合性数组例子
  ```rust
  fn main() {
    // 编译器自动推导出one的类型
    let one             = [1, 2, 3];
    // 显式类型标注
    let two: [u8; 3]    = [1, 2, 3];
    let blank1          = [0; 3];
    let blank2: [u8; 3] = [0; 3];

    // arrays是一个二维数组，其中每一个元素都是一个数组，元素类型是[u8; 3]
    let arrays: [[u8; 3]; 4]  = [one, two, blank1, blank2];

    // 借用arrays的元素用作循环中
    for a in &arrays {
      print!("{:?}: ", a);
      // 将a变成一个迭代器，用于循环
      // 你也可以直接用for n in a {}来进行循环
      for n in a.iter() {
        print!("\t{} + 10 = {}", n, n+10);
      }

      let mut sum = 0;
      // 0..a.len,是一个 Rust 的语法糖，其实就等于一个数组，元素是从0,1,2一直增加到到a.len-1
      for i in 0..a.len() {
        sum += a[i];
      }
      println!("\t({:?} = {})", a, sum);
    }
  }
  ```
  几个需要注意的点：
  + **数组类型与数组切片**不同：`[T;n]`是数组类型，而`[T]`是数组切片类型，后者长度无法在编译期得知，就不能用`[T;n]`描述
    + 这也就意味着以下代码会出错：
      ```rust
      fn create_arr(n: i32) {
        let arr = [1; n];
      }
      ```
  + 数组长度也是类型一部分，所以`[T;3]`与`[T;4]`不是同一类型
  + 实际开发过程中，使用最多的是数组切片`[T]`
<br>

##### 流程控制
~`Rust`程序是从上至下执行的，可以通过循环、分支等流程控制方式，更好实现相应功能~
<br>

###### if 分支控制
+ `if-else`**表达式**（会返回值）根据条件执行不同的代码分支
  ```rust
  fn main() {
    let condition = true;
    let number = if condition {
      5
    } else {
      6
    };

    println!("The value of number is: {}", number);
  }
  ```
  这一代码体现了以下几点：
  + `if`语句块是表达式
  + 使用`if`来赋值时最好保证每个分支返回的类型一致，可以不一致，例如：
    ```rust
    let mut v = 0;
    for i in 1..10 {
      v = if i == 9 {
        continue  // 返回了continue
      } else {
        i
      }
    }
    println!("{}", v);
    ```
+ 可以将`else if`与`if-else`组合，形成更复杂的条件分支语句（类似其他语言）
  + 类似地，条件分支匹配的语句块是首个成功的分支
  + 一旦条件判断成功，执行相应语句块后会直接跳出`if`语句块
  + 大量`else if`之后可以使用`match`（模式匹配）解决冗杂的表现
<br>

##### 循环控制
+ 在 Rust 中有三种循环方式：`for`、`while`和`loop`，其中的`for`是 Rust 循环王冠上的明珠
<br>

###### for 循环
+ `for`循环中的一些常见模式：
  + 一个循环序列的输出：
    ```rust
    for i in 1..=5 {  // 将i替换为_便可以达成单纯循环5次，注意1..5只是循环4次
      print!("{} ", i);
    }
    ```
  + `for`与集合的联动：这里的集合指的是`Vec`、`HashMap`等等这样的复合类型
    ```rust
    for <元素> in <集合> {
      ...
    }
    ```
    需要注意，假如说仍然想在`for`代码块之后继续使用此集合，否则该集合的所有权会在`for`内发生转移（这时其实发生了`Copy`，但是集合不具备这一属性），之后便无法使用了
    ```rust
    for item in &container {
      ...
    }
    ```
    如果想在循环中修改集合中的元素，使用`mut`：
    ```rust
    for item in &mut container {
      ...
    }
    ```
    之前的代码中实际上都发生了集合到集合迭代器的隐式转换，下一代码块中既遍历了集合内元素，也给出了索引：
    ```rust
    fn main() {
      let a = [4, 3, 2, 1];
      for (i, v) in a.iter().enumerate() {
        println!("第{}个元素是{}", i + 1, v);
      }
    }
    ```
<br>

###### 一些参与循环控制的关键字
+ `continue`：没啥好说的，跳过这一次循环
+ `break`：没啥好说的，跳出当前的循环体
  + 不过，这个`break`是可以附带一个表达式的（作为返回值）`break <exp>;`
<br>

###### while 循环
+ 基本用法类似其它语言：
  ```rust
  let mut n = 0;
  
  while n <= 5 {
    n = n + 1;
  }
  ```
<br>

###### loop 循环
+ 相当于一个无限循环，允许带值返回，因此`break`便成为了`loop`的最佳拍档
  ```rust
  fn main() {
    let mut counter = 0;

    let result = loop {
      counter += 1;

      if counter == 10 {
        break counter * 2;
      }
    };

    println!("The result is {}", result);
  }
  ```
+ 当有多层循环时，你可以使用`continue`或`break`来控制外层的循环。要实现这一点，外部的循环必须拥有一个标签`'label`, 然后在`break`或`continue`时指定该标签
  ```rust
  fn main() {
    let mut count = 0;
    'outer: loop {
      'inner1: loop {
        if count >= 20 {
          // 这只会跳出 inner1 循环
          break 'inner1; // 这里使用 `break` 也是一样的
        }
        count += 2;
      }

      count += 5;

      'inner2: loop {
        if count >= 30 {
          break 'outer;
        }

        continue 'outer;
      }
    }

    assert!(count == 30)
  }
  ```
<br>

##### 模式匹配
###### `match` 和 `if let`
+ 在 Rust 中，模式匹配最常用的就是`match`和`if let`
  + 一个关于`match`的简单例子：
    ```rust
    enum Direction {
      East,
      West,
      North,
      South,
    }
    
    fn main() {
      let dire = Direction::South;
      match dire {
        Direction::East => println!("East"),
        Direction::North | Direction::South => {
          println!("South or North");
        };
        _ => println!("West");
      };
    }
    ```
    这里去匹配`dire`对应的枚举类型，因此`match`中的匹配分支必须完全覆盖枚举变量中的所有成员类型，有以下几点值得注意：
    + `match`匹配必须要穷举出所有可能，`_`代表未列出的所有可能性
    + `match`的每一个分支必须是一个表达式，且分支表达式最终返回值类型必须相同
    + `X | Y`：表示两个逻辑表达式的运算
+ `match`匹配：
  + 首先是`match`通用形式：
    ```rust
    match target {
      模式1 => 表达式1,
      模式2 => {
        语句1;
        语句2;
        表达式2
      },
      _ => 表达式3
    }
    ```
    相较于`if`之后只能跟布尔表达式，而`match`后的表达式返回值可以是任意类型
  + 使用`match`表达式赋值：由于`match`本身也是一个表达式，因此可以用它来赋值
    ```rust
    enum IpAddr {
      Ipv4,
      Ipv6
    }
    
    fn main() {
      let ip1 = IpAddr::Ipv6;
      let ip_str = match ip1 {
        IpAddr::Ipv4 => "127.0.0.1",
        _ => "::1",
      };
      
      println!("{}", ip_str);
    }
    ```
  + 模式绑定：模式匹配的另一重要功能是从模式中取出绑定的值
    ```rust
    #[derive(Debug)]
    enum UsState {
      Alabama,
      Alaska,
      // --snip--
    }

    enum Coin {
      Penny,
      Nickel,
      Dime,
      Quarter(UsState), // 25美分硬币
    }
    ```
    接下来可以借助模式绑定得到`state`
    ```rust
    fn value_in_cents(coin: Coin) -> u8 {
      match coin {
        Coin::Penny => 1,
        Coin::Nickel => 5,
        Coin::Dime => 10,
        Coin::Quarter(state) => {
          println!("State quarter from {:?}!", state);
          25
        },
      }
    }
    ```
    假如有一个印了阿拉斯加州标记的 25 分硬币：`Coin::Quarter(UsState::Alaska)`，在匹配时，`state`变量将绑定`UsState::Alaska`的枚举值
    再来个复杂的例子：
    ```rust
    enum Action {
      Say(String),
      MoveTo(i32, i32),
      ChangeColorRGB(u16, u16, u16),
    }

    fn main() {
      let actions = [
        Action::Say("Hello Rust".to_string()),
        Action::MoveTo(1,2),
        Action::ChangeColorRGB(255,255,0),
      ];
      for action in actions {
        match action {
          Action::Say(s) => {
            println!("{}", s);
          },
          Action::MoveTo(x, y) => {
            println!("point from (0, 0) move to ({}, {})", x, y);
          },
          Action::ChangeColorRGB(r, g, _) => {
            println!("change color into '(r:{}, g:{}, b:0)', 'b' has been ignored",
              r, g,
            );
          }
        }
      }
    }
    ```
+ 穷尽匹配：`match`的匹配必须穷尽所有情况，否则会发生报错
+ `_`通配符：这个内容在之前的代码也有迹可循，相当于其它语言的`default`关键字，可以匹配所有遗漏值
  + 当然除了`_`通配符，也可以直接使用一个变量（其实感觉上更像别名）
    ```rust
    #[derive(Debug)]
    enum Direction {
      East,
      West,
      North,
      South,
    }

    fn main() {
      let dire = Direction::South;
      match dire {
        Direction::East => println!("East"),
        other => println!("other direction: {:?}", other),
      };
    }
    ```
    然而，在某些场景中，其实只关心**某一个值是否存在**，`match`就会显得过于繁琐
+ `if let`匹配：有时会遇到只有一个模式的值需要被处理，在`match`中便会如此
  ```rust
  let v = Some(3u8);
  match v {
    Some(3) => println!("three"),
    _ => (),
  }
  ```
  像是只处理`Some(3)`，而不处理其它`Some<u8>`或者`None`，可以使用`if let`的方式来实现：
  ```rust
  if let Some(3) = v {  // 专门匹配 Some(3)
    println!("three");
  }
  ```
+ `matches!`宏：这个宏可以将一个表达式与模式进行匹配，然后返回匹配的结果`true`或者`false`
  + 一个例子：有一个动态数组，存在以下枚举
    ```rust
    enum MyEnum {
      Foo,
      Bar
    }
    
    fn main() {
      let v = vec![MyEnum::Foo, MyEnum::Bar, MyEnum::Foo];
    }
    ```
    现在需要对`v`进行过滤，只保留类型`MyEnum::Foo`的元素
    ```rust
    v.iter().filter(|x| matches!(x, MyEnum::Foo));
    ```
    不能使用`x == MyEnum::Foo`，因为迭代器变量无法与一个枚举变量直接比较
    还有更多使用的例子：
    ```rust
    let foo = 'f';
    assert!(matches!(foo, 'A'..='Z' | 'a'..='z'));
    
    let bar = Some(4);
    assert!(matchers!(bar, Some(x) if x > 2));
    ```
+ 变量遮蔽：上述的两种方法中均隐式声明了新的变量（在代码块中），这就意味着会发生变量遮蔽
  ```rust
  fn main() {
    let age = Some(30);
    if let Some(age) = age {  // 这里的新变量age被遮蔽为了30
      println!("匹配出的年龄为 {}", age);
    }
    // 这里的age仍然是Some(i32)类型，因为超出了age:i32的遮蔽范围
  }
  ```
  同样，在`match`中也是如此
  ```rust
  fn main() {
    let age = Some(30);
    println!("在匹配前，age是{:?}",age);
    match age {
      Some(age) =>  println!("匹配出来的age是{}",age),  // 匹配到i32的age
      _ => ()
    }
    println!("在匹配后，age是{:?}",age);
  }
  ```
<br>

###### 解构 Option
~别忘了`Some(T)`与`None`都是`Option<T>`中的成员~
+ 一个例子：
  ```rust
  fn plus_one(x: Option<i32>) -> Option<i32> {
    match x {
      None => None,
      Some(i) => Some(i + 1),
    }
  }
  ```
  有几个值得注意的地方：
  + 隐式绑定`i32`
  + 通常的`T`都会对应一个`None`
<br>

###### 模式适用场景
+ 模式：这是 Rust 中的特殊语法，它用来匹配类型中的结构和数据，它往往和`match`表达式联用，以实现强大的模式匹配能力。一般由以下内容组合而成：
  + 字面值
  + 解构的数组、枚举、结构体或者元组
  + 变量
  + 通配符
  + 占位符
+ **所有可能用到模式的地方**
  + `match`分支：每个分支就是一个**模式**
    ```rust
    match VALUE {
      PATERN => EXPRESSION,
      PATERN => EXPRESSION,
      _ => EXPRESSION,
    }
    ```
  + `if let`：往往用于匹配一个模式，而忽略剩下的所有模式的场景：
    ```rust
    if let PATERN = SOME_VALUE {
      ...
    }
    ```
  + `while let`条件循环：只要模式匹配就一直进行`while`循环
    ```rust
    let mut st = Vec::new();
    
    for i in 1..4 {
      st.push(i);
    }
    
    while let Some(top) = st.pop() {  // 只要栈顶不为 None 就继续弹出
      println!("{}", top);
    }
    ```
  + `for`循环：下述的`.enumerate()`按照`(<index>, <value>)`来进行遍历
    ```rust
    let v = vec!['a', 'b', 'c'];
    
    for (i, val) in v.iter().enumerate() {
      println!("{} is at index {}", val, i);
    }
    ```
  + `let`语句：实际上`let x = 5;`也是一种模式匹配，内容就是**将匹配的值绑定到变量x上**。所以，在 Rust 中，变量名也是一种模式
    + 因此模式匹配要求两边的类型必须相同，否则就会报错：
      ```rust
      let (x, y) = (1, 2, 3); // 双边不匹配，会报错
      ```
  + 函数参数：实际上也是模式匹配的一种，你还可以在参数中匹配元组：
    ```rust
    fn print_coordinates(&(x, y): &(i32, i32)) {
      println!("Current location: ({}, {})", x, y);
    }

    fn main() {
      let point = (3, 5);
      print_coordinates(&point);
    }
    ```
    `&(3, 5)`会匹配模式`&(x, y)`，
  + 再看`let`与`if let`：上文说到`let`实际上也是一种模式匹配，但是面临以下语句存在不足
    ```rust
    let Some(x) = some_option_value;
    ```
    原因在于右部可能为`None`，而这与`let, for, match`要求全覆盖的原则不符，于是聪明人们就采用`if`来消除这个错误，避免了`None`
    ```rust
    if let Some(x) = some_option_value {
      println!("{}", x);
    }
    ```
    由此达到单模式匹配的效果，之后`let-else`使得原本赋值变为双分支，不过`else`分支必须是发散代码块
    ```rust
    use std::str::FromStr;

    fn get_count_item(s: &str) -> (u64, &str) {
      let mut it = s.split(' ');
      let (Some(count_str), Some(item)) = (it.next(), it.next()) else {
        panic!("Can't segment count item pair: '{s}'");
      };
      let Ok(count) = u64::from_str(count_str) else {
        panic!("Can't parse integer: '{count_str}'");
      };
      // error: `else` clause of `let...else` does not diverge
      // let Ok(count) = u64::from_str(count_str) else { 0 };
      (count, item)
    }

    fn main() {
      assert_eq!(get_count_item("3 chairs"), (3, "chairs"));
    }
    ```
    不过`let-else`带来了一种相当作弊的操作，`let`中的变量可以在`if`分支外使用
    ```rust
    // if let
    if let Some(x) = some_option_value {
      println!("{}", x);
    }

    // let-else
    let Some(x) = some_option_value else { return; }
    println!("{}", x);
    ```
<br>

###### 全模式列表
+ 匹配字面值：
  ```rust
  let x = 1;
  
  match x {
    1 => println!("one"),
    2 => println!("two"),
    _ => println!("anything"),
  }
  ```
+ 匹配命名变量：
  ```rust
  fn main() {
    let x = Some(5);
    let y = 10;
    
    match x {
      Some(50) => println!("Got 50"),
      Some(y) => println!("Matched, y = {:?}", y),  // 匹配出5
      _ => println!("Default case, x = {:?}", x),
    }
    
    println!("at the end: x = {:?}, y = {:?}", x, y);
  }
  ```
  + 这一过程中发生了变量遮蔽
  + 如果不想引入变量遮蔽，可以使用另一变量名而非`y`，或者使用匹配守卫(`match guard`)
+ 单分支多模式：可以使用`|`在一个分支前匹配多个模式
+ 通过序列`..=`匹配值的范围：该语法不仅可以用于循环，还能用于匹配模式
  ```rust
  let x = 5;
  
  match x {
    1..=5 => println!("one through five"),
    _ => println!("something else"),
  }
  ```
  类似，`'a'..='z'`也是正确的模式
+ 解构并分解值：可以使用模式解构结构体、枚举、元组、数组和引用
  + 解构结构体：
    ```rust
    struct Point {
      x: i32,
      y: i32,
    }
    
    fn main() {
      let p = Point { x: 0, y: 7 };
      
      let Point { x: a, y: b } = p;
      assert_eq!(0, a);
      assert_eq!(7, b);
    }
    ```
    这个例子展示了**模式中的变量名不必与结构体中的字段名一致**。不过当两者一致时，也可如此进行模式匹配：
    ```rust
    fn main() {
      let p = Point { x: 0, y: 7 };
      
      let Point { x, y } = p;
      assert_eq!(0, x);
      assert_eq!(7, y);
    }
    ```
    另外，也就可以使用字面值作为结构体模式的一部分进行解构，而不是为所有字段创建变量：
    ```rust
    fn main() {
      let p = Point { x: 0, y: 7 }; // 匹配第二个分支

      match p {
        Point { x, y: 0 } => println!("On the x axis at {}", x),  // 只匹配 y=0 的目标
        Point { x: 0, y } => println!("On the y axis at {}", y),  // 只匹配 x=0 的目标
        Point { x, y } => println!("On neither axis: ({}, {})", x, y),
      }
    }
    ```
  + 解构枚举：
    ```rust
    enum Message {
      Quit,
      Move { x: i32, y: i32 },
      Write(String),
      ChangeColor(i32, i32, i32),
    }

    fn main() {
      let msg = Message::ChangeColor(0, 160, 255);

      match msg {
        Message::Quit => {
          println!("The Quit variant has no data to destructure.")
        }
        Message::Move { x, y } => {
          println!(
            "Move in the x direction {} and in the y direction {}",
            x,
            y
          );
        }
        Message::Write(text) => println!("Text message: {}", text),
        Message::ChangeColor(r, g, b) => {
          println!(
            "Change the color to red {}, green {}, and blue {}",
            r,
            g,
            b
          )
        }
      }
    }
    ```
    模式匹配也需要类型相同；另外没有任何数据的枚举成员，不能进一步解构其值，只能匹配其字面值
  + 解构嵌套的结构体和枚举：`match`也可以匹配嵌套的项
    ```rust
    enum Color {
      Rgb(i32, i32, i32),
      Hsv(i32, i32, i32),
    }

    enum Message {
      Quit,
      Move { x: i32, y: i32 },
      Write(String),
      ChangeColor(Color),
    }

    fn main() {
      let msg = Message::ChangeColor(Color::Hsv(0, 160, 255));

      match msg {
        Message::ChangeColor(Color::Rgb(r, g, b)) => {
          println!(
            "Change the color to red {}, green {}, and blue {}",
            r,
            g,
            b
          )
        }
        Message::ChangeColor(Color::Hsv(h, s, v)) => {
          println!(
            "Change the color to hue {}, saturation {}, and value {}",
            h,
            s,
            v
          )
        }
        _ => ()
      }
    }
    ```
  + 解构结构体与元组：
    ```rust
    struct Point {
      x: i32,
      y: i32,
    }

    let ((feet, inches), Point {x, y}) = ((3, 10), Point { x: 3, y: -10 });
    ```
  + 解构数组：对于数组可以使用类似元组方式解构
    + 定长数组
      ```rust
      let arr: [u16; 2] = [114, 514];
      let [x, y] = arr;
      
      assert_eq!(x, 114);
      assert_eq!(y, 514);
      ```
    + 不定长数组
      ```rust
      let arr: &[u16] = &[114, 514];

      if let [x, ..] = arr {
        assert_eq!(x, &114);
      }

      if let &[.., y] = arr {
        assert_eq!(y, 514);
      }

      let arr: &[u16] = &[];

      assert!(matches!(arr, [..]));
      assert!(!matches!(arr, [x, ..]));
      ```
  + 解构引用：使用模式 `&mut V` 去匹配一个可变引用时，你需要格外小心，因为匹配出来的 `V` 是一个值，而不是可变引用
    ```rust
    fn main() {
      let mut v = String::from("hello,");
      let r = &mut v;

      match r {
        value => value.push_str(" world!") 
      }
    }
    ```
+ 忽略模式中的值：
  + 使用`_`忽略整个值
  + 使用嵌套的`_`忽略部分值：
    ```rust
    let mut setting_value = Some(5);
    let new_setting_value = Some(10);

    match (setting_value, new_setting_value) {
      (Some(_), Some(_)) => {
        println!("Can't overwrite an existing customized value");
      }
      _ => {
        setting_value = new_setting_value;
      }
    }

    println!("setting is {:?}", setting_value);
    ```
    还可以在一个模式中的多处使用下划线来忽略特定值：
    ```rust
    let numbers = (2, 4, 8, 16, 32);

    match numbers {
      (first, _, third, _, fifth) => {
        println!("Some numbers: {}, {}, {}", first, third, fifth)
      },
    }
    ```
  + 使用下划线开头忽略未使用的变量（仍会绑定到变量，而`_`完全不会绑定）
  + 用`..`忽略剩余值：必须要求匹配值是无歧义的
    ```rust
    fn main() {
      let numbers = (2, 4, 8, 16, 32);

      match numbers {
        (.., second, ..) => {   // 会直接报错，因为 second 匹配会有歧义
          println!("Some numbers: {}", second)
        },
      }
    }
    ```
+ 匹配守卫提供的额外条件
  + 匹配守卫：一个位于`match`分支模式后的额外`if`条件，当`if`不成立时，会前往第二分支
    + 一个例子：
      ```rust
      let x = 4;
      let y = false;
      
      match x {
        4 | 5 | 6 if y => println!("yes"),
        _ => println!("no"),
      }
      ```
      第一分支的条件为`(4 | 5 | 6) if y => ...`
+ @ 绑定：
  + `@`允许为一个字段绑定另外一个变量
    ```rust
    enum Message {
      Hello { id: i32 },
    }

    let msg = Message::Hello { id: 5 };

    match msg {
      Message::Hello { id: id_variable @ 3..=7 } => {
        println!("Found an id in range: {}", id_variable) // 将 id 绑定至 id_variable，并判断是否位于 3..=7 内
      },
      Message::Hello { id: 10..=12 } => { // 只能限定 id 范围，而无法使用分支变量
        //println!("{}", id); // 这里会直接报错，因为作用域内没有 id
        println!("Found an id in another range")
      },
      Message::Hello { id } => {
        println!("Found some other id: {}", id)
      },
    }
    ```
  + `@`前方绑定，后方解构(Rust 1.56 新增)：`@`可以在绑定新变量同时，对目标进行解构
    ```rust
    #[derive(Debug)]
    struct Point {
      x: i32,
      y: i32,
    }

    fn main() {
      // 绑定新变量 `p`，同时对 `Point` 进行解构
      let p @ Point {x: px, y: py } = Point {x: 10, y: 23};
      println!("x: {}, y: {}", px, py);
      println!("{:?}", p);


      let point = Point {x: 10, y: 5};
      if let p @ Point {x: 10, y} = point { // p 绑定 point 后，解构判断 x 是否为10
        println!("x is 10 and y is {} in {:?}", y, p);
      } else {
        println!("x was not 10 :(");
      }
    }
    ```
  + `@`新特性(Rust 1.53 新增)：【真的神人语法】
    ```rust
    fn main() {
      match 1 {
        num @ 1 | 2 => {  // 这种模式条件等同为 num @ (1 | 2)，之前 Rust 版本会发生报错
            println!("{}", num);
        }
        _ => {}
      }
    }
    ```
<br>

##### 方法 Method
###### 定义方法
+ Rust 使用`impl`来定义方法，例如：
  ```rust
  struct Circle {
    x: f64,
    y: f64,
    radius: f64,
  }
  
  impl Circle { // 专门定义 Circle 方法
    // new 是 Circle 的关联函数，因为它的第一个参数不是self，且new不是关键字
    // 这种方法往往用于初始化当前结构体的实例
    fn new(x: f64, y: f64, radius: f64) -> Circle {
      Circle {
        x,
        y,
        radius,
      }
    }
    
    // Circle 的方法，&self 表示借用当前的 Circle 结构体
    fn area(&self) -> f64 {
      std::f64::consts::PI * (self.radius * self.radius)
    }
  }
  
  fn main() {
    let cir1 = Circle { x: 3.0, y: 4.0, radius: 5.0 };
    
    println!(
      "The area of the circle is {} square pixels.",
      cir1.area()
    );
  }
  ```
+ `self`、`&self`和`&mut self`：
  + 在`area`的签名中，使用`&self`替代了`circle: &Circle`，`&self`其实是`self: &Self`的简写
    + 在一个`impl`块内，`Self`指代被实现方法的结构体类型，`self`指代此类型实例
    + 这里还可以注意到参数中的`self`相关内容通常没有类型值，实际上`&self`是 `self: &Self`的缩写或者说语法糖
  + `self`依然有所有权的概念：
    + `self`表示`Circle`的所有权转移到该方法中，这种形式用的比较少
      + 这种使用方式往往用于把当前的对象转成另外一个对象时使用
    + `&self`表示该方法对`Circle`的不可变借用
    + `&mut self`表示可变借用
  + 使用方法代替函数有以下好处：
    + 不用在函数签名中重复书写`self`对应的类型
    + 代码的组织性和内聚性更强，对于代码维护和阅读来说，好处巨大
+ 方法名跟结构体字段名相同
  ```rust
  impl Circle {
    fn radius(&self) -> bool {
      self.radius > 0
    }
  }
  
  fn main() {
    let cir1 = Circle {
      x: 3.0,
      y: 4.0,
      radius: 5.0,
    };
    
    if cir1.radius() {
      println!("The circle has a nonzero radius; it is {}", cir1.radius);
    }
  }
  ```
  一般来说，方法跟字段同名，往往适用于实现`getter`访问器，例如：
  ```rust
  mod my {
    pub struct Rectangle {
      width: u32,
      pub height: u32,  // 公用字段
    }
    
    impl Rectangle {
      pub fn new(width: u32, height: u32) -> self {
        Rectangle { width, height }
      }
      pub fn width(&self) -> u32 {
        return self.width;
      }
      pub fn height(&self) -> u32 {
        return self.height;
      }
    }
  }
  
  fn main() {
    let rect1 = my::Rectangle::new(30, 50);
    
    println!("{}", rect1.width());  // OK
    println!("{}", rect1.height()); // OK
    // println!("{}", rect1.width); // Error，这里的 width 是私有字段
    println!("{}", rect1.height); //OK
  }
  ```
+ `->`运算符问题：
  + 在 C/C++ 语言中，有两种不同的运算符来调用方法：`.`直接在对象上调用方法，而`->`在一个对象的指针上调用方法，这时需要先解引用指针。【如果`object`是一个指针，那么`object->something()`和`(*object).something()`是一样的】
  + Rust 中没有一个与`->`等效的运算符；相反，Rust 有一个**自动引用和解引用**的功能。使得这样的代码等价：
    ```rust
    p1.distance(&p2);     // 自动添加了`&`符号
    (&p1).distance(&p2);
    ```
    由于`&self`、`&mut self`以及`self`对应了不同所有权的使用等级，因此方法便有了一个明确的接收者，而不存在`引用`与`实例`的争端
<br>

###### 带有多个参数的方法
+ 方法和函数一样，可以使用多个参数：
  ```rust
  impl Rectangle {
    fn area(&self) -> u32 {
      self.width * self.height
    }

    fn can_hold(&self, other: &Rectangle) -> bool {
      self.width > other.width && self.height > other.height
    }
  }

  fn main() {
    let rect1 = Rectangle { width: 30, height: 50 };
    let rect2 = Rectangle { width: 10, height: 40 };
    let rect3 = Rectangle { width: 60, height: 45 };

    println!("Can rect1 hold rect2? {}", rect1.can_hold(&rect2));
    println!("Can rect1 hold rect3? {}", rect1.can_hold(&rect3));
  }
  ```
<br>

###### 关联函数
+ Rust 中可以通过**关联函数**来定义结构体的构造方法（在`impl`定义且没有`self`的函数）
  + 由于没有`self`，不能用`obj.something()`的形式调用，也因此它是一个函数而非方法
  ```rust
  impl Rectangle {
    // Rust 习惯使用`new`来作为构造器的名称（出于设计上的考虑，特地没有用`new`作为关键字）
    fn new(w: u32, h: u32) -> Rectangle {
      Rectangle { width: w, height: h }
    }
  }
  ```
  由于是函数，所以不能用`.`来调用，需要用`::`来调用（位于结构体的命名空间中，通过`::`关联函数和模块创建的命名空间）
<br>

###### 多个`impl`定义
+ Rust 允许为一个结构体定义多个`impl`块（提高了灵活性和代码组织性），相关的方法便可以组织在同一`impl`块中
  ```rust
  impl Rectangle {
    fn area(&self) -> u32 {
      self.width * self.height
    }
  }
  
  impl Rectangle {
    fn can_hold(&self, other: &Rectangle) -> bool {
      self.width > other.width && self.height > other.height
    }
  }
  ```
<br>

###### 枚举的方法
+ Rust 中的`enum`比起其它语言的，真的过于强大了，它被允许容纳方法
  ```rust
  #![allow(unused)]
  enum Message {
    Quit,
    Move { x: i32, y: i32 },
    Write(String),
    ChangeColor(i32, i32, i32),
  }
  
  impl Message {
    fn call(&self) {
      // 这里定义方法体
    }
  }
  
  fn main() {
    let m = Message::Write(String::from("hello"));
    m.call();
  }
  ```
<br>

###### 一个结构的示例
+ 文件位于`./Note/rust_note/basis/test/method_test`
<br>

##### 泛型和特征
###### 泛型 Generics
+ 泛型详解：Rust 常使用`T`作为泛型参数（可以自选，名称越短越少）
  + 使用泛型参数，有一个先决条件，必须声明`<T>`：
    ```rust
    fn largest<T>(list: &[T]) -> T { ... }
    ```
    + 不过，需要注意一些操作并非所有类型都可以进行（比如说比较、相加等），因此最好添加**类型约束**：使用`std::cmp::PartialOrd`特征 (`Trait`) 对`T`限制，该特征的目的就是让**类型实现可比较的功能**
    + 同样地，不是所有`T`类型都进行相加操作，所以需要进行限制：
    ```rust
    fn add<T: std::ops::Add<Output = T>>(a: T, b: T) -> T {
      a + b
    }
    ```
  + 显式地指定泛型的类型参数：有时候，编译器无法推断目标的泛型参数
    ```rust
    use std::fmt::Display;
    
    fn create_and_print<T>() where T: From<i32> + Display {
      let a: T = 100.into();  // 创建子类型为 T 的变量 a，初值由 100 转换而来
      println!("a is: {}", a);
    }
    
    fn main() {
      create_and_print(); // 无法从这里推断 T 的类型
      create_and_print::<i64>();  // 显式指定类型
    }
    ```
  + 二者混用的例子：
    ```rust
    struct A;          // 具体的类型 `A`.
    struct S(A);       // 具体的类型 `S`.
    struct SGen<T>(T); // 泛型 `SGen`.

    fn reg_fn(_s: S) {}

    fn gen_spec_t(_s: SGen<A>) {}

    fn gen_spec_i32(_s: SGen<i32>) {}

    fn generic<T>(_s: SGen<T>) {}

    fn main() {
      // 使用非泛型函数
      reg_fn(S(A{}));          // 具体的类型
      gen_spec_t(SGen(A{}));   // 隐式地指定类型参数  `A`.
      gen_spec_i32(SGen(32)); // 隐式地指定类型参数`i32`.

      // 显式地指定类型参数 `char`
      generic::<char>(SGen::<char>('a'));

      // 隐式地指定类型参数 `char`.
      generic(SGen('a'));
    }
    ```
+ 结构体中使用泛型：结构体的字段类型也可以用泛型来定义
  ```rust
  struct Point<T> {
    x: T,
    y: T,
  }
  
  fn main() {
    let integer = Point { x: 5, y: 10 };
    let float = Point { x: 1.0, y: 4.0 };
  }
  ```
  这里有两点需要特别注意的：
  + **提前声明**：提前声明`<T>`
  + **x 和 y 是相同的类型**，多个类型可以这样`<T,U,X,...>`
+ 枚举中使用泛型：
  + 一个经典的泛型例子：`Option<T>`就是使用了泛型的`enum`
    ```rust
    enum Option<T> {
      Some(T),
      None,
    }
    ```
    这一枚举类型关注值的有效性
  + 另一个重要的泛型例子：`Result<T, E>`
    ```rust
    enum Result<T, E> {
      Ok(T),
      Err(E),
    }
    ```
    这一枚举类型关注值的正确性。如果函数正常运行，则返回`Ok(T)`类型，否则返回`Err(T)`
+ 方法中使用泛型：
  + 基本使用：
    ```rust
    struct Point<T> {
      x: T,
      y: T,
    }
    
    impl<T> Point<T> {
      fn x(&self) -> &T {
        &self.x
      }
    }
    
    fn main() {
      let p = Point { x: 5, y: 10 };
      
      println!("p.x = {}", p.x());
    }
    ```
    注意几点：
    + `impl<T>`需要提前声明，才能使用在`Point<T>`它
    + 这里的`Point<T>`整体是一个类型，而非`Point`
    + 除了`impl<T>`内的泛型外，仍然可以在方法中单独添加额外的泛型（两者不冲突）
    ```rust
    struct Point<T, U> {
      x: T,
      y: U,
    }

    impl<T, U> Point<T, U> {
      // 实现 mixup，不要修改其它代码！
      fn mixup<V, W>(self, p: Point<V, W>) -> Point<T, W> {
        Point { x: self.x, y: p.y }
      }
    }

    fn main() {
      let p1 = Point { x: 5, y: 10 };
      let p2 = Point { x: "Hello", y: '中'};

      let p3 = p1.mixup(p2);

      assert_eq!(p3.x, 5);
      assert_eq!(p3.y, '中');
    }
    ```
  + 为具体的泛型类型实现方法：对于`Point<T>`类型，不仅能定义基于`T`方法，还能针对特定的具体类型，为方法定义：
    ```rust
    impl Point<f32> {
      fn distance_from_origin(&self) -> f32 {
        (self.x.powi(2) + self.y.powi(2)).sqrt()
      }
    }
    ```
+ `const`泛型 (Rust 1.51 添加)：之前的泛型中，所有的泛型都是为了抽象不同的类型，而这里便出现了针对值的泛型：
  + 基本使用：
    ```rust
    fn display_array(arr: [i32; 3]) {
      println!("{:?}", arr);
    }
    
    fn main() {
      let arr: [i32; 3] = [1, 2, 3];
      display_array(arr);
      
      let arr: [i32; 2] = [1, 2];
      display_array(arr);
    }
    ```
    上面是一段错误代码，通过以下步骤更正
    + 首先，改造参数类型，变为数组切片，以此整合不同长度的数组
    + 之后，变换类型的`i32`，以匹配各种数组元素类型
    ```rust
    fn display_array<T: syd::format::Debug>(arr: &[T]) {
      println!("{:?}", arr);
    }
    
    fn main() {
      let arr: [i32; 3] = [1, 2, 3];
      display_array(arr);
      
      let arr: [i32; 2] = [1, 2];
      display_array(arr);
    }
    ```
    不过，这样的改动也只是缓和了`矛盾`，要解决`根本矛盾`，就得匹配数组的长度，这就用到了“针对值的泛型”(`const`)
    ```rust
    fn display_array<T: syd::format::Debug, const N: usize>(arr: [T; N]) {
      println!("{:?}", arr);
    }
    
    fn main() {
      let arr: [i32; 3] = [1, 2, 3];
      display_array(arr);
      
      let arr: [i32; 2] = [1, 2];
      display_array(arr);
    }
    ```
  + `const`泛型表达式：假设代码需要在内存较小的平台上工作，因此需要限制函数参数占用的内存大小，此时就可以使用`const`泛型表达式来实现：
    ```rust
    // 目前只能在nightly版本下使用
    #![allow(incomplete_features)]
    #![feature(generics_const_exprs)]
    
    fn something<T>(val: T)  // 下面的`768`就是一个 const 表达式，可供替换
    where Assert<{ core::mem::size_of::<T>() < 768 }>: IsTrue, {
      ...
    }
    
    pub enum Assert<const CHECK: bool> {
      ...
    }
    
    pub trait IsTrue {
      ...
    }
    
    impl IsTrue for Assert<true> {
      ...
    }
    
    fn main() {
      something([0u8; 0]);  // ok
      something([0u8; 512]);  // ok
      something([0u8; 1024]); // 编译错误，长度为1024字节，超768字节的参数长度限制
    }
    ```
  + `const fn`：常量函数，允许在编译器对函数进行求值，从而实现更高效、更灵活的代码设计
    + **现实意义**：
      + 通常条件下，函数是运行时被调用和执行的。然而，在某些场景中，为了提高运行时的性能或满足某些编译期的约束条件。例如，定义数组长度、计算常量值等
      + 有了`const fn`，就可以在编译期执行这些函数，从而将计算结果直接嵌入生成的代码中，这不仅提高了运行时的性能，也使代码更加简洁和安全
    + 基本用法：
      ```rust
      const fn add(a: usize, b: usize) -> usize {
        a + b
      }
      
      const RESULT: usize = add(5, 10);
      
      fn main() {
        println!("The result is {}", RESAULT);
      }
      ```
    + `const fm`的限制：
      + 虽然`const fn`提供了很多便利，但是由于其在编译期执行，以确保函数能在编译期被安全地求值，因此有一些限制，例如，不可将随机数生成器写成`const fn`
      + 无论在编译时还是运行时调用`const fn`，它们的结果总是相同，即使多次调用也是如此。唯一的例外是，如果你在极端情况下进行复杂的浮点操作，你可能会得到（非常轻微的）不同结果。因此，不建议使数组长度`(arr.len())`和`Enum`判别式依赖于浮点计算
    + 结合`const fn`与`const`泛型：二者的结合，可以实现更加灵活和高效的代码设计。例如，创建一个固定大小的缓冲区结构，其中缓冲区大小由编译期计算确定：
      ```rust
      struct Buffer<const N: usize> {
        data: [u8; N],
      }
      
      const fn compute_buffer_size(factor: usize) -> usize {
        factor * 1024
      }
      
      fn main() {
        const SIZE: usize = compute_buffer_size(4);
        let buffer = Buffer::<SIZE> {
          data:[0; SIZE];
        };
        println!("Buffer size: {} bytes", buffer.date.len());
      }
      ```
+ 泛型的性能：在 Rust 中泛型是零成本的抽象，意味着你在使用泛型时，完全不用担心性能上的问题
  + 任何选择都是权衡得失的，既然我们获得了性能上的巨大优势，那么又失去了什么呢？Rust 是在编译期为泛型对应的多个类型，生成各自的代码，因此损失了编译速度和增大了最终生成文件的大小
  + Rust 通过在编译时进行泛型代码的 **单态化(monomorphization)**来保证效率。单态化是一个通过填充编译时使用的具体类型，**将通用代码转换为特定代码**的过程。
  + 编译器所做的工作正好与我们创建泛型函数的步骤相反，**编译器寻找所有泛型代码被调用的位置并针对具体类型生成代码**