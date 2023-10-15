#pragma once
#include <vector>
#include <filesystem>
namespace cy::fs {
std::vector<std::filesystem::path> collect_files_in_dir_non_recursive(std::filesystem::path path);
} // namespace cy::fs