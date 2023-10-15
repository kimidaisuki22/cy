#pragma once
#include <optional>
#include <string>
#include <string_view>

namespace cy::regex {

std::optional<std::string>
extract_one_string_from_pattern(const std::string &src,
                                const std::string &pattern);
} // namespace cy::regex