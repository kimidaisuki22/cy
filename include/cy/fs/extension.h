#pragma once
#include <filesystem>
namespace cy::fs {
std::filesystem::path change_extension(std::filesystem::path file_name,
                                       std::filesystem::path ext_name);
} // namespace cy::fs