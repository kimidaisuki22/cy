#include <cstddef>
#include <cy/regex/extract_text.h>
#include <optional>
#include <regex>
#include <string>
#include <vector>

namespace cy::regex {
std::optional<std::string>
extract_one_string_from_pattern(const std::string &src,
                                const std::string &pattern) {

  std::regex regex(pattern);
  std::smatch match;

  if (std::regex_search(src, match, regex) && match.size() > 1) {
    return match[1].str();
  }
  return {};
}
std::optional<std::vector<std::string>>
extract_strings_from_pattern(const std::string &src,
                             const std::string &pattern) {
                                std::regex regex(pattern);
  std::smatch match;

  if (std::regex_search(src, match, regex) && match.size() > 1) {
    std::vector<std::string> results;
    for(size_t i{1};i<match.size();i++){
      results.push_back(match[i].str());
    }
    return results;
  }
  return {};
                             }
} // namespace cy::regex