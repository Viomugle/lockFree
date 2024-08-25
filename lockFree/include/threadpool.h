#include <thread>
#include "LockFreeRingBuffer.hpp"
#include <functional>
#include <vector>
#include <atomic>   
#include <cstddef>
#include <cstddef>
#include <cstdint>



class ThreadPool {
    private:
        LockFreeRingBuffer<std::function<void()>> m_task_queue;
        std::vector<std::thread> m_threads;
        std::atomic<bool> m_running;
    public:
        ThreadPool(size_t thread_num);
        ~ThreadPool();
        void add_task(std::function<void()> task);
        void stop();
};