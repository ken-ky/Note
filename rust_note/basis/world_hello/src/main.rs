#[allow(dead_code)] // 使得函数不被调用也不会产生警告
fn greet_world() {
    let southern_germany = "Grüß Gott!";
    let chinese = "世界，你好";
    let english = "World, hello";
    let regions = [southern_germany, chinese, english];
    for region in regions.iter() {
        println!("{}", &region);
    }
}

fn test() {
    let penguin_data = "\
    common name, length (cm)
    Little penguin,33
    Yellow-eyed penguin,65
    Fiordland penguin,60
    Invalid,data
    ";

    let records = penguin_data.lines();

    for (i, record) in records.enumerate() {
        if i == 0 || (record.trim().len() == 0) {
            continue;
        }

        // 声明一个 fields 变量，类型是 Vec
        // Vec 是 vector 的缩写，是一个可变长度的序列类型（动态数组）
        // <_> 表示 Vec 中的元素类型由编译器自行推断
        let fields: Vec<_> = record.split(',').map(|field| field.trim()).collect();
        if cfg!(debug_assertions) {
            // 输出到标准错误输出
            eprintln!("debug: {:?} -> {:?}", record, fields);
        }

        // 1. 尝试 fields[1] 的值转换为 f32 类型的浮点数，若成功，则把 f32 值赋给 length 变量
        // 2. if let 是一个匹配表达式，用来从右值中匹配 length 的值：
        //  1) 当右侧表达式执行成功，则会返回一个 OK(f32) 的类型；若失败，则会返回一个 Err(e) 类型
        //  2）同时 if let 还会做一次解构匹配，通过 OK(length) 去匹配右边的 OK(f32)，最终把相应的 f32 赋值给 length
        let name = fields[0];
        if let Ok(length) = fields[1].parse::<f32>() {
            println!("{}, {}cm", name, length);
        }
    }
}

fn main() {
    test();
}
