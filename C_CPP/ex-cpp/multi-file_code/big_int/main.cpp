#include "expression.hpp"
#include <iostream>

using std::cin;
using std::cout;
using std::endl;

int main() {
    expression e;
    e.getInput();
    cout << e.getResult() << endl;
}