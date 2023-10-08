#include <cy/text/separator_cut.h>
cy::text::Separator_cut_result
cy::text::separator_cut(std::string_view src, std::string_view separator) {
  Separator_cut_result result;
  auto separator_position = src.find(separator);
  if (separator_position == decltype(src)::npos) {
    result.front_ = src;
  } else {
    result.front_ = src.substr(0, separator_position);
    result.back_ = src.substr(separator_position + separator.size());
  }
  return result;
}
