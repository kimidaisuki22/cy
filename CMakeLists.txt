cmake_minimum_required(VERSION 3.21.0)
project(cy VERSION 0.0.8)

# set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 20)
option(cy_EXPERIMENT "install library cy" ON)

include(CTest)

add_library(cy STATIC)

# target_compile_options(cy PUBLIC -fsanitize=thread)
# target_link_options(cy PUBLIC -fsanitize=thread)

target_sources(cy PRIVATE
src/fs/extension.cpp
src/fs/collect_files.cpp
src/fs/iterate_dir.cpp

src/proc/memory.cpp
src/proc/env.cpp
src/proc/work_dir.cpp

src/text/process.cpp
src/text/to_str.cpp
src/text/breaker.cpp
src/text/separator_cut.cpp
src/text/time.cpp

src/proc/executable.cpp
src/proc/execute_command.cpp
src/text/process.cpp
src/shell/shell.cpp

src/network/ip_inx.cpp
src/network/ip_win32.cpp
src/network/get_interface_inx.cpp
src/network/get_interface_win32.cpp
src/network/sockaddr_to_string_inx.cpp
src/network/sockaddr_to_string_win32.cpp
src/network/find_ip.cpp
src/network/ifaddrs_iterate.cpp
src/network/adapters_iterate.cpp

src/io/read_to_buffer.cpp
src/io/write_from_buffer.cpp
src/io/mmap.cpp
src/io/easy/file_read_write.cpp

src/memory/raw_arena.cpp

src/regex/extract_text.cpp

src/chrono/convert.cpp

src/iteration/round_robin.cpp

src/concurrency/stop_flag.cpp

src/coroutine/coroutine_scheduler.cpp
src/coroutine/scheduler_pack.cpp
src/coroutine/scheduler_executor.cpp
)
if(cy_EXPERIMENT)

target_sources(cy PRIVATE
src/experiment/empty.cpp

)
endif()

target_include_directories(cy PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)

target_include_directories(cy PRIVATE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/inner-include>)
if(WIN32)
    target_link_libraries(cy PRIVATE ntdll)
endif()


option(cy_BUILD_EXAMPLE "build example for cy" ON)
option(cy_INSTALL "install library cy" ON)
option(cy_BENCHMARK "install library cy" ON)

if(${cy_BUILD_EXAMPLE})
    # add_executable(example example/example.cpp)
    # target_link_libraries(example cy)
    add_subdirectory(example)
endif()

# use ctest build variable to check test.
if(BUILD_TESTING)
    enable_testing()
    add_subdirectory(test)
endif()

if(${cy_BENCHMARK})
    add_subdirectory(benchmark)
endif()

if(${cy_INSTALL})
include(CPack)
include(GNUInstallDirs)
install(TARGETS cy
    EXPORT cy
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION  ${CMAKE_INSTALL_BINDIR}
)
install(EXPORT cy
    FILE cyConfig.cmake
    NAMESPACE cy::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/cy
)
install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

endif()
