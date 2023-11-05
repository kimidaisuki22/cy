#include <cy/fs/collect_files.h>
#include <vector>

#include <filesystem>
namespace cy::fs {
std::vector<std::filesystem::path>
collect_files_in_dir_non_recursive(std::filesystem::path path) {
  return std::vector<std::filesystem::path>{
      std::filesystem::directory_iterator{path}, {}};
}
} // namespace cy::fs