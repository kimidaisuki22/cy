#ifndef _WIN32
#include <arpa/inet.h>
#include <cstdlib>
#include <cstring>
#include <cy/network/ip.h>
#include <ifaddrs.h>
#include <iostream>
#include <netinet/in.h>
#include <vector>


namespace cy::network {

std::vector<std::string> get_all_ipv4() {
  std::vector<std::string> ipAddresses;

  struct ifaddrs *ifap;
  if (getifaddrs(&ifap) == -1) {
    std::cerr << "Error getting network interface information." << std::endl;
    return ipAddresses;
  }

  struct ifaddrs *current = ifap;
  while (current != nullptr) {
    if (current->ifa_addr != nullptr &&
        current->ifa_addr->sa_family == AF_INET) {
      struct sockaddr_in *addr =
          reinterpret_cast<struct sockaddr_in *>(current->ifa_addr);
      char buffer[INET_ADDRSTRLEN];
      if (inet_ntop(AF_INET, &(addr->sin_addr), buffer, INET_ADDRSTRLEN) !=
          nullptr) {
        ipAddresses.push_back(buffer);
      }
    }
    current = current->ifa_next;
  }

  freeifaddrs(ifap);
  return ipAddresses;
}
std::vector<std::string> get_all_ip() {
    std::vector<std::string> ipAddresses;

    struct ifaddrs* ifap;
    if (getifaddrs(&ifap) == -1) {
        std::cerr << "Error getting network interface information." << std::endl;
        return ipAddresses;
    }

    struct ifaddrs* current = ifap;
    while (current != nullptr) {
        if (current->ifa_addr != nullptr) {
            if (current->ifa_addr->sa_family == AF_INET) {
                struct sockaddr_in* addr = reinterpret_cast<struct sockaddr_in*>(current->ifa_addr);
                char buffer[INET_ADDRSTRLEN];
                if (inet_ntop(AF_INET, &(addr->sin_addr), buffer, INET_ADDRSTRLEN) != nullptr) {
                    ipAddresses.push_back(buffer);
                }
            } else if (current->ifa_addr->sa_family == AF_INET6) {
                struct sockaddr_in6* addr6 = reinterpret_cast<struct sockaddr_in6*>(current->ifa_addr);
                char buffer[INET6_ADDRSTRLEN];
                if (inet_ntop(AF_INET6, &(addr6->sin6_addr), buffer, INET6_ADDRSTRLEN) != nullptr) {
                    ipAddresses.push_back(buffer);
                }
            }
        }
        current = current->ifa_next;
    }

    freeifaddrs(ifap);
    return ipAddresses;
}

} // namespace cy::network
#endif