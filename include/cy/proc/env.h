#pragma once

#include <optional>
#include <string>

namespace cy::proc {
std::optional<std::string> get_env(const std::string &env_name);

// If this env is not set, it will print error and throw a exception.
// But do we really need it?
// std::string get_env_or_panic(const std::string &env_name);
}