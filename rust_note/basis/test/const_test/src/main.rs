// #![allow(incomplete_features)]
// #![feature(generic_const_exprs)]

// fn check_size<T>(val: T)
// where
//     Assert<{ core::mem::size_of::<T>() < 768 }>: IsTrue,
// {
//     //...
// }

// 修复 main 函数中的错误
fn main() {
    // check_size([0u8; 767]); // 1字节
    // check_size([0i32; 191]); // 4字节
    // check_size(["hello你好"; 47]); // &str 包含了起始位置和终结位置，共16字节
    // check_size([(); 31].map(|_| "hello你好".to_string())); // String 包含三个部分：长度、指针和容量，均8字节
    // check_size(['中'; 191]); // char 为4字节
}

// pub enum Assert<const CHECK: bool> {}

// pub trait IsTrue {}

// impl IsTrue for Assert<true> {}
