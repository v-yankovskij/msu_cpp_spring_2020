#include <stdio.h>
#include "format.h"

int main(int argc, char* argv[])
{
    std::cout << format("{0}+{1}={2}", std::stoi(argv[1]), std::stoi(argv[2]), std::stoi(argv[1]) + std::stoi(argv[2]));
    return 0;
}
