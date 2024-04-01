#pragma once
#include "cy/network/address.h"
#include "cy/network/interface.h"
#include <vector>
namespace cy::network {
Address find_ipv4_for_interface(const Interface &interface);
Address find_ipv6_for_interface(const Interface &interface);
std::vector<Address> find_addresses_for_interface(const Interface &interface);
}