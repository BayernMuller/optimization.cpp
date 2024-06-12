import platform
import psutil
import cpuinfo

class SystemInformation:
    def __init__(self):
        self.os_name = platform.system()
        self.os_version = platform.version()
        self.cpu = cpuinfo.get_cpu_info()['brand_raw']
        self.cpu_count = psutil.cpu_count(logical=True)
        self.physical_cpu_count = psutil.cpu_count(logical=False)
        self.cpu_frequency = psutil.cpu_freq().current if psutil.cpu_freq() else 'Unknown'
        self.total_memory = psutil.virtual_memory().total
        self.architecture = platform.machine()
    
    def __dict__(self):
        return {
            'os_name': self.os_name,
            'os_version': self.os_version,
            'cpu': self.cpu,
            'logical_cpu_count': self.cpu_count,
            'physical_cpu_count': self.physical_cpu_count,
            'cpu_frequency': f'{self.cpu_frequency:.2f} MHz',
            'total_memory': f'{self.total_memory / 1024 / 1024 / 1024:.2f} GB',
            'architecture': self.architecture
        }

if __name__ == '__main__':
    si = SystemInformation()
    print(si.__dict__())