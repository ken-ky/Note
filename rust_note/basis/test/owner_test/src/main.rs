#[allow(dead_code)]
fn test1() -> () {
    {
        let s = String::from("hello");
        takes_ownership(s);
        // println!("s = {}", s);   // s 被move了，所以这里会直接报错

        let x = 5;
        makes_copy(x);
        println!("x = {}", x);
    }

    fn takes_ownership(some_string: String) {
        println!("{}", some_string);
    }

    fn makes_copy(some_integer: i32) {
        println!("{}", some_integer);
    }
}

fn test2() -> () {
    {
        let s = String::from("hello");
        let s1 = takes_ownership(s);
        println!("s1 = {}", s1);
    }

    fn takes_ownership(some_string: String) -> String {
        println!("{}", some_string);
        some_string
    }
}

fn main() {
    // test1();
    test2();
}
