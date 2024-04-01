#ifdef _WIN32
#include <string>
#include <winsock.h>
namespace cy::network {
std::string socket_addr_to_string_ipv4(sockaddr* current);
std::string socket_addr_to_string_ipv6(sockaddr* current);
std::string socket_addr_to_string(sockaddr* current);
} // namespace cy::network
#endif