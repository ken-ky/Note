#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/case_conv.hpp>
#include <iostream>

using namespace std;
using namespace boost;

int main() {
  string str = "hello world!";
  cout << str << endl;

  to_upper(str); // 转换为大写
  cout << str << endl;

  trim(str); // 使用 trim 函数去除首尾空白字符
  cout << str << endl;

  return 0;
}