#include "cy/network/get_interface.h"
#include <algorithm>
#include <cy/network/ip.h>
#include <iostream>

int main() {
  auto ips = cy::network::get_all_ip();
  for (auto ip : ips) {
    std::cout << ip << "\n";
  }

  for (auto interface : cy::network::get_interfaces()) {
    std::cout << interface.get_name() << "\n";
  }
}