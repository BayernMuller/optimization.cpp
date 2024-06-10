import subprocess
import os

class Builder:
    CPP_VERSION = '-std=c++20'
    WARNINGS_FLAGS = ('-Wall', '-Wextra', '-Wpedantic')
    TARGET = 'main.cpp'
    AVAILABLE_OPTIMIZATIONS = ('-O0', '-O1', '-O2', '-O3', '-Ofast', '-Os', '-Og')

    def __init__(self, path, compiler='g++', include=None, lib=None, optimization='-O0'):
        self.path = path
        self.compiler = compiler
        self.include = include
        self.lib = lib
        self.optimization = optimization
        if not os.path.exists(os.path.join(self.path, self.TARGET)):
            raise FileNotFoundError('main.cpp not found in the given path')
        
    def set_optimization(self, optimization: str):
        assert optimization in self.AVAILABLE_OPTIMIZATIONS
        self.optimization = optimization

    def build(self, output='main') -> str:
        flags = [self.compiler, self.CPP_VERSION, self.optimization]
        flags.extend(self.WARNINGS_FLAGS)
        flags.extend(['-o', output, os.path.join(self.path, self.TARGET)])
        if self.include:
            flags.append(f'-I{self.include}')
        if self.lib:
            flags.append(f'-L{self.lib}')
        res = subprocess.run(flags)
        if res.returncode != 0:
            raise RuntimeError('Compilation failed')
        




    
        