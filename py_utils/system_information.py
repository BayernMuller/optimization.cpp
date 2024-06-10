import platform
import psutil

class SystemInformation:
    def __init__(self):
        self.os_name = platform.system()
        self.os_version = platform.version()
        self.cpu_count = psutil.cpu_count(logical=True)
        self.physical_cpu_count = psutil.cpu_count(logical=False)
        self.cpu_frequency = psutil.cpu_freq().current if psutil.cpu_freq() else 'Unknown'
        self.total_memory = psutil.virtual_memory().total
        self.architecture = platform.architecture()

    def __str__(self):
        return (f"Operating System: {self.os_name} {self.os_version}\n"
                f"CPU Count: {self.cpu_count} (Logical), {self.physical_cpu_count} (Physical)\n"
                f"CPU Frequency: {self.cpu_frequency} MHz\n"
                f"Total Memory: {self.total_memory / (1024 ** 3):.2f} GB\n"
                f"CPU Architecture: {self.architecture}\n")
    

if __name__ == '__main__':
    si = SystemInformation()
    print(si)