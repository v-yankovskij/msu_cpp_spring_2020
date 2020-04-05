#include "serializer_h"

struct Data
{
    char a;
    bool b;
    uint64_t c;
    template <class Serializer>
    Error serialize(Serializer& serializer)
    {
        return serializer(a, b, c);
    }
};


int main(int argc, char* argv[];)
{
    Data x{argv[0][0], (std::stoi(argv[1]) > 0), std::stoi(argv[2])};
    Data y{'c', false, 1};
    serializer.save(x);
    const Error err = deserializer.load(y);
    std::cout << (x.a == y.a) << ' ' << assert(x.b == y.b) << ' ' << assert(x.c == y.c);
}

