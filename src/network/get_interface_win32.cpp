#ifdef _WIN32
#include <iostream>
#include <vector>
#include <WinSock2.h>
#include <IPHlpApi.h>

#include "cy/network/interface.h"

namespace cy::network {
std::vector<Interface> get_interfaces() {
    std::vector<Interface> interfaces;

    // Initialize Winsock
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "Failed to initialize Winsock." << std::endl;
        return interfaces;
    }

    // Get adapter addresses
    ULONG bufferSize = 0;
    if (GetAdaptersAddresses(AF_UNSPEC, 0, nullptr, nullptr, &bufferSize) != ERROR_BUFFER_OVERFLOW) {
        std::cerr << "Failed to get adapter addresses buffer size." << std::endl;
        WSACleanup();
        return interfaces;
    }

    std::vector<char> buffer(bufferSize);
    PIP_ADAPTER_ADDRESSES adapterAddresses = reinterpret_cast<PIP_ADAPTER_ADDRESSES>(buffer.data());
    if (GetAdaptersAddresses(AF_UNSPEC, 0, nullptr, adapterAddresses, &bufferSize) != ERROR_SUCCESS) {
        std::cerr << "Failed to get adapter addresses." << std::endl;
        WSACleanup();
        return interfaces;
    }

    // Iterate through adapter addresses and add interfaces
    for (auto adapter = adapterAddresses; adapter != nullptr; adapter = adapter->Next) {
        for (auto address = adapter->FirstUnicastAddress; address != nullptr; address = address->Next) {
            if (address->Address.lpSockaddr->sa_family == AF_INET || address->Address.lpSockaddr->sa_family == AF_INET6) {
                std::string interfaceName(adapter->AdapterName);
                interfaces.push_back(Interface{ interfaceName });
                break;
            }
        }
    }

    WSACleanup();
    return interfaces;
}
} // namespace cy::network
#endif
