cmake_minimum_required(VERSION 3.10)
project(AtmosphEX VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 20)

# Find required packages
find_package(glfw3 REQUIRED)
find_package(spdlog REQUIRED)
find_package(nlohmann_json REQUIRED)
# Add glm as an include directory (header-only)
find_path(GLM_INCLUDE_DIR glm/glm.hpp)

if (NOT GLM_INCLUDE_DIR)
    message(FATAL_ERROR "GLM not found! Make sure it is installed and included properly.")
endif()

# Include directories
include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/lib/glad/include)
include_directories(${PROJECT_SOURCE_DIR}/lib)

include_directories(${GLM_INCLUDE_DIR})

# Add glad source file
set(GLAD_SRC ${PROJECT_SOURCE_DIR}/lib/glad/src/glad.c)

# Gather all source files in the src directory
file(GLOB_RECURSE TARGET_SRC "${PROJECT_SOURCE_DIR}/src/*.cpp")
# Create the main executable
add_executable(main ${TARGET_SRC} ${GLAD_SRC})

# Link glfw (GLM doesn't need linking as it's header-only)
target_link_libraries(main glfw spdlog::spdlog nlohmann_json::nlohmann_json)

# CPack configuration
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
