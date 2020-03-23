#include "my_allocator.h"

int main(int argc, char* argv[])
{
    size_t max_size = (size_t)std::stoi(argv[1], nullptr);
    my_allocator allocator(max_size);
    for(int i = 2; i < argc; i++)
    {
        if (argv[i][0] == 'r')
        {
            allocator.reset();
        }
        else
        {
            size_t size = (size_t)std::stoi(argv[i], nullptr);
            char* ptr = allocator.alloc(size);
            if (ptr == nullptr)
            {
                std::cout << "out of memory ";
            }
            else
            {
                std::cout << "allocated ";
            }
        }
    }
    return 0;
}
