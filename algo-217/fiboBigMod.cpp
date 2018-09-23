#include <cassert>
#include <iostream>

/**
 * Дано число 1≤n≤107, необходимо найти последнюю цифру n-го числа Фибоначчи.

 Как мы помним, числа Фибоначчи растут очень быстро, поэтому при их вычислении
 нужно быть аккуратным с переполнением. В данной задаче, впрочем, этой проблемы
 можно избежать, поскольку нас интересует только последняя цифра числа Фибоначчи:
 если 0≤a,b≤9 — последние цифры чисел Fi и Fi+1 соответственно, то (a+b)mod10 —
 последняя цифра числа Fi+2.
 */

class Fibonacci final {
public:
    static int get_last_digit(int n) {
        assert(n >= 1);
        if (n == 1 || n == 2) {
            return 1;
        }

        int f1 = 1;
        int f2 = 1;
        int fN;
        for (int i = 2; i < n; i++) {
            fN = (f1 + f2)%10;
            f1 = f2;
            f2 = fN;
        }

        return fN;
    }
};

int main(void) {
    int n;
    std::cin >> n;
    std::cout << Fibonacci::get_last_digit(n) << std::endl;
    return 0;
}