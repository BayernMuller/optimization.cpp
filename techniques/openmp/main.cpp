#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <omp.h>

#include "utils/benchmark.h"

constexpr int kIterations = 100000000;
constexpr int kPrintLimit = 20;
constexpr int kThreads = 4;

static_assert(kIterations > kPrintLimit, "kIterations should be greater than kPrintLimit");

void sum_single_thread(const std::vector<int>& v1, const std::vector<int>& v2)
{   
    std::vector<int> result(kIterations);
    for (size_t i = 0; i < kIterations; ++i)
    {
        result[i] = v1[i] + v2[i];
    }
}

void sum_with_openmp(const std::vector<int>& v1, const std::vector<int>& v2)
{   
    std::vector<int> result(kIterations);
    #pragma omp parallel for num_threads(kThreads)
    for (size_t i = 0; i < kIterations; ++i)
    {
        result[i] = v1[i] + v2[i];
    }
}

int main(int argc, char* argv[])
{
    std::mt19937 gen(std::random_device{}());
    std::uniform_int_distribution<int> dist(0, 100);

    auto generator = [&dist, &gen]{ return dist(gen); };

    std::vector<int> v1(kIterations);
    std::generate(v1.begin(), v1.end(), generator);

    std::vector<int> v2(kIterations);
    std::generate(v2.begin(), v2.end(), generator);

    auto bench = BENCHMARKING(
        sum_single_thread,
        sum_with_openmp
    );
    return bench.run(argc, argv, v1, v2);
}