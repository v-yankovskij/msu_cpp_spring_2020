#include <bigint.h>
#include <stdio.h>

int main(int argc, char** argv)
{
    BigInt a = BigInt(atoi(argv[0]))
    BigInt b = BigInt(atoi(argv[0]))
    cout << a + b << ' ' << a - b << ' ' << a * b 
}
