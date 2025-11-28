#include "expression.hpp"
#include <algorithm>
#include <iostream>
#include <vector>

using std::cin;
using std::string;
using std::vector;

// 私有方法
void expression::parse() {
    string num1{}, num2{};
    bool has_got_symbol{false};
    const vector<char> symbol{'+'};
    for (const auto &i : data) {
        if (std::find(symbol.begin(), symbol.end(), i) != symbol.end()) {
            has_got_symbol = true;
            continue;
        }
        if (std::isdigit(i)) {
            if (!has_got_symbol) {
                num1 += i;
            } else {
                num2 += i;
            }
        }
    }
    result = BigInt{num1} + BigInt{num2};
}

// 公有方法
void expression::getInput() {
    std::getline(cin, data);
    parse();
}

BigInt expression::getResult() const { return this->result; }
