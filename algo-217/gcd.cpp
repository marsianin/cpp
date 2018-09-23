#include <cassert>
#include <cstdint>
#include <iostream>

template <class Int>
Int gcd(Int a, Int b) {
    Int r;

    if (b > a) {
        std::swap(a, b);
    }

    r = a % b;

    if (r == 0 || b == 1) {
        return b;
    }

    return gcd(b, r);
}

int main(void) {
    std::int32_t a, b;
    std::cin >> a >> b;
    std::cout << gcd(a, b) << std::endl;
    return 0;
}

//a >= b? a %= b : b %= a;