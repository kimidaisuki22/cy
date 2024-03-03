#pragma once
#include <string_view>
#include <string>

namespace cy::network {
class Interface {
public:
  Interface(std::string_view name) : name_{std::string{name}} {}
  const std::string &get_name() const { return name_; }

private:
  std::string name_;
};
} // namespace cy::network