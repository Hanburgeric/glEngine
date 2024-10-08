cmake_minimum_required(VERSION 3.5)
project(glEngine)

set(CMAKE_CXX_STANDARD 17)

# GLAD
include_directories(vendor/glad/include)
set(GLAD vendor/glad/include/glad/gl.h vendor/glad/src/gl.c)

# GLFW
add_subdirectory(vendor/glfw-3.4)

# GLM
add_subdirectory(vendor/glm-1.0.1)

# JSON
add_subdirectory(vendor/json-3.11.3)

# STB
include_directories(vendor/stb-master)

# SRC
set(SRC src/engine/camera.cc src/engine/camera.h
        src/engine/cube.cc src/engine/cube.h
        src/engine/engine.cc src/engine/engine.h
        src/engine/importer.cc src/engine/importer.h
        src/engine/input_manager.cc src/engine/input_manager.h
        src/engine/mesh.cc src/engine/mesh.h
        src/engine/model.cc src/engine/model.h
        src/engine/primitive.cc src/engine/primitive.h
        src/engine/program.cc src/engine/program.h
        src/engine/shader.cc src/engine/shader.h
        src/engine/texture.cc src/engine/texture.h
        src/engine/utils.cc src/engine/utils.h
        src/gltf/accessor.h
        src/gltf/buffer.h
        src/gltf/buffer_view.h
        src/gltf/gltf.h
        src/gltf/material.h
        src/gltf/mesh.h
        src/gltf/node.h
        src/gltf/scene.h
        src/engine/material.cc
        src/engine/material.h
)

add_executable(${PROJECT_NAME} ${GLAD} ${SRC} main.cc)

target_link_libraries(${PROJECT_NAME} glfw glm::glm nlohmann_json::nlohmann_json)
