#include "cy/experiment/fs/iterate_dir.h"

#include <cstddef>
#include <filesystem>
#include <gtest/gtest.h>

TEST(Fs, lazy_collect) {
  size_t count{};
  for (auto file :
       cy::experiment::fs::iterate_files_in_dir_non_recursive(".")) {
    auto path = file.path();
    EXPECT_NE(path.string(), "a");
    count++;
  }
  EXPECT_GE(count, 0);
}
TEST(Fs, recursive_iteration) {
  bool hint{};
  auto self = std::filesystem::path(__FILE__);
  for (auto file : cy::experiment::fs::iterate_files_in_dir_recursive(
          self.parent_path())) {
   if(std::filesystem::absolute(file) == self){
    hint = true;
   }
  }
  EXPECT_TRUE(hint);
}