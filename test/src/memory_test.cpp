#include "cy/proc.h"

#include <gtest/gtest.h>

TEST(Process, get_current_process_memory_usage) {
    EXPECT_GT(cy::proc::get_current_process_memory_usage(), 0);
}