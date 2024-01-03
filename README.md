## Dependencies

I am using vcpkg to install the dependencies used on this project.

```
vcpkg install glm entt glad glfw3 assimp stb bullet3 --triplet x64-windows
```

The toolchain is being specified in the root [CMakeLists.txt](CMakeLists.txt) file.

``` cmake
...
set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake")
...
```

The linking is being done in the [src/CMakeLists.txt](src/CMakeLists.txt) as PUBLIC so it could be available for projects using my nelore lib.

``` cmake
...
# Locating packages installed globally via vcpkg
find_package(glfw3 CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)
find_package(assimp CONFIG REQUIRED)
find_package(Bullet CONFIG REQUIRED)
find_package(EnTT CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)

# Linking vcpkg installed packages
target_link_libraries(nelore PUBLIC
  glfw
  EnTT::EnTT
  glm::glm
  glad::glad
  assimp::assimp
  ${BULLET_LIBRARIES}
)
...
```

## Usage

```
git submodule add https://github.com/criticow/nelore.git 
git submodule update --init --recursive
```

## CMakeLists.txt example

``` cmake
cmake_minimum_required(VERSION 3.20)

# cpp dialect/standard
set(CMAKE_CXX_STANDARD 20)

# dependencies manager toolchain
set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake")

project(game CXX)

# Include all the cpp and hpp files from the src folder, src folder should be created or this should be altered
file(GLOB_RECURSE SOURCE "src/*.cpp" "src/*.hpp")

add_executable(${PROJECT_NAME} ${SOURCE})

# disable tests building
set(NEL_BUILD_TESTS OFF)

add_subdirectory(nelore)

# linking and including lib directories
target_link_libraries(${PROJECT_NAME} PRIVATE nelore)
target_link_directories(${PROJECT_NAME} PRIVATE nelore/src)

# nelore/data folder should be copied for default shaders, models, textures...
set(DATA_DESTINATION ${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE}/data)

# postbuild command to copy the data folder
add_custom_command(
  TARGET ${PROJECT_NAME} POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_directory
  ${CMAKE_SOURCE_DIR}/nelore/data ${DATA_DESTINATION}
)

add_custom_target(
  copy_data_folder ALL
  DEPENDS ${DATA_DESTINATION}
)
```

## Entry point example

``` cpp
#include <nel/nel.hpp>

int main()
{
  Engine engine(1280, 720, "Game", true);
  engine.run();
  return 0;
}
```

## Game class example

game.hpp
``` cpp
#pragma once

#include <nel/nel.hpp>

class Game : public Engine
{
  public:
  Game(int width, int height, const char *title, bool centered) : Engine(width, height, title, centered){};
  // This method is called in the end of the main update
  void onUpdate() override;
  // This method is called in the end of the main setup
  void onSetup() override;
};
```

game.cpp
``` cpp
#include "game.hpp"

void Game::onUpdate()
{
  if(this->time.justUpdated)
  {
    this->window.setTitle(std::format("{:.2f}ms {:.2f}fps", this->time.ms, this->time.fps));
  }
}

void Game::onSetup()
{
}
```