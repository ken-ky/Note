#pragma once

#include "big_int.hpp"

class expression {
  public:
    expression() = default;
    ~expression() = default;

    void getInput();
    BigInt getResult() const;

  private:
    void parse();
    std::string data;
    BigInt result;
};