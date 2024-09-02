cmake_minimum_required(VERSION 3.28)
project(glEngine)

set(CMAKE_CXX_STANDARD 23)

# GLAD
include_directories(vendor/glad/include)
set(GLAD vendor/glad/include/glad/gl.h vendor/glad/src/gl.c)

# GLFW
add_subdirectory(vendor/glfw-3.4)

# GLM
add_subdirectory(vendor/glm-1.0.1)

# JSON
add_subdirectory(vendor/json-3.11.3)

# SRC
set(SRC src/gltf/accessor.h
        src/gltf/buffer.h
        src/gltf/buffer_view.h
        src/gltf/gltf.h
        src/gltf/mesh.h
        src/gltf/node.h
        src/gltf/scene.h
        src/model.cc src/model.h
        src/renderer/program.cc src/renderer/program.h
        src/renderer/shader.cc src/renderer/shader.h
        src/utils.cc src/utils.h)

add_executable(${PROJECT_NAME} ${GLAD} ${SRC} main.cpp)

target_link_libraries(${PROJECT_NAME} glfw glm::glm nlohmann_json::nlohmann_json)
