#include <cy/regex/extract_text.h>
#include <optional>
#include <regex>

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
} // namespace cy::regex