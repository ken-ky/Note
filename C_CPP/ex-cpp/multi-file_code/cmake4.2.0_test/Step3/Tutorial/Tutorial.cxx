// A simple program that computes the square root of a number

// TODO3: Include <format>
#include <fmt/core.h>

#include <iostream>
#include <string>

namespace std {
template <typename... Args>
inline auto format(Args &&... args)
    -> decltype(fmt::v6::format(std::forward<Args>(args)...)) {
    return fmt::v6::format(std::forward<Args>(args)...);
}
} // namespace std

#include <MathFunctions.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        // TODO4: Convert the print to use std::format
        // std::cout << "Usage: " << argv[0] << " number" << std::endl;
        std::cout << std::format("Usage: {} number\n", argv[0]);
        return 1;
    }

    // convert input to double
    double const inputValue = std::stod(argv[1]);

    // calculate square root
    double const outputValue = mathfunctions::sqrt(inputValue);
    // TODO5: Convert the print to use std::format
    // std::cout << "The square root of " << inputValue << " is " << outputValue
    //           << std::endl;
    std::cout << std::format("The square root of {} is {}\n", inputValue,
                             outputValue);
}
