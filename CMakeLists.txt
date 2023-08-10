cmake_minimum_required(VERSION 3.21.0)
project(cy VERSION 0.0.1)

# set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 20)

include(CTest)

add_library(cy STATIC)

target_sources(cy PRIVATE
src/fs/extension.cpp
src/proc/memory.cpp
src/text/to_str.cpp
src/proc/executable.cpp
src/proc/execute_command.cpp
src/text/process.cpp
)

target_include_directories(cy PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>)


option(cy_BUILD_EXAMPLE "build example for cy" ON)
option(cy_INSTALL "install library cy" ON)

if(${cy_BUILD_EXAMPLE})
    # add_executable(example example/example.cpp)
    # target_link_libraries(example cy)
    add_subdirectory(example)
endif()

# use ctest build variable to check test.
if(BUILD_TESTING)
    add_subdirectory(test)
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
