cmake_minimum_required(VERSION 3.20)

set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake")
set(CMAKE_CXX_STANDARD 20)
set(NEL_SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR})

project(nelore)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "Debug")
endif()

option(NEL_BUILD_TESTS "Build nelore engine tests" ON)

add_subdirectory(src)
if(NEL_BUILD_TESTS)
  add_subdirectory(tests)
endif()