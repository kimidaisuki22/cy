#include <cy/proc/executable.h>
#include <iostream>

int main() { std::cout << cy::proc::get_executable_path() << std::endl; }