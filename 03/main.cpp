#include "matrix.h"

int main(int argc, char* argv[])
{
    if (argc < 4)
    {
        return 1;
    }
    if (std::stoi(argv[1]) == 0)
    {
        if (argc < 6 + std::stoi(argv[2])*stoi(argv[3]))
        {
            return 1;
        }
        matrix_ M(std::stoi(argv[2]), std::stoi(argv[3]));
        for (int i = 0; i < std::stoi(argv[2]); i++)
        {
            for (int j = 0; j < std::stoi(argv[3]); j++)
            {
                M[i][j] = std::stoi(argv[4 + i*std::stoi(argv[3]) + j]);
            }
        }
        std::cout << M[std::stoi(argv[4 + std::stoi(argv[2])*std::stoi(argv[3])])][std::stoi(argv[5 + std::stoi(argv[2])*std::stoi(argv[3])])];
    }
    if (std::stoi(argv[1]) == 1)
    {
        if (argc < 4 + 2*std::stoi(argv[2])*std::stoi(argv[3]))
        {
            return 1;
        }
        matrix_ M1(std::stoi(argv[2]), std::stoi(argv[3]));
        matrix_ M2(std::stoi(argv[2]), std::stoi(argv[3]));
        for (int i = 0; i < std::stoi(argv[2]); i++)
        {
            for (int j = 0; j < std::stoi(argv[3]); j++)
            {
                M1[i][j] = std::stoi(argv[4 + i*std::stoi(argv[3]) + j]);
            }
        }
        for (int i = 0; i < std::stoi(argv[2]); i++)
        {
            for (int j = 0; j < std::stoi(argv[3]); j++)
            {
                M2[i][j] = std::stoi(argv[4 + std::stoi(argv[2])*std::stoi(argv[3]) + i*std::stoi(argv[3]) + j]);
            }
        }
        if (M1 == M2)
        {
            std::cout << 1;
        }
        else
        {
            std::cout << 0;
        }
    }
    return 0;
}
