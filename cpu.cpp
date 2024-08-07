#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <unistd.h>

class CPUUsage {
public:
    CPUUsage() {
        previous_total_time = 0;
        previous_idle_time = 0;
    }

    double getCPUUsage() {
        std::vector<long> cpu_times = getCPUTimes();
        long idle_time = cpu_times[3];
        long total_time = 0;
        for (const auto& time : cpu_times) {
            total_time += time;
        }

        long total_diff = total_time - previous_total_time;
        long idle_diff = idle_time - previous_idle_time;

        double cpu_usage = 100.0 * (1.0 - static_cast<double>(idle_diff) / total_diff);

        previous_total_time = total_time;
        previous_idle_time = idle_time;

        return cpu_usage;
    }

private:
    std::vector<long> getCPUTimes() {
        std::ifstream proc_stat("/proc/stat");
        std::string line;
        std::getline(proc_stat, line);

        std::istringstream ss(line);
        std::string cpu;
        ss >> cpu;  // Ignore the first token ("cpu")

        std::vector<long> cpu_times;
        long time;
        while (ss >> time) {
            cpu_times.push_back(time);
        }

        return cpu_times;
    }

    long previous_total_time;
    long previous_idle_time;
};

int main() {
    CPUUsage cpu_usage;

    while (true) {
        double usage = cpu_usage.getCPUUsage();
        std::cout << "CPU Usage: " << usage << "%" << std::endl;
        sleep(1);  // Atualiza a cada segundo
    }

    return 0;
}
