#include <iostream>

/**
Задача на программирование повышенной сложности: огромное число Фибоначчи по модулю


Даны целые числа 1≤n≤10^18 и 2≤m≤10^5, необходимо найти остаток от деления n-го числа Фибоначчи на m.
 */
class Fibonacci {
    const int initMatrix[2][2] = {{0, 1}, {1, 1}};
    const int eMatrix[2][2] = {{1, 0}, {0, 1}};

    public:
    static int get_remainder(long long n, int m) {
        long long F[2][2] = {{1,1},{1,0}};
        if (n == 0)
            return 0;
        power(F, n-1, m);
        return F[0][0];
    }

    static void power(long long F[2][2], long long n, int m)
    {
        if(n == 0 || n == 1)
            return;

        long long M[2][2] = {{1,1},{1,0}};

        power(F, n/2, m);
        multiply(F, F, m);

        if (n%2 != 0)
            multiply(F, M, m);
    }

    static void multiply(long long F[2][2], long long  M[2][2], int m)
    {
        long long x =  F[0][0]*M[0][0] + F[0][1]*M[1][0];
        long long y =  F[0][0]*M[0][1] + F[0][1]*M[1][1];
        long long z =  F[1][0]*M[0][0] + F[1][1]*M[1][0];
        long long w =  F[1][0]*M[0][1] + F[1][1]*M[1][1];

        F[0][0] = x%m;
        F[0][1] = y%m;
        F[1][0] = z%m;
        F[1][1] = w%m;
    }
};

int main(void) {
    long long n;
    int m;
    std::cin >> n >> m;
    std::cout << Fibonacci::get_remainder(n, m) << std::endl;
    return 0;
}