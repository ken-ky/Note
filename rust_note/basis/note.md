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
  + 枚举类型：这个类型包含了所有可能的枚举成员，而枚举值是该类型中的具体某个成员的实例
  