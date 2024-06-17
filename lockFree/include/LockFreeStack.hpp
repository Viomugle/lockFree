#include <iostream>
#include <atomic>
#include <memory>
#include <thread>
#include <chrono>
#include <random>

template <typename T>
struct node
{
    T value;
    node* next;
    node(T const&data_):value(data_),next(nullptr){}
};

template <typename T>
class lock_free_stack{
    private:
        std::atomic<node<T>*> m_head;
    public:
        lock_free_stack
}
