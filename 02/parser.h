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
    
    parser()
    {
        callback_on_number = nullptr;
        callback_on_string = nullptr;
        callback_on_start = nullptr;
        callback_on_stop = nullptr;
    }
    
    void define_callback_on_number(int_function_ptr number)
    {
        callback_on_number = number;
    }
 
    void define_callback_on_string(string_function_ptr string)
    {
        callback_on_string = string;
    }

    void define_callback_on_start(void_function_ptr start)
    {
        callback_on_start = start;
    }

    void define_callback_on_stop(void_function_ptr stop)
    {
        callback_on_stop = stop;
    }

    void parse(const std::string& text)
    {
        char pos;
        std::string token = "";
        if (callback_on_start)
        {
            callback_on_start();
        }
        bool dig;
        for (int i =0; i < text.length(); i++)
        {
            dig = true;
            while (isspace(text[i]))
            {
                i++;
            }
            while (text[i] && !isspace(text[i]))
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
                if (callback_on_number)
                {
                    callback_on_number(std::stoi(token));
                }
                token.erase();
                continue;
            }
            if(token.length())
            {
                if (callback_on_string)
                {
                    callback_on_string(token);
                }
            }
            token.erase();
        }
        callback_on_stop();
    }
};

#endif 
