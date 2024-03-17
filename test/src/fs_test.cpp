#include "cy/fs/extension.h"
#include <cy/fs.h>
#include <cy/fs/iterate_dir.h>

#include <gtest/gtest.h>

TEST(Filesytem, replace_file_extension) {
    EXPECT_EQ(cy::fs::change_extension("main.txt", ".cpp"), "main.cpp");
    EXPECT_EQ(cy::fs::change_extension("main.txt", "main.cpp"), "main.cpp");
    EXPECT_EQ(cy::fs::change_extension("main.txt", ".h"), "main.h");

    EXPECT_EQ(cy::fs::change_extension(".config", ".cpp"), ".config.cpp");
    EXPECT_EQ(cy::fs::change_extension(".config", "a.cpp"), ".config.cpp");

    EXPECT_NE(cy::fs::change_extension("main.cpp", ".txt"), "main.cpp");
}

TEST(Fs, lazy_collect) {
  size_t count{};
  for (auto file :
       cy::fs::iterate_files_in_dir_non_recursive(".")) {
    auto path = file.path();
    EXPECT_NE(path.string(), "a");
    count++;
  }
  EXPECT_GE(count, 0);
}
TEST(Fs, recursive_iteration) {
  bool hint{};
  auto self = std::filesystem::path(__FILE__);
  for (auto file : cy::fs::iterate_files_in_dir_recursive(
          self.parent_path())) {
   if(std::filesystem::absolute(file) == self){
    hint = true;
   }
  }
  EXPECT_TRUE(hint);
}