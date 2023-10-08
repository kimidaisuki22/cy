#include "cy/memory/raw_arena.h"
#include <gtest/gtest.h>

TEST(raw_arena, runable_test) {
  cy::memory::Raw_arena arena(1024);
  auto i = (int *)arena.alloc(4);
  *i = 42;

  for(int i=0;i<1024;i++){
    auto b = (int*) arena.alloc(4);
    *b = 43;
  }

    EXPECT_EQ(*i, 42);
}
