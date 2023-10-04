#include <cy/proc/executable.h>

#include <gtest/gtest.h>

TEST(Proc, get_executable_path) {
  EXPECT_EQ(cy::proc::get_executable_path().filename().stem(), "proc_test");
}
