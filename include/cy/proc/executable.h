#pragma once

#include <filesystem>
namespace cy::proc {
std::filesystem::path get_executable_path();

std::string execute_command(std::string command);
} // namespace cy::proc