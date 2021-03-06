#ifndef pool_h
#define pool_h

#include <condition_variable>
#include <ctype.h>
#include <functional>
#include <future>
#include <iostream>
#include <mutex>
#include <queue>
#include <thread>
#include <vector>
 
class ThreadPool
{
public:
    std::condition_variable cond;
    std::queue<std::function<void()>> my_queue;
    std::mutex mut;
    std::vector< std::thread > pool;
    std::atomic<bool> terminate;
    size_t pool_size;
    
    void thread_func()
    {
        std::function<void()> task;
        while(true)
        {
            std::unique_lock<std::mutex> lock(mut);
            while (my_queue.empty() && !terminate)
            {
                cond.wait(lock);
            }
            if (my_queue.empty() || terminate)
            {
                return;
            }
            task =  my_queue.front();
            my_queue.pop();
            task();
        }
    }

    ThreadPool(size_t PoolSize)
    {
        pool_size = PoolSize;
        terminate = false;
        for (size_t i = 0; i < pool_size; ++i)
        {
            pool.emplace_back(&ThreadPool::thread_func, this);
        }
    }
    
    template <class Func, class... Args> auto exec(Func func, Args... args) -> std::future<decltype(func(args...))>
    {
        if (terminate)
        {
            throw std::runtime_error("The pool is not active");
        }
        std::lock_guard<std::mutex> lock(mut);
        auto task = std::make_shared<std::packaged_task<decltype(func(args...))()>>(std::bind(func, args...));
        auto future = task->get_future();
        my_queue.push([task](){(*task)();});
        cond.notify_one();
        return future;
    }
    
    ~ThreadPool()
    {
        terminate = true;
        cond.notify_all();
        for(size_t i=0; i < pool_size; i++)
        {
            pool[i].join();
        }
    }
    
};

#endif
