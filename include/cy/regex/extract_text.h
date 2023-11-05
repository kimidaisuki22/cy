#pragma once
#include <optional>
#include <string>
#include <string_view>
#include <vector>

namespace cy::regex {

std::optional<std::string>
extract_one_string_from_pattern(const std::string &src,
                                const std::string &pattern);

std::optional<std::vector<std::string>>
extract_strings_from_pattern(const std::string &src,
                             const std::string &pattern);
} // namespace cy::regex