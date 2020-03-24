#include "parser.h"

void callback_on_number(int str)
{
    std::cout<<"number ";
}

void callback_on_string(const std::string& str)
{
    std::cout<<"string ";
}

void callback_on_start()
{
    std::cout<<"start ";
}

void callback_on_stop()
{
    std::cout<<"stop ";
}

int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        return 1;
    }
    std::string s;
    for (int i = 1; i < argc; i++)
    {
        s.append(argv[i]);
        s.append(" ");
    }
    parser p(callback_on_number, callback_on_string, callback_on_start, callback_on_stop);
    p.parse(s);
    return 0;
}
