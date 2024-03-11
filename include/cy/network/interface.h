#pragma once
#include "cy/network/address.h"
#include <string>
#include <string_view>

namespace cy::network {
class Interface {
public:
  Interface(std::string_view name, Address address = {})
      : name_{std::string{name}}, address_(address) {}
  const std::string &get_name() const { return name_; }
  const Address &get_address() const { return address_; }

private:
  std::string name_;
  Address address_;
};
} // namespace cy::network