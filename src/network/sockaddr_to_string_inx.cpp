#ifndef _WIN32
#include <arpa/inet.h>
#include <netinet/in.h>
#include <string>
#include <sys/socket.h>
namespace cy::network {
std::string socket_addr_to_string_ipv4(sockaddr *current) {
  struct sockaddr_in *addr = reinterpret_cast<struct sockaddr_in *>(current);
  char buffer[INET_ADDRSTRLEN];
  if (inet_ntop(AF_INET, &(addr->sin_addr), buffer, INET_ADDRSTRLEN) !=
      nullptr) {
    return buffer;
  }
  return {};
}
std::string socket_addr_to_string_ipv6(sockaddr *current) {
  struct sockaddr_in6 *addr6 = reinterpret_cast<struct sockaddr_in6 *>(current);
  char buffer[INET6_ADDRSTRLEN];
  if (inet_ntop(AF_INET6, &(addr6->sin6_addr), buffer, INET6_ADDRSTRLEN) !=
      nullptr) {
    return buffer;
  }
  return {};
}
std::string socket_addr_to_string(sockaddr *addr) {
  auto family = addr->sa_family;
  if (family == AF_INET) {
    return socket_addr_to_string_ipv4(addr);
  } else if (family == AF_INET6) {
    return socket_addr_to_string_ipv6(addr);
  }
  return {};
}
} // namespace cy::network
#endif