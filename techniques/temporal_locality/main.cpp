#include <iostream>

#include "../utils/benchmark.h"

constexpr int kSize = 100000000;

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

int main()
{
    std::vector<int> data(kSize, 0);
    frequent_access(&data);
    // frequent access is faster than infrequent access because of cache hit rate is higher. [NOLINT]
    infrequent_access(&data);
    return 0;
}

/*
+ frequent_access()
- frequent_access() took 197698125 ns
+ infrequent_access()
- infrequent_access() took 225844333 ns
*/
