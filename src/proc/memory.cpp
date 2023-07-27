#include "cy/proc/memory.h"
#ifdef _WIN32
#include <Windows.h>
#include <Psapi.h> // For GetProcessMemoryInfo

#else
#include <iostream>
#include <fstream>
#include <string>
#endif
#ifdef _WIN32
size_t cy::proc::get_current_process_memory_usage() {
  PROCESS_MEMORY_COUNTERS_EX memory_counter;
  GetProcessMemoryInfo(
      GetCurrentProcess(),
      reinterpret_cast<PROCESS_MEMORY_COUNTERS *>(&memory_counter),
      sizeof(memory_counter));
  return memory_counter.PrivateUsage;
}
#elif __linux__
namespace {
  // Function to get the current memory usage of a specific process in KB
unsigned long long GetProcessMemoryUsage(int pid) {
    std::ifstream statm_file("/proc/" + std::to_string(pid) + "/statm");
    if (!statm_file) {
        std::cerr << "Error: Could not open statm file for process " << pid << std::endl;
        return 0;
    }

    unsigned long long size, resident, shared, text, lib, data, dt;
    statm_file >> size >> resident >> shared >> text >> lib >> data >> dt;

    return resident; // Return resident set size (RSS) in KB
}
// Function to get system-wide memory usage in KB
unsigned long long GetSystemMemoryUsage() {
    std::ifstream meminfo_file("/proc/meminfo");
    if (!meminfo_file) {
        std::cerr << "Error: Could not open meminfo file" << std::endl;
        return 0;
    }

    std::string line;
    unsigned long long totalMemory = 0;
    while (std::getline(meminfo_file, line)) {
        if (line.compare(0, 8, "MemTotal") == 0) {
            size_t startPos = line.find(':') + 1;
            size_t endPos = line.find("kB");
            totalMemory = std::stoull(line.substr(startPos, endPos - startPos));
            break;
        }
    }

    return totalMemory; // Return total memory in KB
}
}
size_t cy::proc::get_current_process_memory_usage() {
  return GetProcessMemoryUsage(getpid());
}
#else
size_t cy::proc::get_current_process_memory_usage() {
  static_assert(false, "Not implemented");
  //   return 0;
}
#endif