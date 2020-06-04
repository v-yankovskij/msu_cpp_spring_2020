#include <fstream>
#include <iostream>
#include <stdio.h>
#include "sort.h"

int main()
{
    std::atomic<bool> finished(false);
    std::atomic<int> finished_step(0);
    std::atomic<int> finished_sort(0);
    std::condition_variable condition;
    std::mutex sort_finish_mutex;
    std::mutex iter_finish_mutex;
    std::mutex stream_read_mutex;
    std::mutex output_queue_mutex;
    uint_seq nums(M / sizeof(uint64_t));
    std::ifstream datas("data.bin", std::ios::binary);
    std::queue<std::string> output_queue;
    std::vector<std::thread> threads;
    if (!datas)
    {
        throw std::invalid_argument("can't open file");
    }
    for (int i = 0; i < N; i++)
    {
        threads.emplace_back(Sort, std::ref(nums),std::ref(datas), i, std::ref(output_queue), std::ref(finished), std::ref(finished_step), std::ref(finished_sort), std::ref(condition), std::ref(sort_finish_mutex), std::ref(iter_finish_mutex), std::ref(stream_read_mutex), std::ref(output_queue_mutex));
    }
    for (int i = 0; i < N; i++)
    {
        threads[i].join();
    }
    system("pause");
    return 0;
}
