from time import sleep, time, localtime


# 类的声明
class Clock(object):
    def __init__(self, second=0, minute=0, hour=0):
        self._second = second
        self._minute = minute
        self._hour = hour

    @classmethod
    def now(cls):
        ctime = localtime(time())
        return cls(ctime.tm_sec, ctime.tm_min, ctime.tm_hour)

    def run(self):
        self._second += 1
        if self._second == 60:
            self._second = 0
            self._minute += 1
            if self._minute == 60:
                self._minute = 0
                self._hour += 1
                if self._hour == 24:
                    self._hour = 0

    def show(self):
        return '%02d:%02d:%02d' % (self._hour, self._minute, self._second)


def main1():
    clock = Clock(58, 59, 23)
    while True:
        print(clock.show())
        sleep(1)
        clock.run()


# 装饰器

class Person(object):
    # __slots__ 绑定
    __slots__ = ('_name', '_age', '_gender')  # 限定Person对象只能绑定_name, _age和_gender属性

    def __init__(self, name, age):
        self._name = name
        self._age = age

    # 访问器 - getter 方法
    @property
    def name(self):
        return self._name

    @property
    def age(self):
        return self._age

    # 修改器 - setter 方法
    @age.setter
    def age(self, age):
        self._age = age

    def play(self):
        if self._age <= 16:
            print('%s正在玩飞行棋.' % self._name)
        else:
            print('%s正在玩斗地主.' % self._name)


# 继承
class Student(Person):
    def __init__(self, name, age, grade):
        super().__init__(name, age)
        self._grade = grade


def main2():
    person = Person('王大锤', 22)
    person.play()
    person._gender = '男'
    # AttributeError: 'Person' object has no attribute '_is_gay'
    # person._is_gay = True


# 静态方法和类方法
from math import sqrt


class Triangle(object):
    __slots__ = ('_a', '_b', '_c')

    def __init__(self, a, b, c):
        self._a, self._b, self._c = a, b, c

    @property
    def info_dis(self):
        return '%d:%d:%d' % (self._a, self._b, self._c)

    @staticmethod
    def is_valid(a, b, c):
        return a + b > c and b + c > a and a + c > b

    def area(self):
        half = self.perimeter() / 2
        return sqrt(half * (half - self._a) *
                    (half - self._b) * (half - self._c))


def main3():
    a, b, c = 3, 4, 5

    # 静态方法可直接使用类名进行调用
    if Triangle.is_valid(a, b, c):
        t = Triangle(a, b, c)
        print(t.info_dis)
        # 也可以通过给类发消息来调用对象方法但是要传入接收消息的对象作为参数
        print(t.area())
        # print(Triangle.area(t))
    else:
        print('无法构成三角形')
