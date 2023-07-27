#include "cy/proc/memory.h"
#ifdef _WIN32
#include <Windows.h>
#include <Psapi.h> // For GetProcessMemoryInfo

#else

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
#else
size_t cy::proc::get_current_process_memory_usage() {
  static_assert(false, "Not implemented");
  //   return 0;
}
#endif