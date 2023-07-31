#include <cy/text/to_str.h>

#include <gtest/gtest.h>

TEST(Text, number_unit) {
  EXPECT_EQ(cy::text::to_number_unit_SI(1024), "1K");
  EXPECT_EQ(cy::text::to_number_unit_SI(1025), "1.001K");
  EXPECT_EQ(cy::text::to_number_unit_SI(1024 * 1024), "1M");
  EXPECT_EQ(cy::text::to_number_unit_SI(1024 * 1024 * 1024), "1G");
  EXPECT_EQ(cy::text::to_number_unit_SI(1024ull * 1024 * 1024 * 1024), "1T");
}
int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}