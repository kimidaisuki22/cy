#include <algorithm>
#include <cy/proc/executable.h>
#include <cy/text/process.h>
#include <iostream>

int main() {
  std::cout << cy::proc::get_executable_path() << std::endl;
  {
    using namespace cy::text;
    using namespace cy::proc;

    auto command =
#ifdef _WIN32
        "ipconfig";
#else
        "ip a";
#endif
    auto lines = to_lines(execute_command(command));
    std::sort(lines.begin(), lines.end());
    for (auto line : lines) {
      if (contains(line, "inet") || contains(line, "IPv")) {
        std::cout << trim(line) << std::endl;
      }
    }
  }
}