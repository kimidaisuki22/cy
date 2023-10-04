#include <cy/text/to_str.h>
#include <cy/text/process.h>

#include <gtest/gtest.h>

TEST(Text, number_unit) {
  EXPECT_EQ(cy::text::to_number_unit_SI(1024), "1K");
  EXPECT_EQ(cy::text::to_number_unit_SI(1025), "1.001K");
  EXPECT_EQ(cy::text::to_number_unit_SI(1024 * 1024), "1M");
  EXPECT_EQ(cy::text::to_number_unit_SI(1024 * 1024 * 1024), "1G");
  EXPECT_EQ(cy::text::to_number_unit_SI(1024ull * 1024 * 1024 * 1024), "1T");
}
TEST(Text, lower) {
  EXPECT_STREQ(cy::text::lower("abc").c_str(), "abc");
  EXPECT_STREQ(cy::text::lower("aBC").c_str(), "abc");
  EXPECT_STREQ(cy::text::lower("ABC").c_str(), "abc");
  EXPECT_STREQ(cy::text::lower("ABC89 234 8").c_str(), "abc89 234 8");
  EXPECT_STREQ(cy::text::lower("").c_str(), "");
}
TEST(Text, upper) {
  EXPECT_STREQ(cy::text::upper("abc").c_str(), "ABC");
  EXPECT_STREQ(cy::text::upper("aBc").c_str(), "ABC");
  EXPECT_STREQ(cy::text::upper("").c_str(), "");
  EXPECT_STREQ(cy::text::upper("1389").c_str(), "1389");
}
