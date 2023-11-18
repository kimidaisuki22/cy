#include <cy/proc/env.h>
#include <cy/proc/executable.h>


#include <gtest/gtest.h>
#include <string>
#include <cstdlib>

TEST(Proc, get_executable_path) {
  EXPECT_EQ(cy::proc::get_executable_path().filename().stem(), "proc_test");
}
TEST(Proc, env) {
  std::string rand_envname = "WHAT_IS_A_RANDOM_ENV_NAME";
  std::string value = "Test passed!";

  EXPECT_TRUE(!cy::proc::get_env(rand_envname).has_value());
  #ifdef _WIN32
  _putenv_s(rand_envname.c_str(), value.c_str());
  // SetEnvironmentVariableA(rand_envname.c_str(), value.c_str());
  #else
  setenv(rand_envname.c_str(), value.c_str(), true);
  #endif
  EXPECT_TRUE(cy::proc::get_env(rand_envname).has_value());
  EXPECT_EQ(cy::proc::get_env(rand_envname).value(), value);
}
