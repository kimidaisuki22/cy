#include <cy/regex/extract_text.h>
#include <filesystem>
#include <iostream>
int main(int argc, char **argv) {
  std::cout << cy::regex::extract_one_string_from_pattern(
                   "hello:[Alice]", ":\\[(.*)\\]")
                   .value()
            << "\n";
  auto results = cy::regex::extract_strings_from_pattern(
      "hello:[Alice][Bob]", ":\\[(.*)\\]\\[(.*)\\]");
  for (auto r : results.value()) {
    std::cout << r << "\n";
  }
}