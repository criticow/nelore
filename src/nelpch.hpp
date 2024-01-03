#pragma once

// std
#include <iostream>
#include <fstream>
#include <sstream>
#include <format>
#include <unordered_map>
#include <unordered_set>
#include <thread>
#include <mutex>
#include <vector>
#include <iomanip>
#include <random>
#include <cctype>

// Math
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

// Physics
#include <bullet/btBulletDynamicsCommon.h>

// Window and OpenGL loader
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>

// ECS
#include <entt/entt.hpp>

#include <nel/util/logger.hpp>