#pragma once
#include "cy/coroutine/simple_generator.h"
#include <cstddef>
#include <filesystem>
namespace cy::fs {
coroutine::Simple_generator<std::filesystem::directory_entry>
iterate_files_in_dir_non_recursive(std::filesystem::path path);
// You can check or change value outside to change behavior.
coroutine::Simple_generator<std::filesystem::directory_entry>
iterate_files_in_dir_recursive(std::filesystem::path path,
                                   size_t &&depth = {},
                                   bool &&jump_out_this_dir = {});
} // namespace cy::experiment::fs