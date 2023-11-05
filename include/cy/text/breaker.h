#pragma once

#include <string_view>
#include <vector>
namespace cy::text::breaker {
std::vector<std::string_view> empty_line_break(std::string_view text);
}