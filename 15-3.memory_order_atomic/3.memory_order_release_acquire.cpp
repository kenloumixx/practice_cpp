#include <iostream>
#include <atomic>
#include <vector>
#include <thread>

std::atomic<bool> is_ready;
std::atomic<int> data[3];

void producer()
{
    data[0].store(1, std::memory_order_relaxed);
    data[1].store(2, std::memory_order_relaxed);
    data[2].store(3, std::memory_order_relaxed);
    is_ready.store(true, std::memory_order_release);
}

void consumer()
{
    while (!is_ready.load(std::memory_order_acquire))
    {

    }
    std::cout << "data[0] : " << data[0].load(std::memory_order_relaxed) << std::endl; 
    std::cout << "data[1] : " << data[1].load(std::memory_order_relaxed) << std::endl; 
    std::cout << "data[2] : " << data[2].load(std::memory_order_relaxed) << std::endl; 
}

int main()
{
    std::vector<std::thread> workers;
    workers.push_back(std::thread(producer));
    workers.push_back(std::thread(consumer));

    for (int i = 0; i < 2; i++)
    {
        workers[i].join();
    }
    return 0;
}