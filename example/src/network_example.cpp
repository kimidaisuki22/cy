#include <algorithm>
#include <cy/network/ip.h>
#include <iostream>

int main() {
  auto ips = cy::network::get_all_ip();
  for (auto ip : ips) {
    std::cout << ip << "\n";
  }
}