#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <omp.h>

#include "../utils/benchmark.h"

using vec = std::vector<int>;

constexpr int kIterations = 100000000;
constexpr int kPrintLimit = 20;
constexpr int kThreads = 4;

static_assert(kIterations > kPrintLimit, "kIterations should be greater than kPrintLimit");

void sum_single_thread(const vec& v1, const vec& v2)
{   
    vec result(kIterations);
    for (size_t i = 0; i < kIterations; ++i)
    {
        result[i] = v1[i] + v2[i];
    }

    for (size_t i = 0; i < kPrintLimit; ++i)
    {
        std::cout << result[i] << " ";
    }
    std::cout << std::endl;
}

void sum_with_openmp(const vec& v1, const vec& v2)
{   
    vec result(kIterations);

    #pragma omp parallel for num_threads(kThreads)
    for (size_t i = 0; i < kIterations; ++i)
    {
        result[i] = v1[i] + v2[i];
    }

    for (size_t i = 0; i < kPrintLimit; ++i)
    {
        std::cout << result[i] << " ";
    }
    std::cout << std::endl;
}


int main()
{
    std::mt19937 gen(std::random_device{}());
    std::uniform_int_distribution<int> dist(0, 100);

    auto generator = [&dist, &gen]{ return dist(gen); };

    vec v1(kIterations);
    std::generate(v1.begin(), v1.end(), generator);

    vec v2(kIterations);
    std::generate(v2.begin(), v2.end(), generator);

    sum_with_openmp(v1, v2);
    sum_single_thread(v1, v2);    
}

/*

+ sum_with_openmp() 0x1f769b900
170 79 163 60 101 90 141 97 130 168 128 126 58 108 78 96 81 104 166 143
- sum_with_openmp() 0x1f769b900
  took 324732000 ns

+ sum_single_thread() 0x1f769b900
170 79 163 60 101 90 141 97 130 168 128 126 58 108 78 96 81 104 166 143
- sum_single_thread() 0x1f769b900
  took 541322000 ns

*/