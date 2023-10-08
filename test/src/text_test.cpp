#include "cy/text/breaker.h"
#include "cy/text/separator_cut.h"
#include <cy/text/to_str.h>
#include <cy/text/process.h>

#include <gtest/gtest.h>
#define STR_EQ(a, b) EXPECT_STREQ(std::string(a).c_str(), std::string(b).c_str())

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

TEST(Text, separator_cut){
  auto result = cy::text::separator_cut("Hello: Friend", ":");
  EXPECT_TRUE(result.back_);

  STR_EQ(result.front_, "Hello");
  STR_EQ(result.back_.value(), " Friend");
}

TEST(Text, separator_cut_not_found){
  auto result = cy::text::separator_cut("Hello", ":");
  EXPECT_TRUE(!result.back_);

  STR_EQ(result.front_, "Hello");
}

TEST(Text, separator_cut_empty){
  auto result = cy::text::separator_cut("Hello:", ":");
  EXPECT_TRUE(result.back_);

  STR_EQ(result.front_, "Hello");
  STR_EQ(result.back_.value(), "");
}

TEST(Text, to_lines_string_view){
  auto result = cy::text::to_lines("Hello:");

  EXPECT_EQ(result.size(), 1);
  STR_EQ(result[0],"Hello:");

  result = cy::text::to_lines("A\nb\n\nC");
  EXPECT_EQ(result.size(), 4);
  STR_EQ(result[0], "A");
  STR_EQ(result[1], "b");
  STR_EQ(result[2], "");
  STR_EQ(result[3], "C");
}

TEST(Text, empty_line_break){
  auto txt = "abc\nd\n\nfun\n";
  auto blocks = cy::text::breaker::empty_line_break(txt);

  EXPECT_EQ(blocks.size(), 2);

  STR_EQ(blocks[0], "abc\nd");
  STR_EQ(blocks[1], "fun");
}