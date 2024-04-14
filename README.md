<p align="center">
    <img src="docs/logo.svg" width="100%"/>
</p>

<span align="center">
    
# C++ Optimization

Skills and techniques for fast and efficient C++ code.

</span>

<br>

### Table of Contents

##### Techniques
- [Loop Unrolling](loop_unroll/): a technique to improve performance by reducing loop overhead.

##### Parallel Programming
- [False Sharing](false_sharing/): a performance issue that occurs when multiple threads modify variables that reside on the same cache line.
- [std::async](async/): a high-level interface for managing asynchronous tasks supported by the C++ Standard Library.

##### Memory and Cache
- [Spatial Locality](spatial_locality/): a principle that states that if a program accesses a memory location, it is likely to access nearby memory locations in the near future.
- [Temporal Locality](temporal_locality/): a principle that states that if a program accesses a memory location, it is likely to access the same memory location in the near future.

### Getting Started

##### Requirements
- C++ compiler with C++20 support

##### Running the examples
```bash
git clone https://github.com/BayernMuller/cpp-optimization
cd cpp-optimization
./run.sh <example>
```

### Contributing

Contributions are welcome! For bug reports, feature requests, or questions, please submit an issue.

### License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.
