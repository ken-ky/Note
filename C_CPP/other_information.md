#### C/C++ 备忘

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
    + 友元函数是在当前类以外定义的（不属于当前类的函数也可以在类中声明）
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
<br>

##### 模板类编程
+ 参考：
  + [雾里看花：真正意义上的理解 C++ 模板](https://zhuanlan.zhihu.com/p/655902377)
<br>