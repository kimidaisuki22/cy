project(cy_test)

find_package(GTest CONFIG)

if(NOT GTest_DIR)
return()
endif()

include(GoogleTest)
enable_testing()

set(LIB_MIX  GTest::gtest GTest::gtest_main cy)


function(add_test_executable name)
    add_executable(${name} ${ARGN})
    target_link_libraries(${name} PRIVATE ${LIB_MIX})
    # add_test(
    #     NAME ${name}
    #     COMMAND $<TARGET_FILE:${name}>)

    gtest_add_tests(TARGET ${name} SKIP_DEPENDENCY) # SKIP_DEPENDENCY will not add new test function to test list, but it prevent re-configure every modify for test source file.

    # add_test(NAME ${name} COMMAND ${name}) // simple way but give less info.
endfunction()

add_test_executable(process_test src/memory_test.cpp)
add_test_executable(filesystem_test src/fs_test.cpp)
add_test_executable(text_test src/text_test.cpp)
add_test_executable(proc_test src/proc_test.cpp)
add_test_executable(network_test src/network_test.cpp)
add_test_executable(io_test src/io_test.cpp)
add_test_executable(raii_test src/raii_test.cpp)
add_test_executable(raw_arena_test src/raw_arena_test.cpp)
add_test_executable(tpl_pod_test src/tpl_pod_test.cpp)
add_test_executable(coroutine_test src/coroutine_test.cpp)
add_test_executable(ext_fs_test src/experiment/fs_test.cpp)
# add_test_executable(axx_test src/axx_test.cpp)