#include "threadpool.h"
#include <cstddef>
#include <stddef.h>
#include <iostream>

ThreadPool::ThreadPool(size_t thread_num = 8) : m_task_queue(16), m_running(true)
{
    for (size_t i = 0; i < thread_num; i++)
    {
        m_threads.push_back(std::thread([this]() {
            while (m_running)
            {
                std::function<void()> task;
                if (m_task_queue.front(task))
                {
                    task();
                }
            }
        }));
    }
}

ThreadPool::~ThreadPool()
{
    stop();
}

void ThreadPool::add_task(std::function<void()> task)
{
    while (!m_task_queue.back(task))
        ;
}

void ThreadPool::stop()
{
    m_running = false;
    
    for (auto &thread : m_threads)
    {
        thread.join();
    }
    std::cout << "thread pool stop" << std::endl;
}