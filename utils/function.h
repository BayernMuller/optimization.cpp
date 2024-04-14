#ifndef UTILS_FUNCTION_H_
#define UTILS_FUNCTION_H_

#include <chrono> 
#include <iostream>
#include <string>
#include <thread> 

namespace utils
{

class Function
{
public:
    explicit Function(const char *name);
    Function(Function &) = delete;
    Function(Function &&) = delete;
    void operator=(Function) = delete;
    ~Function();

private:
    const std::string name_;
    const std::thread::id thread_id_;
    std::chrono::time_point<std::chrono::high_resolution_clock> start_;
};

Function::Function(const char *name) : name_(name), thread_id_(std::this_thread::get_id())
{
    std::cout << "+ " << name_ << "() " << thread_id_ << std::endl;
    start_ = std::chrono::high_resolution_clock::now();
}

Function::~Function()
{
    auto duration = std::chrono::high_resolution_clock::now() - start_;
    auto ns = std::chrono::duration_cast<std::chrono::nanoseconds>(duration);
    std::cout << "- " << name_ << "() " << thread_id_ << std::endl;
    std::cout << "  took " << ns.count() << " ns" << std::endl;
    std::cout << std::endl;
}

} // namespace utils

#endif // UTILS_FUNCTION_H_
