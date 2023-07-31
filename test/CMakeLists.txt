project(cy_test)

enable_testing()
find_package(GTest CONFIG REQUIRED)
include(GoogleTest)


set(LIB_MIX  GTest::gtest GTest::gtest_main GTest::gmock GTest::gmock_main cy)


function(add_test_executable name)
    add_executable(${name} ${ARGN})
    target_link_libraries(${name} PRIVATE ${LIB_MIX})
    # add_test(
    #     NAME ${name}
    #     COMMAND $<TARGET_FILE:${name}>)

    gtest_discover_tests(${name})
endfunction()

add_test_executable(process src/memory_test.cpp)
add_test_executable(filesystem src/fs_test.cpp)
add_test_executable(text src/text_test.cpp)
