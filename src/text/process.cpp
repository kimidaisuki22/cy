#include "cy/text/separator_cut.h"
#include <cstddef>
#include <cy/text/process.h>

#include <sstream>
#include <string>
#include <string_view>
#include <vector>
std::vector<std::string> cy::text::to_lines(std::string str) {
  std::stringstream ss{std::move(str)};
  std::string line;
  std::vector<std::string> lines;
  while (std::getline(ss, line)) {
    lines.push_back(line);
  }

  return lines;
}
std::string cy::text::trim(std::string str) {
  while (!str.empty() && std::isspace(str.back())) {
    str.pop_back();
  }
  while (!str.empty() && std::isspace(str.front())) {
    str.erase(str.begin());
  }
  return str;
}
std::string cy::text::column(std::string str, int index) {
  std::stringstream ss{std::move(str)};
  std::string result;
  for (int i = 0; i <= index; i++) {
    ss >> result;
  }
  return result;
}
std::string cy::text::take_until(std::string str, char ch) {
  for (size_t i{}; i < str.size(); i++) {
    if (str[i] == ch) {
      str.resize(i);
      break;
    }
  }
  return str;
}
bool cy::text::contains(std::string_view str, std::string_view substr) {
  return str.find(substr) != std::string_view::npos;
}
std::string cy::text::lower(std::string_view str) {
  std::string result;
  result.resize(str.size());
  for (size_t i{}; i < str.size(); i++) {
    result[i] = tolower(str[i]);
  }
  return result;
}
std::string cy::text::upper(std::string_view str) {
  std::string result;
  result.resize(str.size());
  for (size_t i{}; i < str.size(); i++) {
    result[i] = toupper(str[i]);
  }
  return result;
}
std::vector<std::string_view> cy::text::to_lines(std::string_view str) {
  auto buffer = str;
  std::vector<std::string_view> results;

  while (buffer.size()) {
    auto cut_result = separator_cut(buffer, "\n");
    cut_result.front_ = remove_end_new_line_char(cut_result.front_);
    results.push_back(cut_result.front_);
    if (cut_result.back_) {
      buffer = cut_result.back_.value();
    } else {
      break;
    }
  }

  return results;
}
std::string_view cy::text::remove_end_new_line_char(std::string_view str) {
  while (!str.empty()) {
    if (str.back() == '\r' || str.back() == '\n') {
      str.remove_suffix(1);
    } else {
      break;
    }
  }
  return str;
}
