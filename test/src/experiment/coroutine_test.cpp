#include "cy/experiment/coroutine/simple_generator.h"

#include <gtest/gtest.h>
#include <vector>

cy::experiment::coroutine::Simple_generator<int> one_to_ten() {
  for (int i = 0; i <= 10; i++) {
    co_yield i;
  }
}

TEST(Coroutine, simple_coroutine) {
  std::vector<int> a, b;
  for (int i = 0; i <= 10; i++) {
    a.push_back(i);
  }
  for (auto i : one_to_ten()) {
    b.push_back(i);
  }
  EXPECT_EQ(a, b);
}