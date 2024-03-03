#ifndef _WIN32
#include <sys/socket.h>
#include <arpa/inet.h>
#include <cstdlib>
#include <cstring>
#include <cy/network/ip.h>
#include <ifaddrs.h>
#include <iostream>
#include <netinet/in.h>
#include <vector>

#include "cy/network/interface.h"
#include <vector>
namespace cy::network {
std::vector<Interface> get_interfaces() {
    std::vector<Interface> interfaces;

  struct ifaddrs *ifap;
  if (getifaddrs(&ifap) == -1) {
    std::cerr << "Error getting network interface information." << std::endl;
    return {};
  }

  struct ifaddrs *current = ifap;
  while (current != nullptr) {
    if (current->ifa_addr != nullptr && current->ifa_addr->sa_family == AF_PACKET) {
       interfaces.push_back(Interface{current->ifa_name});
    }
    current = current->ifa_next;
  }

  freeifaddrs(ifap);
  return interfaces;
}

} // namespace cy::network
#endif