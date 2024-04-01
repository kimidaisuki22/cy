#pragma once
#ifdef  _WIN32
#include <cy/coroutine/simple_generator.h>
#include <winsock2.h>
#include <iphlpapi.h>
namespace cy::network {
// This function is only working on Windows.
cy::coroutine::Simple_generator<PIP_ADAPTER_ADDRESSES> iterate_interface();
}
#endif