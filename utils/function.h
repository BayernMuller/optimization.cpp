#ifndef UTILS_FUNCTION_H_
#define UTILS_FUNCTION_H_

/*

Copyright 2024 Jayden Yang

*/

#include <chrono> // NOLINT [build/c++11]
#include <string>
#include <iostream>

namespace utils {

class Function {
 public:
    explicit Function(const char *name);
    Function(Function &) = delete;
    void operator=(Function) = delete;
    ~Function();

 private:
    const std::string name_;
    std::chrono::time_point<std::chrono::high_resolution_clock> start_;
};

Function::Function(const char *name) : name_(name) {
    std::cout << "+ " << name_ << "()" << std::endl;
    start_ = std::chrono::high_resolution_clock::now();
}

Function::~Function() {
    auto duration = std::chrono::high_resolution_clock::now() - start_;
    auto ns = std::chrono::duration_cast<std::chrono::nanoseconds>(duration);
    std::cout << "- " << name_ << "() took " << ns.count() << " ns"
        << std::endl;
}

}  // namespace utils

#endif  // UTILS_FUNCTION_H_
