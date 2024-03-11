#ifndef _WIN32
#include <arpa/inet.h>
#include <netinet/in.h>
#include <string>
#include <sys/socket.h>
namespace cy::network {
std::string socket_addr_to_string_ipv4(sockaddr *current);
std::string socket_addr_to_string_ipv6(sockaddr *current);
std::string socket_addr_to_string(sockaddr *addr);
} // namespace cy::network
#endif