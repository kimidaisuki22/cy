#include <string>
#ifdef _WIN32
#include "detail_include/sockaddr_to_string_win32.h"
#include "ip2string.h"
#include <winsock.h>
namespace cy::network {

std::string socket_addr_to_string_ipv6(sockaddr *current) {
  std::string buf;
  buf.resize(46);
  // hack ?
  RtlIpv6AddressToStringA((const in6_addr *)&(current->sa_data[2]), buf.data());
  return buf.c_str();
}
std::string socket_addr_to_string_ipv4(sockaddr *current) {
  std::string buf;
  buf.resize(16);
  // hack ?
  // try getnameinfo: https://learn.microsoft.com/en-us/windows/win32/api/ws2tcpip/nf-ws2tcpip-getnameinfo
  RtlIpv4AddressToStringA((const in_addr *)&(current->sa_data[2]), buf.data());
  return buf.c_str();
}
std::string socket_addr_to_string(sockaddr *current) {
  if (current->sa_family == AF_INET) {
    return socket_addr_to_string_ipv4(current);
  } else {
    return socket_addr_to_string_ipv6(current);
  }
}
} // namespace cy::network
#endif