#ifndef  LOCK_FREE_RING_BUFFER_HPP
#define  LOCK_FREE_RING_BUFFER_HPP
#include <atomic>
#include <cstddef>
#include <cstdlib>
#include <cstddef>
#include <cstdint>


template <typename T>
class LockFreeRingBuffer {
    private:
        T* data=nullptr;
        std::atomic<size_t> m_head;
        std::atomic<size_t> m_tail;
        size_t capacity;
    public:
        LockFreeRingBuffer(size_t size);
        ~LockFreeRingBuffer();
        bool back(T data);
        bool front(T& data);
    private:
        bool CAS(std::atomic<size_t>& target, size_t expected, size_t desired);
};

template <typename T>
LockFreeRingBuffer<T>::LockFreeRingBuffer(size_t size) {
    data = (T*)malloc(size*sizeof(T));
    m_head = 0;
    m_tail = 0;
    capacity = size;
}


template<typename T>
LockFreeRingBuffer<T>::~LockFreeRingBuffer() {
    free(data);
}


template<typename T>
bool LockFreeRingBuffer<T>::back(T val) {
    auto cur_h=m_head.load();
    auto cur_t=m_tail.load(); 
    do
    {
        cur_h=m_head.load();
        cur_t=m_tail.load(); 
        if((cur_t+1)%capacity==cur_h)//full
        {
            return false;
        }
    }while(!CAS(m_tail,cur_t,(cur_t+1)%capacity));
    data[(cur_t)%capacity]=val;
    return true;
}

template<typename T>
bool LockFreeRingBuffer<T>::front(T& val) {
    auto cur_h=m_head.load();
    auto cur_t=m_tail.load(); 
    do
    {
        cur_h=m_head.load();
        cur_t=m_tail.load(); 
        if(cur_h==cur_t)//empty
        {
            return false;
        }
    }while(!CAS(m_head,cur_h,(cur_h+1)%capacity));
    val=data[(cur_h)%capacity];
    return true;
}



template<typename T>
bool LockFreeRingBuffer<T>::CAS(std::atomic<size_t>& target, size_t expected, size_t desired) {
    return target.compare_exchange_strong(expected, desired);
}

#endif
