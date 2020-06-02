#include <fstream>
#include <iostream>
#include <stdio.h>
#include "sort.h"

constexpr auto BufferSize = 8 << 20;

int main(int argc, char* argv[])
{
    std::vector<uint64_t> elements;
    for (i = 1; i < argc; i++)
    {
        elements.push_back(std::stoi(argv[i]));
    }
    std::ofstream input_file("input.txt", std::ios::binary | std::ios::trunc);
    for (auto& elem : elements)
    {
        input_file.write(reinterpret_cast<char*>(&elem), sizeof(elem));
    }
    auto path = std::experimental::filesystem::path("input.txt");
    auto save_path = std::experimental::filesystem::path("output.txt");
    FileSorter Sorter(BufferSize);
    Sorter.Run(path.string(), save_path.string());
    std::ifstream output_file("input.txt", std::ios::binary);
    std::cout << output_file.rdbuf();
    return 0;
}
