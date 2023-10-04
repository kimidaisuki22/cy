#include "cy/fs/extension.h"
#include <cy/fs.h>

#include <gtest/gtest.h>

TEST(Filesytem, replace_file_extension) {
    EXPECT_EQ(cy::fs::change_extension("main.txt", ".cpp"), "main.cpp");
    EXPECT_EQ(cy::fs::change_extension("main.txt", "main.cpp"), "main.cpp");
    EXPECT_EQ(cy::fs::change_extension("main.txt", ".h"), "main.h");

    EXPECT_EQ(cy::fs::change_extension(".config", ".cpp"), ".config.cpp");
    EXPECT_EQ(cy::fs::change_extension(".config", "a.cpp"), ".config.cpp");

    EXPECT_NE(cy::fs::change_extension("main.cpp", ".txt"), "main.cpp");
}
