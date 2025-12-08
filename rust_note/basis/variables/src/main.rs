#[allow(dead_code)]
fn test1() {
    let x = 5;
    println!("The value of x is: {}", x);
    // x = 6;
    println!("The value of x is: {}", x);
}

#[allow(dead_code)]
fn test2() {
    let mut x = 5;
    println!("The value of x is: {}", x);
    x = 6;
    println!("The value of x is: {}", x);
}

#[allow(dead_code)]
fn test3() {
    let _x = 5;
    let y = 10;
    println!("y = {}", y);
}

#[allow(dead_code)]
fn test4() {
    let (a, mut b): (bool, bool) = (true, false);
    println!("a = {:?}, b = {:?}", a, b);

    b = true;
    assert_eq!(a, b);
}

#[allow(dead_code)]
fn test5() {
    struct Struct {
        e: i32,
    }

    let (a, b, c, d, e);
    (a, b) = (1, 2);
    [c, .., d, _] = [1, 2, 3, 4, 5]; // 这里的..表示省略x个变量
    Struct { e, .. } = Struct { e: 5 };

    assert_eq!([1, 2, 1, 4, 5], [a, b, c, d, e])
}

fn main() {
    test5();
}
