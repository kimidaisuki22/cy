#include <cy/network/ip.h>

#include <gtest/gtest.h>

TEST(Network, get_ip_address) {
  auto ips = cy::network::get_all_ip();
  EXPECT_GT(ips.size(), 0);

  for (auto ip : ips) {
    EXPECT_TRUE(!ip.empty());
  }
}
TEST(Network, get_ip_address_V4) {
  auto ips = cy::network::get_all_ipv4();
  EXPECT_GT(ips.size(), 0);

  for (auto ip : ips) {
    EXPECT_TRUE(!ip.empty());
  }
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}