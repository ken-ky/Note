#### C/C++ 备忘

##### 概念
+ 常量表达式：
  + 必须是可以在编译阶段被识别的，比如模板的参数/数组大小
  ```c++
  template<int N>
  class fixed_size_list { ... };
  
  fixed_size_list<X> mylist;  // X必须是字面值类型
  int numbers[X];
  ```
<br>

##### 关键字
+ [`inline`关键字](https://c.biancheng.net/view/4tevnqv.html)
  + `inline` 关键字用于建议编译器尝试将函数体内联到每个函数调用的位置。
  + **编译器会在函数调用的位置直接插入函数的代码**，而不是执行常规的函数调用，从而减少函数调用的运行时开销
+ [`final`关键字](https://c.biancheng.net/view/90vn2fi.html)
  + 在虚函数声明或定义的声明符之后用 `final` 防止在派生类中对函数进行进一步覆盖
    ```c++
    class Derived2: public Derived1 {
        virtual void foo() final {}
    };
    ```
  + 在类声明中的类名后用 `final` 防止类被进一步继承
    ```C++
    class Derived4 final: public Derived1 {
        virtual void foo() override {}
    };
    ```
+ [`override`关键字](https://c.biancheng.net/view/90vn2fi.html)
  + 在虚函数的声明或定义中，它可以保证函数确实覆盖了一个基类函数，否则，编译器会报错
    ```C++
    class Base {
    public:
        virtual void foo() {}
        virtual void bar() {}
    };
    
    class Derived: public Base {
    public:
        void foo() override {}  // 成功覆盖基类
        virtual void bar(char const c) override {}  // 不能覆盖，因为基类没有包含这样的虚函数
    };
    ```
+ [`friend`关键字](https://zhuanlan.zhihu.com/p/620730340)
  + 友元函数
    + 友元函数是在当前类以外定义的（不属于当前类的函数也可以在类中声明）【外部定义时也不能添加`friend`】
    + 友元函数可以访问当前类中的所有成员
    + 友元关系是单向的，而且不能传递
    + 声明：
    ```C++
    class Student{
    public:
        Student(char *name, int age, float score);
    public:
        friend void show(Student *pstu); //将show()声明为友元函数
    private:
        char *m_name;
        int m_age;
        float m_score;
    };

    Student::Student(char *name, int age, float score): m_name(name), m_age(age), m_score(score){ }

    //非成员函数
    void show(Student *pstu){
        cout<<pstu->m_name<<"的年龄是 "<<pstu->m_age<<"，成绩是 "<<pstu->m_score<<endl;
    }

    int main(){
        Student stu("小明", 15, 90.6);
        show(&stu); //调用友元函数
        Student *pstu = new Student("李磊", 16, 80.5);
        show(pstu); //调用友元函数

        return 0;
    }
    ```
  + 友元类：将整个类声明为另一个类的友元
    + 代码：
    ```C++
    class Address; //提前声明Address类

    //声明Student类
    class Student{
    public:
        Student(char *name, int age, float score);
    public:
        void show(Address *addr);
    private:
        char *m_name;
        int m_age;
        float m_score;
    };

    //声明Address类
    class Address{
    public:
        Address(char *province, char *city, char *district);
    public:
        //将Student类声明为Address类的友元类
        friend class Student;
    private:
        char *m_province; //省份
        char *m_city; //城市
        char *m_district; //区（市区）
    };

    //实现Student类
    Student::Student(char *name, int age, float score): m_name(name), m_age(age), m_score(score){ }
    void Student::show(Address *addr){
        cout<<m_name<<"的年龄是 "<<m_age<<"，成绩是 "<<m_score<<endl;
        cout<<"家庭住址："<<addr->m_province<<"省"<<addr->m_city<<"市"<<addr->m_district<<"区"<<endl;
    }

    //实现Address类
    Address::Address(char *province, char *city, char *district){
        m_province = province;
        m_city = city;
        m_district = district;
    }

    int main(){
        Student stu("小明", 16, 95.5f);
        Address addr("陕西", "西安", "雁塔");
            stu.show(&addr);
        
        Student *pstu = new Student("李磊", 16, 80.5);
        Address *paddr = new Address("河北", "衡水", "桃城");
            pstu -> show(paddr);

        return 0;
    }
    ```
+ [`explicit`关键字](https://blog.csdn.net/weixin_45031801/article/details/137796214)
  + 用于修饰**只有一个参数的类构造函数**，以表明该构造函数是显式的，而非隐式的
  + 禁止类对象之间的隐式转换，并禁止隐式调用拷贝构造函数
+ [`const`和`constexpr`的区别](https://zhuanlan.zhihu.com/p/20206577)
  + 修饰对象
    + `const`修饰一个对象表示它是常量
    + `constexpr`修饰一个常量表达式【但是`constexpr`不是修饰常量表达式唯一途径】
  + 修饰函数
    + `const`只能用于非静态成员函数而不是所有函数，保证成员函数不修改任何非静态数据
    + `constexpr`可以用于含参和无参函数。适用于常量表达式，只有在以下情况，编译器才会接受`constexpr`函数：
      + 函数体足够简单，除了`typedef`和静态元素，只允许有`return`语句
      + 参数和返回值必须是字面值类型
<br>

##### 模板类编程
+ 参考：
  + [雾里看花：真正意义上的理解 C++ 模板](https://zhuanlan.zhihu.com/p/655902377)
<br>

###### Code Gerneration（代码泛型）
+ 泛型 (Generic) 编程，也就是为不同类型编写相同的代码，实现代码复用。在加入模板之前，只能通过宏来模拟泛型。一个例子：
  ```C
  #define add(T) _ADD_IMPL_##T  // 设定宏参数以及替换部分
  
  #define ADD_IMPL(T)     \     // 设定替换部分的函数体
    T add(T)(T a, T b) {  \
      return a + b;       \
    }
  
  // 使用宏定义，以声明两个不同类型的函数
  ADD_IMPL(int);
  ADD_IMPL(float);
  
  int main() {
    add(int)(1, 2);
    add(float)(1.0f, 2.0f);
  }
  ```
  + 原理实际上就是，将普通函数中的类型替换为宏参数`T`，之后使用宏定义替换后，便能声明此类型函数（可以认为是一种**实例化**）
  + 具体来说，用宏来实现泛型主要有几个缺点：
    + 代码可读性差，宏的拼接和代码逻辑耦合，不容易阅读报错信息
    + 难以调试，断点只能设置到宏展开的位置，而不是宏定义内部
    + 需要显式写出类型参数，参数较多时，会显得十分冗长
    + 必须手动声明实例化的函数定义，
  + 这些内容都被模板解决了
  ```C++
  template<typename T>
  T add(T a, T b) {
    return a + b;
  }
  
  template int add<>(int, int); // 显式实例化（可选）
  
  int main() {
    add(1, 2);        // 自动检测类型
    add(1.0f, 2.0f);  // 隐式实例化
    add<float>(1, 2); // 显式指定 T
  }
  ```
  + 模板的优点在于：
    + 模板就是占位符，无需字符拼接，与普通代码别无二致
    + 报错和调试信息都会直接指向模板定义位置，而不是模板实例化的位置
    + 支持模板参数自动推导，不需要显式写出类型参数，不过也支持显式指定类型参数
    + 支持**隐式实例化 (implicit instantiation)**【编译器自动实例化使用到的函数】，同时也支持**显式实例化 (explicit instantiation)**【手动实例化】
  + 除此之外，还有诸如**偏特化 (partial specialization)**、**全特化 (full specialization)**、**可变模板参数 (variadic template)**、**变量模板 (variable template)** 等等一系列特性，这些仅凭宏都是做不到的。正是由于模板的出现，才使用 STL 这样的泛型库的实现成为可能
+ `Table Gen`：上面的泛型，可以看作模板最直接的用法，基于它们乐意有一些更高级的代码生成：
  > 例如：在编译期生成一个确定的表以供运行期查询。标准库中`std::visit`的实现就利用了这种技巧，下面是一个简单的模拟：
  ```C++
  template<typename T, typename Variant, typename Callback>
  void wrapper(Variant& variant, Callback& callback) {
    callback(std::get<T>(variant));
    // 安全地自variant获取T类型的值，并调用callback()函数
  }
  
  template<typename... Ts, typename Callback>
  void visit(std::variant<Ts...>& variant, Callback&& callback) {
    using Variant = std::variant<Ts...>;  // 使用对应Ts...集合对应的类型
    constexpr static std::array table = { &wrapper<Ts, Variant, Callback>... }; // 转换为函数指针数组
    table[Variant.index()](variant, callback);  // 通过迭代器匿名运行对应类型函数
  }
  
  int main() {
    auto callback = [](auto& value) { std::cout << value << std::endl; };
    
    std::variant<int, float, std::string> variant = 42;
    visit(variant, callback);
    
    variant = 3.14f;
    visit(variant, callback);
    
    variant = "Hello, world!";
    visit(variant, callback);
    
    return 0;
  }
  ```
  + 尽管`variant`中储存的元素类型在运行时才能确定，不过可能取值的类型集合在编译期便可以确定，所以用`callback`给集合中每一个可能的类型都实例化一个对应的`wrapper`函数，并且存到一个数组里面。在运行时直接用`variant`的`index`访问数组里面对应的成员即可完成调用
  + 使用 C++17 加入的**折叠表达式 (folding expression)**，另一种实现：
  ```C++
  template<typename... Ts, typename Callback>
  void visit(std::variant<Ts...>& variant, Callback&& callback) {
    auto foreach = []<typename T>(std::variant<Ts...>& variant, Callback& callback) {
      if(auto value = std::get_if<T>(&variant)) {
        callback(*value);
        return true;
      }
      return false;
    };
    (foreach.template operator()<Ts>(variant, callback) || ...);
  }
  ```
<br>

###### 备忘
+ 结构外成员函数示例：
  ```cpp
  template<typename T> struct Exam {
    ...
    Exam();
    void func();
    ...
  };
  
  // 结构外的成员函数定义
  template<typename T> Exam<T>::Exam() {
    // 相关构造定义
    ...
  }
  
  template<typename T> void Exam<T>::func() {
    // 函数内容
    ...
  }
  ```
<br>

##### 设计模式
+ 单例模式：一个类只有一个实例，且该类能自行创建这个实例的一种模式
  + 优点：
    1. 避免循环应用：避免了内存泄漏
    2. 访问控制：可以访问对象，但是不会延长对象的生命周期
    3. 可以在单例对象不被使用时，自动释放对象
+ 工厂模式：用工厂方法代替`new`操作，把对象创建逻辑集中管理
  + 以`shared_ptr`为例：
    ```c++
    template<class T, class... Args>    // C++可变参数模板
    typename boost::detail::sp_if_not_array<T>::type    // 模板元计算类型
    make_shared( Args && ... args );    // C++的右值引用
    ```
+ 桥接模式：一种结构型设计模式，将抽象与实现分离，让它们可以独立变化
  + 通过组合而非继承，把两个可变维度解耦，避免类爆炸