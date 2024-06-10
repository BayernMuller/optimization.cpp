#include <iostream>

#include "utils/benchmark.h"

constexpr int kSize = 100000000;
static_assert(kSize % 10 == 0, "kSize must be a multiple of 10 to unroll");

void loop_unroll(std::vector<int> *data)
{
    for (int j = 0; j < kSize; j += 10)
    {
        (*data)[j]++;
        (*data)[j + 1]++;
        (*data)[j + 2]++;
        (*data)[j + 3]++;
        (*data)[j + 4]++;
        (*data)[j + 5]++;
        (*data)[j + 6]++;
        (*data)[j + 7]++;
        (*data)[j + 8]++;
        (*data)[j + 9]++;
    }
}

void loop_unroll_with_pragma_unroll(std::vector<int> *data)
{
#pragma unroll 10
    for (int j = 0; j < kSize; ++j)
    {
        (*data)[j]++;
    }
}

void no_loop_unroll(std::vector<int> *data)
{
    for (int i = 0; i < kSize; ++i)
    {
        (*data)[i]++;
    }
}

int main(int argc, char* argv[])
{
    std::vector<int> data(kSize, 0);
    auto bench = BENCHMARKING(
        loop_unroll,
        loop_unroll_with_pragma_unroll,
        no_loop_unroll
    );
    return bench.run(argc, argv, &data);
}