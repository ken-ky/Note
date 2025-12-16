// use std::clone;
use std::env;
use std::error::Error;
use std::fs;
use std::process;

struct Config {
    query: String,
    file_path: String,
}

impl Config {
    fn _new(args: &[String]) -> Config {
        // 需要进行错误处理
        if args.len() < 3 {
            panic!("not enough arguments"); // 这里直接中断报错，但是仍然不大合适
        }

        Config {
            query: args[1].clone(),
            file_path: args[2].clone(),
        }
    }

    fn build(args: &[String]) -> Result<Config, &'static str> {
        if args.len() < 3 {
            // 进行报错，设置错误信息`&static str`，拥有`'static`
            return Err("not enough arguments");
        }

        let query = args[1].clone();
        let file_path = args[2].clone();

        Ok(Config { query, file_path })
    }
}

fn run(config: Config) -> Result<(), Box<dyn Error>> {
    let contents = fs::read_to_string(config.file_path)?;

    println!("With text:\n{contents}");
    Ok(())
}

fn main() {
    let args: Vec<String> = env::args().collect();
    // dbg!(args);

    let config = Config::build(&args).unwrap_or_else(|err| {
        println!("Problem parsing arguments: {err}");
        process::exit(1);
    }); // 如果`Result`是`Ok`，那该方法就如同`unwrap`解绑，否则就进行后面的函数部分

    println!("Searching for {}", config.query);
    println!("In file {}\n", config.file_path);

    // 读取文件
    run(config);
}
