#ifndef parser_h
#define parser_h

#include <stdio.h>
#include <stdint.h>
#include <iostream>
#include <ctype.h>
#include <cstring>
#include <string>

typedef void (*int_function_ptr)(int);
typedef void (*string_function_ptr)(const std::string&);
typedef void (*void_function_ptr)();

class parser
{
public:
    int_function_ptr callback_on_number;
    string_function_ptr callback_on_string;
    void_function_ptr callback_on_start;
    void_function_ptr callback_on_stop;
    
    parser(int_function_ptr number, string_function_ptr string, void_function_ptr start, void_function_ptr stop)
    {
        callback_on_number = number;
        callback_on_string = string;
        callback_on_start = start;
        callback_on_stop = stop;
    }
    
    void parse(const std::string& text)
    {
        char pos;
        std::string token = "";
        bool dig;
        callback_on_start();
        for (int i =0; i < text.length(); i++)
        {
            dig = true;
            while (text[i] == '\n' || text[i] == '\t' || text[i] == ' ')
            {
                i++;
            }
            while (!(text[i] == '\n') && !(text[i] == '\t') && !(text[i] == ' ') && text[i])
            {
                token += text[i];
                if (!isdigit(text[i]))
                {
                    dig = false;
                }
                i++;
            }
            if (dig)
            {
                callback_on_number(std::stoi(token));
                token.erase();
                continue;
            }
            if(token.length())
            {
                callback_on_string(token);
            }
            token.erase();
        }
        callback_on_stop();
    }
};

#endif 
