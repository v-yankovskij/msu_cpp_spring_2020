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
    
    ThreadPool(size_t poolSize) 
    {
        pool_size = poolSize;
        terminate = false;
        for (size_t i = 0; i < pool_size; ++i)
        {
            pool.emplace_back(&thread_func, this);
        }
    }
    
    void thread_func()
    {
        std::function<void()> task;
        while(true)
        {
            std::unique_lock<std::mutex> lock(m);
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
    
    template <class Func, class... Args> auto exec(Func func, Args... args) -> std::future<decltype(func(args...))>
    {
        using type = decltype(func(args...));
        std::lock_guard<std::mutex> lock(mut);
        if (terminate)
        {
            throw std::runtime_error("The pool is not active");
        }
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
	    threads[i].join();
	}
    }
    
};

#endif
