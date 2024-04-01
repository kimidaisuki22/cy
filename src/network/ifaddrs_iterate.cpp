#ifndef _WIN32
#include "detail_include/ifaddrs_iterate.h"
#include <cy/coroutine/simple_generator.h>
#include <ifaddrs.h>
namespace cy::network {
cy::coroutine::Simple_generator<ifaddrs *> iterate_interface() {
  struct ifaddrs *ifap;
  if (getifaddrs(&ifap) == -1) {
    // std::cerr << "Error getting network interface information." << std::endl;
    co_return;
  }

  struct ifaddrs *current = ifap;
  while (current != nullptr) {
    co_yield current;
    current = current->ifa_next;
  }

  freeifaddrs(ifap);
  co_return;
}
} // namespace cy::network
#endif
