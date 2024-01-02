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

project's CMakeLists.txt

``` cmake
cmake_minimum_required(VERSION 3.20)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake")
project(game CXX)

add_executable(${PROJECT_NAME} src/main.cpp)

set(NEL_BUILD_TESTS OFF)
add_subdirectory(nelore)
target_link_libraries(${PROJECT_NAME} PRIVATE nelore)
target_link_directories(${PROJECT_NAME} PRIVATE nelore/src)
```