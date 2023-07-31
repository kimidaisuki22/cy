#include "cy/text/to_str.h"
#include <array>
#include <sstream>
#include <stdint.h>
#include <string>
#include <string_view>

namespace {
std::string format_double(double number, int precise) {
  // std::string result = std::to_string(number);
  // auto pos = result.find('.');
  // if(pos != std::string::npos){
  //   result = result.substr(0, pos + precise + 1);
  // }
  // return result;

  std::ostringstream out;
  out.precision(precise);
  out << number;
  return std::move(out).str();
}
} // namespace

std::string cy::text::to_number_unit_SI(uint64_t number) {
  std::array<std::string_view, 5> SI_units = {
      "", "K", "M", "G", "T",
  };
  constexpr uint64_t unit = 1024;
  std::array<uint64_t, 5> numbers;
  auto n = number;
  for (int i = 0; i < numbers.size(); i++) {
    numbers[i] = n % unit;
    n /= unit;
  }
  int level{};
  for (int i = numbers.size() - 1; i >= 0; i--) {
    if (numbers[i] > 0) {
      level = i;
      break;
    }
  }
  double result{};
  if (level > 0) {
    result = numbers[level] + (numbers[level - 1] / static_cast<double>(unit));
  } else {
    result = numbers[level];
  }
  return format_double(result,4) + std::string(SI_units[level]);
}
