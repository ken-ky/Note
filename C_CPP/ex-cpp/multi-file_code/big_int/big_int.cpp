#include "big_int.hpp"
#include <algorithm>

using std::string;

BigInt::BigInt(const std::string &data) { this->data = data; }

BigInt BigInt::operator+(const BigInt &b) {
    string calc_data = "";
    BigInt &a = *this;
    int aTail = a.data.length() - 1, bTail = b.data.length() - 1;
    int tmp = 0;
    bool carry = false;

    while (true) {
        tmp = ((aTail < 0) ? 0 : (a.data[aTail--] - '0')) +
              ((bTail < 0) ? 0 : (b.data[bTail--] - '0')) + carry;
        if (tmp >= 10) {
            carry = tmp / 10;
            tmp %= 10;
        }

        calc_data += (unsigned char)(tmp + '0');
        if (aTail < 0 && bTail < 0 && !carry) {
            break;
        }
    }
    std::reverse(calc_data.begin(), calc_data.end());
    return BigInt(calc_data);
}

BigInt &BigInt::operator=(const BigInt &b) {
    this->data = std::move(b.data);
    return *this;
}

std::ostream &operator<<(std::ostream &output, const BigInt &a) {
    output << a.data;
    return output;
}

std::istream &operator>>(std::istream &input, BigInt &a) {
    input >> a.data;
    return input;
}