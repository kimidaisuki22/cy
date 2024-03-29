#pragma once
#include <string>
#include <string_view>
#include <vector>

namespace cy::text {

std::vector<std::string> to_lines_str(std::string str);
std::vector<std::string_view> to_lines(std::string_view str);

std::string trim_str(std::string str);
std::string_view trim(std::string_view str);
std::string_view l_trim(std::string_view str, char charater = ' ');
std::string_view r_trim(std::string_view str, char charater = ' ');
std::string column(std::string str, int index);

std::string take_until(std::string str, char ch);
bool contains(std::string_view str, std::string_view substr);
std::string upper(std::string_view str);
std::string lower(std::string_view str);

std::string_view remove_end_new_line_char(std::string_view str);

} // namespace cy::text