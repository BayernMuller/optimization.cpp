#include <thread> 
#include <vector>

#include "../utils/benchmark.h"

constexpr int kIterations = 1000000000;
constexpr int kPaddingSize = 64;
constexpr int kThreadCount = 4;

struct PaddedInt
{
    volatile int value;
    char padding[kPaddingSize - sizeof(int)];
};

#pragma pack(push, 1)
struct UnpaddedInt
{
    volatile int value;
};
#pragma pack(pop)

static_assert(sizeof(PaddedInt) == kPaddingSize, "PaddedInt is not padded");
static_assert(sizeof(UnpaddedInt) == sizeof(int), "UnpaddedInt is padded");

template <typename T> void increment(T *data)
{
    for (int i = 0; i < kIterations; ++i)
    {
        data->value++;
    }
}

int sum_padded_data()
{
    std::thread threads[kThreadCount];
    std::vector<PaddedInt> padded_data(kThreadCount);

    for (int i = 0; i < kThreadCount; ++i)
    {
        threads[i] = std::thread(increment<PaddedInt>, &padded_data[i]);
    }

    for (auto &thread : threads)
    {
        thread.join();
    }

    int sum = 0;
    for (int i = 0; i < kThreadCount; ++i)
    {
        sum += padded_data[i].value;
    }
    return sum;
}

int sum_unpadded_data()
{
    std::thread threads[kThreadCount];
    std::vector<UnpaddedInt> unpadded_data(kThreadCount);

    for (int i = 0; i < kThreadCount; ++i)
    {
        threads[i] = std::thread(increment<UnpaddedInt>, &unpadded_data[i]);
    }

    for (auto &thread : threads)
    {
        thread.join();
    }

    int sum = 0;
    for (int i = 0; i < kThreadCount; ++i)
    {
        sum += unpadded_data[i].value;
    }
    return sum;
}
    

int main(int argc, char* argv[])
{
    auto bench = BENCHMARKING(
        sum_padded_data,
        sum_unpadded_data
    );
    return bench.run(argc, argv);
}