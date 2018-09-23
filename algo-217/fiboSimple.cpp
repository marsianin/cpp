#include <cassert>
#include <iostream>

class Fibonacci final {
public:
    static int get(int n) {
        assert(n >= 0);

        if (n == 1 || n == 2) {
            return 1;
        }

        int* fiboArray = new int[n];
        fiboArray[0] = 1;
        fiboArray[1] = 1;

        for (int i = 2; i < n; i++) {
            fiboArray[i] = fiboArray[i-1] + fiboArray[i-2];
        }

        n = fiboArray[n-1];

        delete[] fiboArray;

        return n;
    }
};

int main(void) {
    int n;
    std::cin >> n;
    std::cout << Fibonacci::get(n) << std::endl;
    return 0;
}