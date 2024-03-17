#include "cy/network/address.h"
#include "detail_include/ifaddrs_iterate.h"
#include "detail_include/sockaddr_to_string_inx.h"
#include <cy/network/find_ip.h>
#include <sys/socket.h>
#include <vector>
namespace {
cy::network::Address
find_address_family_for_interface(const cy::network::Interface &interface,
                                  int family_flag) {

  for (auto current : cy::network::iterate_interface()) {
    if (current->ifa_addr != nullptr &&
        current->ifa_addr->sa_family == family_flag &&
        current->ifa_name == interface.get_name()) {
      return cy::network::Address{
          cy::network::socket_addr_to_string(current->ifa_addr)};
    }
    current = current->ifa_next;
  }

  return {};
}
} // namespace
cy::network::Address
cy::network::find_ipv6_for_interface(const Interface &interface) {
  return find_address_family_for_interface(interface, AF_INET6);
}
cy::network::Address
cy::network::find_ipv4_for_interface(const Interface &interface) {
  return find_address_family_for_interface(interface, AF_INET);
}
std::vector<cy::network::Address>
cy::network::find_addresses_for_interface(const Interface &interface) {
  std::vector<Address> addresses{};
  auto addr = find_ipv4_for_interface(interface);
  if (!addr.to_string().empty()) {
    addresses.push_back(addr);
  }
  auto addr6 = find_ipv6_for_interface(interface);
  if (!addr6.to_string().empty()) {
    addresses.push_back(addr6);
  }
  return addresses;
}
