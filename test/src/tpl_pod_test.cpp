#include "cy/tpl/pod_compare.h"
#include "cy/tpl/pod_write.h"
#include <cy/tpl/pod_copy.h>
#include <gtest/gtest.h>
#include <iostream>

TEST(Template, Pod_copy) {
  int src[4]{1, 2, 4, 5};
  int dest[4]{};
  tpl::pod_copy_slice<4, 4>(src, dest);
  EXPECT_FALSE(tpl::pod_is_same(src, dest));
  EXPECT_EQ(dest[0], 0);
  EXPECT_EQ(dest[1], 2);
  EXPECT_EQ(dest[2], 0);
  EXPECT_EQ(dest[3], 0);

  tpl::pod_copy(src, dest);
  EXPECT_TRUE(tpl::pod_is_same(src, dest));
  for(int i=0;i<4;i++){
    EXPECT_EQ(src[i], dest[i]);
  }
}
TEST(Template, Pod_write) {
  int numbers[3] = {0,1,2};

  tpl::pod_write(std::cout, numbers);
  class Writable{
    public:
    void write(const char*,size_t){

    }
  };
  Writable w;
  tpl::pod_write(w, numbers);
}