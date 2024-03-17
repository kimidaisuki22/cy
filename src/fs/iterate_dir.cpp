#include "cy/utils/local_RAII.h"
#include <cy/experiment/fs/iterate_dir.h>
#include <filesystem>
cy::experiment::coroutine::Simple_generator<std::filesystem::directory_entry>
cy::experiment::fs::iterate_files_in_dir_non_recursive(
    std::filesystem::path path) {
  std::filesystem::directory_iterator iter{path}, end;
  while (iter != end) {
    co_yield *iter;
    ++iter;
  }
}
cy::experiment::coroutine::Simple_generator<std::filesystem::directory_entry>
cy::experiment::fs::iterate_files_in_dir_recursive(std::filesystem::path path,
                                                   size_t &&depth,
                                                   bool &&jump_out_this_dir) {
  depth++;
  utils::Local_RAII decrease_depth{[&depth] { depth--; }};
  std::filesystem::directory_iterator iter{path}, end;
  // output self first.
  co_yield std::filesystem::directory_entry{path};
  if (jump_out_this_dir) {
    jump_out_this_dir = false;
    co_return;
  }

  while (iter != end) {
    auto entry = *iter;
    if (entry.is_directory()) {
      for (auto entry : iterate_files_in_dir_recursive(
               entry.path(), std::move(depth), std::move(jump_out_this_dir))) {
        co_yield entry;
      }
    } else {
      co_yield entry;
      if (jump_out_this_dir) {
        jump_out_this_dir = false;
      }
    }

    ++iter;
  }
}
