#include "cy/network/address.h"
#ifndef _WIN32
#include <arpa/inet.h>
#include <cstdlib>
#include <cstring>
#include <cy/network/ip.h>
#include <ifaddrs.h>
#include <iostream>
#include <netinet/in.h>
#include <string>
#include <sys/socket.h>
#include <vector>

#include "cy/network/interface.h"
#include "detail_include/sockaddr_to_string_inx.h"
#include <vector>
namespace cy::network {
std::vector<Interface> get_interfaces() {
  std::vector<Interface> interfaces;

  struct ifaddrs *ifap;
  if (getifaddrs(&ifap) == -1) {
    std::cerr << "Error getting network interface information." << std::endl;
    return {};
  }
  std::vector<int> family_set{};
// On macos
#ifdef __APPLE__
  // AF_LINK; has too much device that don't have an IP address.
  family_set.push_back(AF_INET);
  family_set.push_back(AF_INET6);
#else
  family_set.push_back(AF_PACKET);
#endif
  auto has_flag = [&family_set](int flag) {
    for (auto f : family_set) {
      if (f == flag) {
        return true;
      }
    }
    return false;
  };
  struct ifaddrs *current = ifap;
  while (current != nullptr) {
    if (current->ifa_addr != nullptr &&
        has_flag(current->ifa_addr->sa_family)) {
      interfaces.push_back(
          Interface{current->ifa_name,
                    Address{socket_addr_to_string(current->ifa_addr)}});
    }
    current = current->ifa_next;
  }

  freeifaddrs(ifap);
  return interfaces;
}

} // namespace cy::network
#endif