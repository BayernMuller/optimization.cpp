#include <iostream>
#include <vector>
#include <future>
#include "utils/benchmark.h"

constexpr int kIterations = 1000000;

int sum_single_thread()
{
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

int main(int argc, char* argv[])
{
    auto bench = BENCHMARKING(
        sum_single_thread,
        sum_with_async
    );
    return bench.run(argc, argv);
}
