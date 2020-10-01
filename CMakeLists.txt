################################################################################
# License: The Unlicense (https://unlicense.org)
################################################################################
cmake_minimum_required(VERSION 3.14) # FetchContent_MakeAvailable

project(lynel
  VERSION 0.0.1
  DESCRIPTION "A library for small, dense matrices and vectors"
  LANGUAGES CXX)

option(BUILD_PROJECT_TESTS "Build and run tests as a subproject" OFF)

set(IS_ROOT_PROJECT CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
if(IS_ROOT_PROJECT)
  include(CTest)
endif()
include(FetchContent)
include(util/cmake/compiler_settings.cmake)
include(util/cmake/Linters.cmake)

if(IS_ROOT_PROJECT OR BUILD_PROJECT_TESTS)
  add_subdirectory(test)
endif()
