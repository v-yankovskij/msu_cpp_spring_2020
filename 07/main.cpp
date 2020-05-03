#include <stdio.h>
#include "vector.h"
#include <iostream>

int main(int argc, char* argv[])
{
    Vector<int> v;
    for(int i = 1; i < argc; i++)
    {
        v.push_back(std::stoi(argv[i]));
    }
    for(int i = 0; i < argc - 1; i++)
    {
        std::cout << v[i] << " ";
    }
    return 0;
}
