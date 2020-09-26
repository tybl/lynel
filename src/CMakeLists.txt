################################################################################
# License: The Unlicense (https://unlicense.org)
################################################################################

add_executable(example)
target_link_libraries(example PRIVATE compiler_settings)
target_sources(example PRIVATE example/main.cpp)
