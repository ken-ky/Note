#include <iostream>

// TODO6: Include <format>
#include <fmt/core.h>

namespace std {
template <typename... Args>
inline auto format(Args &&... args)
    -> decltype(fmt::v6::format(std::forward<Args>(args)...)) {
    return fmt::v6::format(std::forward<Args>(args)...);
}
} // namespace std

namespace {
// a hack square root calculation using simple operations
double mysqrt(double x) {
    if (x <= 0) {
        return 0;
    }

    double result = x;

    // do ten iterations
    for (int i = 0; i < 10; ++i) {
        if (result <= 0) {
            result = 0.1;
        }
        double delta = x - (result * result);
        result = result + 0.5 * delta / result;

        // TODO7: Convert the print to use std::format
        // std::cout << "Computing sqrt of " << x << " to be " << result
        //           << std::endl;
        std::cout << std::format("Computing sqrt of {} to be {}\n", x, result);
    }
    return result;
}
} // namespace

namespace mathfunctions {
double sqrt(double x) { return mysqrt(x); }
} // namespace mathfunctions
