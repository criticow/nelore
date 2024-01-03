link_libraries(nelore)

file(GLOB_RECURSE SOURCE "*.cpp" "*.hpp")

add_executable(tests ${SOURCE})