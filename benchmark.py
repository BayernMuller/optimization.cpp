from py_utils import (
    SystemInformation,
    Builder
)
import argparse
import subprocess
from collections import defaultdict
import json
from plotly import graph_objects as go

class Benchmark:
    def __init__(self, path, include=None, lib=None):
        self.path = path
        self.builder = Builder(path, include=include, lib=lib)

    def run(self, output='main') -> str:
        result = defaultdict(dict)
        for optimization in Builder.AVAILABLE_OPTIMIZATIONS:
            self.builder.set_optimization(optimization)
            
            self.builder.build(output)
            execution = f'./{output}'
            count = 0
            
            for _ in range(10):
                res = subprocess.run([execution, str(count)], capture_output=True)
                if res.returncode != 0:
                    break
                stdout = res.stdout.decode('utf-8')
                json_output = json.loads(stdout)
                name = json_output['name']
                took = json_output['took']
                result[name][optimization] = took
                count += 1
        
        return result
    
    def graph(self, res):
        fig = go.Figure()

        for category, timings in res.items():
            fig.add_trace(go.Bar(
                x=list(timings.keys()),
                y=list(timings.values()),
                name=category
            ))

        fig.update_layout(
            title="Execution Time for Different Compiler Optimization Options",
            xaxis_title="Compiler Optimization Option",
            yaxis_title="Execution Time (in nanoseconds)",
            barmode='group'
        )

        fig.show()
    

if __name__ == '__main__':
    parser = argparse.ArgumentParser(description='Benchmark runner')
    parser.add_argument('path', type=str, help='Path to tequnique directory')
    parser.add_argument('--include', type=str, default=None, help='Include path')
    parser.add_argument('--lib', type=str, default=None, help='Library path')
    
    args = parser.parse_args()
    benchmark = Benchmark(args.path)
    res = benchmark.run()
    
    benchmark.graph(res)