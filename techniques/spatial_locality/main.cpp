#include <iostream>

#include "../utils/benchmark.h"

constexpr int kSize = 500;
using ThreeDArray = std::vector<std::vector<std::vector<int>>>;

void row_major(ThreeDArray& arr)
{
    // access array in row-major order
    for (int i = 0; i < kSize; ++i)
    {
        for (int j = 0; j < kSize; ++j)
        {
            for (int k = 0; k < kSize; ++k)
            {
                arr[i][j][k] = 0xc0ffee;
            }
        }
    }
}

void column_major(ThreeDArray& arr)
{   
    // access array in column-major order
    for (int i = 0; i < kSize; ++i)
    {
        for (int j = 0; j < kSize; ++j)
        {
            for (int k = 0; k < kSize; ++k)
            {
                arr[k][j][i] = 0xc0ffee;
            }
        }
    }
}

int main(int argc, char* argv[])
{
    ThreeDArray arr(kSize, std::vector<std::vector<int>>(kSize, std::vector<int>(kSize, 0)));
    auto bench = BENCHMARKING(
        row_major,
        column_major
    );
    return bench.run(argc, argv, arr);
}
