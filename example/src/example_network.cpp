#include "cy/network/find_ip.h"
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
    std::cout << interface.get_name() << ": "
              << cy::network::find_ipv4_for_interface(interface).to_string()
              << "\n";
  }
}