#pragma once
#include <string>

class BigInt {
  public:
    ~BigInt() = default;
    BigInt(const std::string &data);

    BigInt operator+(const BigInt &b);
    BigInt &operator=(const BigInt &b);

    friend std::ostream &operator<<(std::ostream &output, const BigInt &a);
    friend std::istream &operator>>(std::istream &input, BigInt &a);

    friend class expression;

  private:
    std::string data;
    BigInt() = default;
};