#pragma once
#include <filesystem>
#include <optional>
#include <span>
#include <string>

namespace cy::io::easy {
std::optional<std::string> read_file_to_buffer(std::filesystem::path filename);

bool write_buffer_to_file(std::span<char> buffer,
                          std::filesystem::path filename);
} // namespace cy::io::easy