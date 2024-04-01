#pragma once
#ifndef  _WIN32
#include <cy/experiment/coroutine/simple_generator.h>
#include <ifaddrs.h>
namespace cy::network {
// This function is not working on Windows.
cy::experiment::coroutine::Simple_generator<ifaddrs *> iterate_interface();
}
#endif