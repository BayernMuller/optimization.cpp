#include <iostream>
#include <vector>
#include <future>

#include "../utils/function.h"

constexpr int kIterations = 1000000;

int sum_single_thread()
{
    utils::Function f(__func__);
    std::vector<int> v(kIterations, 1);
    int sum = 0;
    for (int i = 0; i < kIterations; ++i)
    {
        sum += v[i];
    }
    return sum;
}

int sum_with_async()
{
    utils::Function f(__func__);
    std::vector<int> v(kIterations, 1);
    
    constexpr int kThreads = 4;
    static_assert(kIterations % kThreads == 0, "kIterations must be divisible by kThreads");
    auto task = [&v](int start, int end) {
        int sum = 0;
        for (int i = start; i < end; ++i)
        {
            sum += v[i];
        }
        return sum;
    };

    std::vector<std::future<int>> futures(kThreads);
    for (int i = 0; i < kThreads; ++i)
    {
        int start = i * kIterations / kThreads;
        int end = (i + 1) * kIterations / kThreads;
        futures[i] = std::async(std::launch::async, task, start, end);
    }   

    int sum = 0;
    for (int i = 0; i < kThreads; ++i)
    {
        sum += futures[i].get();
    }
    return sum;
}

int main()
{
    auto single_thread_sum = sum_single_thread();
    auto async_sum = sum_with_async();
    
    std::cout << "Single thread sum: " << single_thread_sum << std::endl;
    std::cout << "Async sum: " << async_sum << std::endl;
}

/*

+ sum_single_thread() 0x1f769b900
- sum_single_thread() 0x1f769b900
  took 29573791 ns

+ sum_with_async() 0x1f769b900
- sum_with_async() 0x1f769b900
  took 19723125 ns

Single thread sum: 1000000
Async sum: 1000000

*/