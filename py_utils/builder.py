import subprocess
import os

class Builder:
    TARGET = 'main.cpp'
    CPP_VERSION = '-std=c++20'
    AVAILABLE_OPTIMIZATIONS = ('-O0', '-O1', '-O2', '-O3', '-Ofast', '-Os', '-Og')
    WARNINGS_FLAGS = ('-Wall', '-Wextra', '-Wpedantic', '-Werror', '-Werror=unknown-pragmas', '-Wno-deprecated-volatile', '-Wno-unknown-attributes')

    def __init__(self, path, compiler='g++', include=None, lib=None, options=None, optimization='-O3'):
        self.path = path
        self.compiler = compiler
        self.include = include
        self.lib = lib
        self.optimization = optimization
        self.options = options
        if not os.path.exists(os.path.join(self.path, self.TARGET)):
            raise FileNotFoundError('main.cpp not found in the given path')
        
    def get_compiler_info(self):
        res = subprocess.run([self.compiler, '--version'], capture_output=True)
        return res.stdout.decode('utf-8').split('\n')[0]
        
    def set_optimization(self, optimization: str):
        assert optimization in self.AVAILABLE_OPTIMIZATIONS
        self.optimization = optimization

    def get_compile_command(self, output='main', verbose=False) -> list[str]:
        flags = [self.compiler, self.CPP_VERSION, self.optimization]
        flags.extend(self.WARNINGS_FLAGS)
        flags.extend(['-o', output, os.path.join(self.path, self.TARGET)])
        
        if self.include:
            flags.append(f'-I{self.include}')

        if self.lib:
            flags.append(f'-L{self.lib}')

        if self.options:
            flags.extend(self.options)

        if verbose:
            flags.append('-v')

        return flags
    
    def get_general_compile_command(self, output='main', verbose=False):
        """
        Returns the compile command without any optimization flags and paths to include and lib to remove system dependencies
        """
        flags = self.get_compile_command(output, verbose)
        return [
            os.path.basename(f) if os.path.isdir(f) or os.path.isfile(f) else f    
            for f in flags if not ('-I' in f or '-L' in f or '-O' in f)
        ]

    def build(self, output='main', verbose=False):
        flags = self.get_compile_command(output, verbose)
        res = subprocess.run(flags)
        if res.returncode != 0:
            raise RuntimeError('Compilation failed')
        return res
        




    
        