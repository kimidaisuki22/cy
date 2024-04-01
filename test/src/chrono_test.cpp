#include <ctime>
#include <cy/chrono/clock_convert.h>
#include <cy/chrono/convert.h>
#include <cy/chrono/to_system_time_point.h>

#include <filesystem>
#include <gtest/gtest.h>
TEST(Chrono, compile_test) {
  auto last_write = std::filesystem::last_write_time(__FILE__);

  auto system_time = cy::chrono::to_system_time_point(last_write);
  auto system_time_2 = cy::chrono::convert_to_clock(last_write);
  EXPECT_EQ(system_time, system_time_2);
  time_t t;
  EXPECT_TRUE(time(&t));

  bool ok{};
  cy::chrono::time_t_to_local_time(t, &ok);
  EXPECT_TRUE(ok);
  cy::chrono::time_t_to_gmt_time(t, &ok);
  EXPECT_TRUE(ok);
}