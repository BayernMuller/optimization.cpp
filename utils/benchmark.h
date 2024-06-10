#ifndef UTILS_BENCHMARK_H_
#define UTILS_BENCHMARK_H_

#include <functional>
#include <vector>
#include <iostream>
#include <string>
#include <chrono>

namespace benchmark
{

template<typename Function>
class Benchmark : public std::vector<std::pair<std::string, Function>>
{
public:
    using std::vector<std::pair<std::string, Function>>::vector;

    template<typename... Args>
    int run(int argc, char* argv[], Args... args)
    {
        if (argc < 2)
        {
            runAll(args...);
            return 0;
        }

        int function_index = atoi(argv[1]);
        if (function_index < 0 || function_index >= this->size())
        {
            std::cerr << "Invalid benchmark index" << std::endl;
            return 1;
        }
        auto took = runFunction((*this)[function_index], args...);
        std::cout << "{";
        std::cout << "\"name\": \"" << (*this)[function_index].first << "\"";
        std::cout << ", \"took\": " << took;
        std::cout << "}";
        return 0;
    }

private:
    template<typename... Args>
    void runAll(Args... args)
    {
        for (const auto &f : *this)
        {
            runFunction(f, args...);
        }
    }

    template<typename... Args>
    auto runFunction(const std::pair<std::string, Function> &f, Args... args)
    {
        std::cerr << "+ " << f.first << "()" << std::endl;
        auto start = std::chrono::high_resolution_clock::now();
        
        f.second(args...);
        
        auto end = std::chrono::high_resolution_clock::now();
        auto took = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
        std::cerr << "- " << f.first << "()\n  took " << took << " ns" << std::endl;
        std::cerr << std::endl;
        return took;
    }

};

#define STRINGIFY(x) #x
#define TOSTRING(x) STRINGIFY(x)
#define MAKE_PAIR(x) std::make_pair(TOSTRING(x), std::function(x))

#define FUNCTION_LIST_1(fn) MAKE_PAIR(fn)
#define FUNCTION_LIST_2(fn, ...) MAKE_PAIR(fn), FUNCTION_LIST_1(__VA_ARGS__)
#define FUNCTION_LIST_3(fn, ...) MAKE_PAIR(fn), FUNCTION_LIST_2(__VA_ARGS__)
#define FUNCTION_LIST_4(fn, ...) MAKE_PAIR(fn), FUNCTION_LIST_3(__VA_ARGS__)
#define FUNCTION_LIST_5(fn, ...) MAKE_PAIR(fn), FUNCTION_LIST_4(__VA_ARGS__)
#define FUNCTION_LIST_6(fn, ...) MAKE_PAIR(fn), FUNCTION_LIST_5(__VA_ARGS__)
#define FUNCTION_LIST_7(fn, ...) MAKE_PAIR(fn), FUNCTION_LIST_6(__VA_ARGS__)
#define FUNCTION_LIST_8(fn, ...) MAKE_PAIR(fn), FUNCTION_LIST_7(__VA_ARGS__)
#define FUNCTION_LIST_9(fn, ...) MAKE_PAIR(fn), FUNCTION_LIST_8(__VA_ARGS__)
#define FUNCTION_LIST_10(fn, ...) MAKE_PAIR(fn), FUNCTION_LIST_9(__VA_ARGS__)

#define GET_MACRO(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, NAME, ...) NAME
#define FUNCTION_LIST(...) \
        GET_MACRO(__VA_ARGS__, \
        FUNCTION_LIST_10, \
        FUNCTION_LIST_9, \
        FUNCTION_LIST_8, \
        FUNCTION_LIST_7, \
        FUNCTION_LIST_6, \
        FUNCTION_LIST_5, \
        FUNCTION_LIST_4, \
        FUNCTION_LIST_3, \
        FUNCTION_LIST_2, \
        FUNCTION_LIST_1)(__VA_ARGS__)

#define FUNCTION_TYPE(fn, ...) decltype(fn)
#define BENCHMARKING(...) \
    benchmark::Benchmark<std::function<FUNCTION_TYPE(__VA_ARGS__)>>{FUNCTION_LIST(__VA_ARGS__)}

} // namespace benchmark

#endif // UTILS_BENCHMARK_H_