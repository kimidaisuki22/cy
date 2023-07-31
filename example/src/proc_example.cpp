#include <algorithm>
#include <cy/proc/executable.h>
#include <cy/text/process.h>
#include <iostream>

int main() {
  std::cout << cy::proc::get_executable_path() << std::endl;
  {
    auto command =
#ifdef _WIN32
        "ipconfig";
#else
        "ip a";
#endif
    auto lines = cy::text::to_lines(cy::proc::execute_command(command));
    std::sort(lines.begin(), lines.end());
    for (auto line : lines) {
      if (cy::text::contains(line, "inet") || cy::text::contains(line, "IPv"))
        std::cout << cy::text::trim(line) << std::endl;
    }
  }
}