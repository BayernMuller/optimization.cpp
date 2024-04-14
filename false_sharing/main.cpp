/*

Copyright 2024 Jayden Yang

*/

#include <vector>
#include <thread> // NOLINT [build/c++11]

#include "../utils/function.h"

constexpr int kIterations = 1000000000;
constexpr int kPaddingSize = 64;

struct PaddedInt {
    volatile int value;
    char padding[kPaddingSize - sizeof(int)];
};

#pragma pack(push, 1)
struct UnpaddedInt {
    volatile int value;
};
#pragma pack(pop)

static_assert(sizeof(PaddedInt) == kPaddingSize, "PaddedInt is not padded");
static_assert(sizeof(UnpaddedInt) == sizeof(int), "UnpaddedInt is padded");

template <typename T>
void increment(T* data) {
    utils::Function f(__FUNCTION__);
    for (int i = 0; i < kIterations; ++i) {
        data->value++;
    }
}

int main() {
    constexpr int kThreadCount = 4;

    std::thread threads1[kThreadCount];
    std::vector<PaddedInt> padded_data(kThreadCount);

    for (int i = 0; i < kThreadCount; ++i) {
        threads1[i] = std::thread(increment<PaddedInt>, &padded_data[i]);
    }

    for (auto& thread : threads1) {
        thread.join();
    }

    std::thread threads2[kThreadCount];
    std::vector<UnpaddedInt> unpadded_data(kThreadCount);

    for (int i = 0; i < kThreadCount; ++i) {
        threads2[i] = std::thread(increment<UnpaddedInt>, &unpadded_data[i]);
    }

    for (auto& thread : threads2) {
        thread.join();
    }

    return 0;
}

/*
+ increment() 0x16f8bb000
+ increment() 0x16fa5f000
+ increment() 0x16f9d3000
+ increment() 0x16f947000
- increment() 0x16fa5f000 took 2068267708 ns
- increment() 0x16f9d3000 took 2075802166 ns
- increment() 0x16f8bb000 took 2100436291 ns
- increment() 0x16f947000 took 2102462958 ns
+ increment() 0x16f8bb000
+ increment() 0x16f947000
+ increment() 0x16fa5f000
+ increment() 0x16f9d3000
- increment() 0x16f8bb000 took 2197488875 ns
- increment() 0x16fa5f000 took 2208755500 ns
- increment() 0x16f9d3000 took 2216119417 ns
- increment() 0x16f947000 took 2230533917 ns
*/
