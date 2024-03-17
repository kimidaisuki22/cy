#include <cy/experiment/coroutine/simple_generator.h>
#include <ifaddrs.h>
namespace cy::network {
cy::experiment::coroutine::Simple_generator<ifaddrs *> iterate_interface();
}