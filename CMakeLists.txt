cmake_minimum_required(VERSION 3.23)
project(glEngine)

set(CMAKE_CXX_STANDARD 11)

#GLAD
include_directories(vendor/glfw-3.3.8/deps)
set(GLAD_GL vendor/glfw-3.3.8/deps/glad/gl.h
        ${GLFW_SOURCE_DIR}/deps/glad_gl.c)

#GLFW
find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIRS})
add_subdirectory(vendor/glfw-3.3.8)

#GLM
include_directories(vendor/glm-0.9.9.8/glm)

#rapidjson
include_directories(vendor/rapidjson)

#stb-master
include_directories(vendor/stb-master)

#tinygltf
include_directories(vendor/tinygltf-2.7.0)

add_executable(${PROJECT_NAME} ${GLAD_GL} main.cc
        accessor.h
        animation.h
        buffer.h
        buffer_view.h
        gltf.h
        importer.cc importer.h
        mesh.h
        node.h
        scene.h
        shader.cc shader.h
        utils.cc utils.h
        camera.h
        Interpolator.cc Interpolator.h)

#GLFW
target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARIES} glfw)
