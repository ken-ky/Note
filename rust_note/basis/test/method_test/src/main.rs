/* 矩形相关定义 */
struct Point {
    x: f64,
    y: f64,
}

impl Point {
    fn init() -> Point {
        Point { x: 0.0, y: 0.0 }
    }

    fn new(x: f64, y: f64) -> Point {
        Point { x: x, y: y }
    }
}

struct Rectangle {
    p1: Point,
    p2: Point,
}

impl Rectangle {
    fn area(&self) -> f64 {
        let Point { x: x1, y: y1 } = self.p1;
        let Point { x: x2, y: y2 } = self.p2;

        (x1 - x2).abs() * (y1 - y2).abs()
    }

    fn perimeter(&self) -> f64 {
        let Point { x: x1, y: y1 } = self.p1;
        let Point { x: x2, y: y2 } = self.p2;

        2.0 * ((x1 - x2).abs() + (y1 - y2).abs())
    }

    fn translate(&mut self, x: f64, y: f64) {
        self.p1.x += x;
        self.p1.y += y;
        self.p2.x += x;
        self.p2.y += y;
    }
}

/* Pair<i32, i32> 分配在堆上的数对 */
struct Pair(Box<i32>, Box<i32>);

impl Pair {
    fn new(x: i32, y: i32) -> Pair {
        Pair(Box::new(x), Box::new(y))
    }

    fn destroy(self) {
        let Pair(_x, _y) = self;
        // 结束函数时会自动销毁 self 中的内容
        println!("Pair({}, {}) has destroyed!", _x, _y);
    }
}

fn main() {
    let rectangle = Rectangle {
        // 关联函数的调用不是通过点操作符，而是使用 `::`
        p1: Point::init(),
        p2: Point::new(3.0, 4.0),
    };

    // 方法才是通过点操作符调用
    // 注意，这里的方法需要的是 `&self` 但是我们并没有使用 `(&rectangle).perimeter()` 来调用，原因在于：
    // 编译器会帮我们自动取引用
    //  `rectangle.perimeter()` === `Rectangle::perimeter(&rectangle)`
    println!("Rectangle perimeter: {}", rectangle.perimeter());
    println!("Rectangle area: {}", rectangle.area());

    let mut square = Rectangle {
        p1: Point::init(),
        p2: Point::new(1.0, 1.0),
    };

    // 错误！`rectangle` 是不可变的，但是这个方法要求一个可变的对象
    //rectangle.translate(1.0, 0.0);
    // TODO ^ 试着反注释此行，看看会发生什么

    // 可以！可变对象可以调用可变的方法
    square.translate(1.0, 1.0);

    let pair = Pair::new(1, 2);

    pair.destroy();
}
