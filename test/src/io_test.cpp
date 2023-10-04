#include "cy/io/read_to_buffer.h"
#include "cy/io/write_from_buffer.h"

#include <cstring>
#include <fstream>
#include <gtest/gtest.h>
#include <string>

TEST(Io, read_write_buffer) {
  std::string file_name = "a_test_file_name_1289742.txt";
  std::string content = "Hello OK";
  {
    std::ofstream file{file_name};
    EXPECT_TRUE(cy::io::write_from_buffer(content, file));
  }
  {
    std::ifstream file{file_name};
    auto buf = cy::io::read_to_buffer(file);
    EXPECT_EQ(content.size(), buf.size());
    EXPECT_TRUE(memcmp(buf.data(), content.data(), content.size()) == 0);
  }
}