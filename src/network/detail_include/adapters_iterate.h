#pragma once
#include <cy/experiment/coroutine/simple_generator.h>
#ifdef  _WIN32
#include <winsock2.h>
#include <iphlpapi.h>
namespace cy::network {
// This function is only working on Windows.
cy::experiment::coroutine::Simple_generator<PIP_ADAPTER_ADDRESSES> iterate_interface();
}
#endif