#pragma once
#include <cy/experiment/coroutine/simple_generator.h>
#ifndef  _WIN32
namespace cy::network {
// This function is not working on Windows.
cy::experiment::coroutine::Simple_generator<ifaddrs *> iterate_interface();
}
#endif