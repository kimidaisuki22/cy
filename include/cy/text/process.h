#pragma once
#include <string>
#include <string_view>
#include <vector>

namespace cy::text {

std::vector<std::string> to_lines(std::string str);

std::string trim(std::string str);
std::string column(std::string str, int index);

std::string take_until(std::string str, char ch);
bool contains(std::string_view str, std::string_view substr);

} // namespace cy::text