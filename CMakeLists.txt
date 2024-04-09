cmake_minimum_required(VERSION 3.14)
project(0xFF)
set(CMAKE_CXX_STANDARD 20)
enable_testing()

# Set the path to the vcpkg toolchain file
set(VCPKG_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/vcpkg)
set(CMAKE_TOOLCHAIN_FILE ${VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake CACHE STRING "")

# Include vcpkg CMake integration
include(${VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake)

# Find vcpkg packages
find_package(CURL REQUIRED)

if(CMAKE_C_COMPILER_ID STREQUAL "MSVC")
    set(CMAKE_CXX_FLAGS "/WX /W4 /DWIN32 /D_WINDOWS /GR /EHsc /utf-8")
    set(CMAKE_CXX_FLAGS_DEBUG "/Zi /Ob0 /Od /RTC1 /Zi")
    set(CMAKE_CXX_FLAGS_RELEASE "/Ox /Ob2 /DNDEBUG")
elseif(CMAKE_C_COMPILER_ID STREQUAL "GNU" OR CMAKE_C_COMPILER_ID STREQUAL "Clang")
    set(CMAKE_CXX_FLAGS "-Wall -Werror -Wfatal-errors -Wold-style-cast -Wextra -pedantic")
    set(CMAKE_CXX_FLAGS_DEBUG "-g")
    set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG")

    if(CMAKE_C_COMPILER_ID STREQUAL "Clang")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
    endif()
else()
    message(FATAL_ERROR "Unable to identify compiler.")
endif()

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY $<1:${CMAKE_BINARY_DIR}/bin/${CMAKE_BUILD_TYPE}>)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY $<1:${CMAKE_BINARY_DIR}/bin/${CMAKE_BUILD_TYPE}>)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY $<1:${CMAKE_BINARY_DIR}/bin/${CMAKE_BUILD_TYPE}>)

file(GLOB_RECURSE SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)
add_executable(${PROJECT_NAME} src/main.cpp)
target_link_libraries(${PROJECT_NAME} CURL::libcurl)

add_subdirectory(tests)
