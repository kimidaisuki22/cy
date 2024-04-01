#include "cy/utils/local_RAII.h"
#include <iostream>
#include <vector>
#ifdef _WIN32
#include "detail_include/adapters_iterate.h"
#include <cy/experiment/coroutine/simple_generator.h>

namespace cy::network {
cy::experiment::coroutine::Simple_generator<PIP_ADAPTER_ADDRESSES>
iterate_interface() {

  // Initialize Winsock
  WSADATA wsaData;
  if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
    std::cerr << "Failed to initialize Winsock." << std::endl;
    co_return;
  }
  utils::Local_RAII release_wsa{[] { WSACleanup(); }};

  // Get adapter addresses
  ULONG bufferSize = 0;
  if (GetAdaptersAddresses(AF_UNSPEC, 0, nullptr, nullptr, &bufferSize) !=
      ERROR_BUFFER_OVERFLOW) {
    std::cerr << "Failed to get adapter addresses buffer size." << std::endl;

    co_return;
  }

  std::vector<char> buffer(bufferSize);
  PIP_ADAPTER_ADDRESSES adapterAddresses =
      reinterpret_cast<PIP_ADAPTER_ADDRESSES>(buffer.data());
  if (GetAdaptersAddresses(AF_UNSPEC, 0, nullptr, adapterAddresses,
                           &bufferSize) != ERROR_SUCCESS) {
    std::cerr << "Failed to get adapter addresses." << std::endl;
    co_return;
  }

  // Iterate through adapter addresses and add interfaces
  for (auto adapter = adapterAddresses; adapter != nullptr;
       adapter = adapter->Next) {
    co_yield adapter;
  }

  co_return;
}
} // namespace cy::network
#endif
