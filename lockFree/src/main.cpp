#include <iostream>
#include "LockFreeRingBuffer.hpp"
#include <thread>
#include <functional>
#include <vector>
#include <mutex>    
#include "threadpool.h"


ThreadPool tp(8);

void task(int num)
{
    printf("task %d\n",num);
    fflush(stdout);
}

void addtask(std::function<void()> task)
{
    tp.add_task(task);
}


int main(int argc, char **argv)
{
    for(int i=0;i<2000;i++)
    {
        addtask(std::bind(task,i));
    }
    tp.stop();
    std::cout<<"main thread exit"<<std::endl;
    while (1)
    {
        std::this_thread::yield();
    }
    
    return 0;

}
