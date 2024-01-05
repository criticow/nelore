file(GLOB_RECURSE SOURCE "${NEL_SOURCE_DIR}/src/*.cpp" "${NEL_SOURCE_DIR}/src/*.hpp")

add_library(nelore ${SOURCE})

find_package(glfw3 CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)
find_package(assimp CONFIG REQUIRED)
find_package(Bullet CONFIG REQUIRED)
find_package(EnTT CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)

target_precompile_headers(nelore PRIVATE nelpch.hpp)

target_link_libraries(${PROJECT_NAME} PUBLIC
  glfw
  glad::glad
  ${BULLET_LIBRARIES}
  glm::glm
  EnTT::EnTT
  assimp::assimp
)

target_include_directories(nelore PUBLIC
  $<BUILD_INTERFACE:${NEL_SOURCE_DIR}/src>
)