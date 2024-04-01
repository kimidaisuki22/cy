#pragma once
#include <string>
namespace cy::network {
class Address {
public:
  Address() {}
  explicit Address(const std::string &address) : address_(address) {}
  std::string to_string() const { return address_; }

private:
  std::string address_{};
};
} // namespace cy::network