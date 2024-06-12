from pydantic import BaseModel
from typing import List, Dict, Optional, Any

class ExecutionResult(BaseModel):
    name: str
    took: float
    
class OptimizationResult(BaseModel):
    optimization: str
    results: List[ExecutionResult] = []

class BenchmarkResult(BaseModel):
    title: str
    compiler: str
    compiler_info: str
    build_command: str
    system_information: Optional[Dict[str, Any]] = None
    benchmarks: List[OptimizationResult] = []