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


int main(int argc, char* argv[])
{
    std::stringstream stream;
    Serializer serializer(stream);
    Deserializer deserializer(stream);
    Data x{argv[1][0], (std::stoi(argv[2]) > 0), std::stoi(argv[3])};
    Data y{'c', false, 1};
    serializer.save(x);
    const Error err = deserializer.load(y);
    std::cout << (x.a == y.a) << ' ' << (x.b == y.b) << ' ' << (x.c == y.c);
}

