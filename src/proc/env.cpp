#define _CRT_SECURE_NO_WARNINGS
#include <cy/proc/env.h>
#include <cstdlib>
#include <string>
std::optional<std::string> cy::proc::get_env(const std::string &env_name) {
  auto env = std::getenv(env_name.c_str());
  if (!env) {
    return {};
  }
  return std::string{env};
}
// std::string cy::proc::get_env_or_panic(const std::string &env_name) {}
