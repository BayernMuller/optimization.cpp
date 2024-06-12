from py_utils import *
import argparse
import subprocess
import json
import os

class Benchmark:
    def __init__(self, path, compiler='g++', include=None, lib=None, options=None):
        self.path = path
        self.builder = Builder(path, compiler, include, lib, options)

    def run(self, output='main') -> BenchmarkResult:
        result = BenchmarkResult(
            title=os.path.basename(self.path),
            compiler=self.builder.compiler,
            compiler_info=self.builder.get_compiler_info(),
            build_command=' '.join(self.builder.get_general_compile_command()),
            system_information=SystemInformation().__dict__()
        )

        executable = f'./{output}'

        for optimization in Builder.AVAILABLE_OPTIMIZATIONS:
            opti_result = OptimizationResult(optimization=optimization)
            self.builder.set_optimization(optimization)
            print(f'Building with optimization: {optimization}')
            self.builder.build(output)    
            
            for i in range(10):
                res = subprocess.run([executable, str(i)], capture_output=True)
                stdout = res.stdout.decode('utf-8')

                # 0 is success, 9 means no function found to execute. it's not an error
                if res.returncode != 0:
                    
                    if res.returncode == 9:
                        break

                    stderr = res.stderr.decode('utf-8')
                    raise Exception(f'Failed to execute {executable} with input {i}. Error: {stderr.strip()}')
                
                execute_result = ExecutionResult(**json.loads(stdout))
                opti_result.results.append(execute_result)
                
                print(f' - {execute_result.name} took {execute_result.took} ns')
            
            result.benchmarks.append(opti_result)
        
        return result

if __name__ == '__main__':
    parser = argparse.ArgumentParser(description='Benchmark runner')
    parser.add_argument('path', type=str, help='Path to tequnique directory')
    parser.add_argument('--compiler', type=str, default='g++', help='Compiler to use')
    parser.add_argument('--include', type=str, default=None, help='Include path')
    parser.add_argument('--lib', type=str, default=None, help='Library path')
    parser.add_argument('--openmp', action='store_true', help='Enable OpenMP')
    # parser.add_argument('--cuda', action='store_true', help='Enable CUDA') # Not implemented yet
    parser.add_argument('--show-graph', action='store_true', help='Show graph')
    parser.add_argument('--save-graph', action='store_true', help='Save graph')

    args = parser.parse_args()
    options = []
    if args.openmp:
        options.append('-fopenmp')

    benchmark = Benchmark(args.path, args.compiler, args.include, args.lib, options)
    res = benchmark.run()
    
    if args.show_graph:
        plot = Plot(res)
        plot.show()
    if args.save_graph:
        plot = Plot(res)
        plot.save_svg(os.path.join(args.path, 'benchmark.svg'))
        if not os.path.exists(os.path.join(args.path, 'README.md')):
            with open(os.path.join(args.path, 'README.md'), 'w') as f:
                f.write(f'# {os.path.basename(args.path)}\n')
                f.write(f'![Benchmark result](benchmark.svg)\n')

    