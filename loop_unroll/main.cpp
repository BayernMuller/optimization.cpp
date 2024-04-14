#include <iostream>

#include "../utils/function.h"

constexpr int kSize = 100000000;
static_assert(kSize % 10 == 0, "kSize must be a multiple of 10 to unroll");

void loop_unroll(std::vector<int> *data)
{
    utils::Function f(__FUNCTION__);
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
    utils::Function f(__FUNCTION__);
#pragma unroll 10
    for (int j = 0; j < kSize; ++j)
    {
        (*data)[j]++;
    }
}

void no_loop_unroll(std::vector<int> *data)
{
    utils::Function f(__FUNCTION__);
    for (int i = 0; i < kSize; ++i)
    {
        (*data)[i]++;
    }
}

int main()
{
    std::vector<int> data(kSize, 0);
    loop_unroll(&data);
    loop_unroll_with_pragma_unroll(&data);
    no_loop_unroll(&data);
    return 0;
}

/*
+ loop_unroll()
- loop_unroll() took 21630250 ns
+ loop_unroll_with_pragma_unroll()
- loop_unroll_with_pragma_unroll() took 13396583 ns
+ no_loop_unroll()
- no_loop_unroll() took 37302709 ns
*/
