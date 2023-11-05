#include "cy/utils/local_RAII.h"
#include <gtest/gtest.h>

TEST(RAII, local_raii) {
  int i{};
  {
    cy::utils::Local_RAII obj{[&i] { i = 42; }};
    EXPECT_EQ(i, 0);
  }
  EXPECT_EQ(i, 42);
}
