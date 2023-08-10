#include <cy/proc/executable.h>

#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <string>

#ifndef _WIN32
#include <limits.h>
#include <unistd.h>
#else
#include <Windows.h>
#endif

#ifdef __APPLE__
#include <mach-o/dyld.h>
#endif

#ifdef _WIN32

// std::filesystem::path cy::proc::get_executable_path() {
//   std::string buffer;
//   buffer.resize(10);
//   DWORD ret = GetModuleFileNameA(nullptr, buffer.data(), buffer.size());
//   if (ret < buffer.size()) {
//     buffer.resize(ret);
//     return buffer;
//   }

//   while (GetLastError() == ERROR_INSUFFICIENT_BUFFER) {
//     buffer.resize(buffer.size() * 2);
//     ret = GetModuleFileNameA(nullptr, buffer.data(), buffer.size());
//     if (ret < buffer.size()) {
//       buffer.resize(ret);
//       return buffer;
//     }
//   }
//   return buffer;
// }

std::filesystem::path cy::proc::get_executable_path() {
  // see doc:
  // https://learn.microsoft.com/en-us/windows/win32/api/libloaderapi/nf-libloaderapi-getmodulefilenamea#remarks

  // The global variable _pgmptr is automatically initialized to the full path
  // of the executable file, and can be used to retrieve the full path name of
  // an executable file.
  return _pgmptr;
}

#else
std::filesystem::path cy::proc::get_executable_path() {

  const size_t bufSize = PATH_MAX + 1;
  char dirNameBuffer[bufSize];

#ifdef __APPLE__
  uint32_t size = bufSize;

  if (_NSGetExecutablePath(dirNameBuffer, &size) != 0) {
    // Buffer size is too small.
    return {};
  }
#else  // not __APPLE__
  // Read the symbolic link '/proc/self/exe'.
  const char *linkName = "/proc/self/exe";
  const int ret = int(readlink(linkName, dirNameBuffer, bufSize - 1));

  if (ret == -1) {
    // Permission denied (We must be inetd with this app run as other than
    // root).
    return {};
  }

  dirNameBuffer[ret] = 0; // Terminate the string with a NULL character.
#endif // else not __APPLE__

  return dirNameBuffer;
}

#endif // else not _WIN32
void cy::proc::execute_self(){
  execute_command(get_executable_path().string());
}
