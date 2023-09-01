#pragma once

#include <filesystem>

namespace cy::shell {
// show a file in file explorer with highlight
void show(const std::filesystem::path &path);

// open a file with default program
void open(const std::filesystem::path &path);

} // namespace cy::shell