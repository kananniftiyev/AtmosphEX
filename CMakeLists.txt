cmake_minimum_required(VERSION 3.10)
project(AtmosphEX VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 20)


# Add the TinyOBJLoader submodule directory
add_subdirectory(external/tinyobjloader)

# Include TinyOBJLoader headers in your project
include_directories(external/tinyobjloader)

# Set ImGui directory
set(IMGUI_DIR ${PROJECT_SOURCE_DIR}/external/imgui)

# Include ImGui headers
include_directories(${IMGUI_DIR})

# Add ImGui source files
set(IMGUI_SRC
    ${IMGUI_DIR}/imgui.cpp
    ${IMGUI_DIR}/imgui_draw.cpp
    ${IMGUI_DIR}/imgui_tables.cpp
    ${IMGUI_DIR}/imgui_widgets.cpp
    ${IMGUI_DIR}/backends/imgui_impl_glfw.cpp
    ${IMGUI_DIR}/backends/imgui_impl_opengl3.cpp
)

# Find required packages
find_package(glfw3 REQUIRED)
find_package(spdlog REQUIRED)

# Add glm as an include directory (header-only)
find_path(GLM_INCLUDE_DIR glm/glm.hpp)
include_directories(${ASSIMP_INCLUDE_DIR})

if (NOT GLM_INCLUDE_DIR)
    message(FATAL_ERROR "GLM not found! Make sure it is installed and included properly.")
endif()

# Include other directories
include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/lib/glad/include)
include_directories(${PROJECT_SOURCE_DIR}/lib/stbi)
include_directories(${PROJECT_SOURCE_DIR}/lib/linux)

include_directories(${GLM_INCLUDE_DIR})

# Add glad source file
set(GLAD_SRC ${PROJECT_SOURCE_DIR}/lib/glad/src/glad.c)

# Gather all source files in the src directory
file(GLOB_RECURSE TARGET_SRC "${PROJECT_SOURCE_DIR}/src/*.cpp")

# Create the main executable
add_executable(main ${TARGET_SRC} ${GLAD_SRC} ${IMGUI_SRC})

# Link glfw, spdlog, TinyOBJLoader, and ImGui to the executable
target_link_libraries(main glfw spdlog::spdlog tinyobjloader)

# CPack configuration
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
