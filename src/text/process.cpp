#include <cy/text/process.h>

#include <sstream>
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
