#ifndef my_allocator_h
#define my_allocator_h

#include <iostream>
#include <memory>

class my_allocator
{
public:
    size_t allocator_capacity;
    size_t allocator_size;
    std::unique_ptr<char[]> allocator_memory;
    
    my_allocator(size_t max_size)
    {
        allocator_capacity = max_size;
        allocator_size = 0;
        allocator_memory = std::unique_ptr<char[]>(new char[max_size]);
    }
    
    char* alloc(size_t size)
    {
        if (allocator_size + size <= allocator_capacity)
        {
            char* ptr = allocator_memory.get() + allocator_size;
            allocator_size += size;
            return ptr;
        }
        else
        {
            return nullptr;
        }
    }
    
    void reset()
    {
        allocator_size = 0;
    }
};

#endif
