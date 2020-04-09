#include "bigint.h"
#include <stdio.h>

int main(int argc, char* argv[])
{
    BigInt a = BigInt(int64_t(std::stoi(argv[1])));
    BigInt b = BigInt(int64_t(std::stoi(argv[2])));
    std::cout << a + b << ' ' << a * b;
    return 0;
}
