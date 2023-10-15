#include <cy/fs/collect_files.h>
#include <filesystem>
#include <iostream>
int main(int argc, char **argv) {
  std::filesystem::path path =
      argc > 1 ? argv[1] : std::filesystem::current_path();
  auto files = cy::fs::collect_files_in_dir_non_recursive(path);

  for (auto &file : files) {
    std::cout << file << "\n";
  }
}