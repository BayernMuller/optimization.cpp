

#include <iostream>

#include "../utils/function.h"

constexpr int kSize = 100;

void row_major(int arr[kSize][kSize][kSize])
{
    utils::Function f(__FUNCTION__);

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

void column_major(int arr[kSize][kSize][kSize])
{
    utils::Function f(__FUNCTION__);

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

int main()
{
    int arr[kSize][kSize][kSize];
    // row major access is faster than column major access!
    row_major(arr);
    column_major(arr);
    return 0;
}
