#include "cy/text/process.h"
#include <cy/text/breaker.h>
#include <string_view>
#include <vector>
std::vector<std::string_view>
cy::text::breaker::empty_line_break(std::string_view text) {
  std::vector<std::string_view> results;

  auto lines = to_lines(text);
  std::optional<std::string_view> current;

  for (auto l : lines) {
    if (l.empty()) {
      if (current) {
        results.push_back(current.value());
      }
      current = {};
    } else {
      if (current) {
        current = std::string_view{current->data(),
                                   l.size() + (l.data() - current->data())};
      } else {
        current = l;
      }
    }
    if (current) {
      results.push_back(current.value());
    }
    return results;
  }

  return results;
}
