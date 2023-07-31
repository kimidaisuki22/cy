#include <cy/proc/executable.h>
#include <iostream>

int main() {
  std::cout << cy::proc::get_executable_path() << std::endl;
  {
    auto s = cy::proc::execute_command("help");

    std::cout << s.size() << " help: ";
    s.resize(80);
    std::cout << s << std::endl;
  }
}