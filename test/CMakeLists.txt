project(cy_test)

enable_testing()
find_package(GTest CONFIG REQUIRED)

add_executable(fs_test src/fs_test.cpp)
target_link_libraries(fs_test PRIVATE GTest::gtest GTest::gtest_main GTest::gmock GTest::gmock_main cy)
add_test(AllTestsInMain fs_test)