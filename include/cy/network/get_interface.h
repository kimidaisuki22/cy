#pragma once


#include "cy/network/interface.h"
#include <vector>
namespace cy::network {
std::vector<Interface> get_interfaces();
} // namespace cy::network