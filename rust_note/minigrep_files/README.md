### 实现基本功能
+ 对于一个文件查找命令而言，首先要指定文件和待查找字符串
+ 用户会从命令行给出输出，之后需要在程序内读取
<br>

#### 接收命令行参数
+ 命令的样例：
	```sh
	$ cargo run -- searchstring example-filename.txt
	```
	`--`告诉`cargo`之后的参数需要传递到程序中使用
+ 捕获参数：
	```rust
	use std::env;

	fn main() {
		let args: Vec<String> = env::args().collect();
		dbg!(args);
	}
	```
	生成了以下结果：
	```sh
	[src/main.rs:5:5] args = [
		"target/debug/minigrep",
		"searchstring",
		"exp_file.txt",
	]
	```
<br>

#### 文件读取
+ 通过`std::fs`可以进行文件相关操作：
  ```rust
  use std::fs;
  
  fn main() {
	...
	
	let contents = fs::read_to_str(file_path)
		.expect("Should have been able to read the file.")
	println!("With text:\n{contents}");
  }
  ```
  这里需要注意，将要处理的文件放置于项目根目录
<br>

#### 分离`main`函数
+ 多文件方案：处理庞大的`main`函数
  + 将程序分割为`main.rs`和`lib.rs`，并将程序的逻辑代码移动到后者内
  + 命令行解析属于较基础的功能，严格来说并非逻辑代码的一部分，因此还可以放在`main.rs`中
+ `main`函数应包含的功能：
  + 解析命令行参数
  + 初始化其它配置
  + 调用`lib.rs`中的`run`函数，以启动逻辑代码的运行
  + 如果`run`返回一个错误，需要对该错误进行处理
<br>