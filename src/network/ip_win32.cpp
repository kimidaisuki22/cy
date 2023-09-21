#ifdef _WIN32
#include <cy/network/ip.h>
#include <string>
#include <vector>

#include <winsock2.h>
#include <ws2tcpip.h>
#include <iphlpapi.h>

#pragma comment(lib, "Ws2_32.lib")
#pragma comment(lib, "iphlpapi.lib")

namespace cy::network {
std::vector<std::string> get_all_ip() {
  std::vector<std::string> ipAddresses;

  WSADATA wsaData;
  if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
    return ipAddresses;
  }

  PIP_ADAPTER_ADDRESSES adapterAddresses = nullptr;
  ULONG bufferSize = 0;

  if (GetAdaptersAddresses(AF_UNSPEC, GAA_FLAG_INCLUDE_PREFIX, nullptr,
                           adapterAddresses,
                           &bufferSize) == ERROR_BUFFER_OVERFLOW) {
    adapterAddresses =
        reinterpret_cast<IP_ADAPTER_ADDRESSES *>(malloc(bufferSize));
    if (GetAdaptersAddresses(AF_UNSPEC, GAA_FLAG_INCLUDE_PREFIX, nullptr,
                             adapterAddresses, &bufferSize) == NO_ERROR) {
      PIP_ADAPTER_ADDRESSES adapter = adapterAddresses;
      while (adapter) {
        // Process IPv4 addresses
        if (adapter->FirstUnicastAddress) {
          IP_ADAPTER_UNICAST_ADDRESS *unicastAddress =
              adapter->FirstUnicastAddress;
          while (unicastAddress) {
            if (unicastAddress->Address.lpSockaddr->sa_family == AF_INET) {
              char buffer[INET_ADDRSTRLEN];
              inet_ntop(AF_INET,
                        &reinterpret_cast<sockaddr_in *>(
                             unicastAddress->Address.lpSockaddr)
                             ->sin_addr,
                        buffer, INET_ADDRSTRLEN);
              ipAddresses.push_back(buffer);
            }
            unicastAddress = unicastAddress->Next;
          }
        }

        // Process IPv6 addresses
        if (adapter->FirstUnicastAddress) {
          IP_ADAPTER_UNICAST_ADDRESS *unicastAddress =
              adapter->FirstUnicastAddress;
          while (unicastAddress) {
            if (unicastAddress->Address.lpSockaddr->sa_family == AF_INET6) {
              char buffer[INET6_ADDRSTRLEN];
              inet_ntop(AF_INET6,
                        &reinterpret_cast<sockaddr_in6 *>(
                             unicastAddress->Address.lpSockaddr)
                             ->sin6_addr,
                        buffer, INET6_ADDRSTRLEN);
              ipAddresses.push_back(buffer);
            }
            unicastAddress = unicastAddress->Next;
          }
        }

        adapter = adapter->Next;
      }
    }
    free(adapterAddresses);
  }

  WSACleanup();
  return ipAddresses;
}
std::vector<std::string> get_all_ipv4() {
  std::vector<std::string> ipAddresses;

  WSADATA wsaData;
  if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
    return ipAddresses;
  }

  PIP_ADAPTER_INFO adapterInfo = nullptr;
  PIP_ADAPTER_INFO adapter = nullptr;
  DWORD bufferSize = 0;

  if (GetAdaptersInfo(adapterInfo, &bufferSize) == ERROR_BUFFER_OVERFLOW) {
    adapterInfo = reinterpret_cast<IP_ADAPTER_INFO *>(malloc(bufferSize));
    if (GetAdaptersInfo(adapterInfo, &bufferSize) == NO_ERROR) {
      adapter = adapterInfo;
      while (adapter) {
        if (adapter->Type == MIB_IF_TYPE_ETHERNET &&
            adapter->IpAddressList.IpAddress.String[0] != '0') {
          // Skip all 0.0.0.0
          ipAddresses.push_back(adapter->IpAddressList.IpAddress.String);
        }
        adapter = adapter->Next;
      }
    }
    free(adapterInfo);
  }

  WSACleanup();
  return ipAddresses;
}
} // namespace cy::network
#endif