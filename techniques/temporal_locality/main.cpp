#include <iostream>

#include "../utils/benchmark.h"

constexpr int kSize = 1000000000;

void frequent_access(std::vector<int> *data)
{
    for (int j = 0; j < kSize; ++j)
    {
        (*data)[0]++;
    }
}

void infrequent_access(std::vector<int> *data)
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
        frequent_access,
        infrequent_access
    );
    return bench.run(argc, argv, &data);
}