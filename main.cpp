// System headers
#include <iostream>

// Vendor headers
#include "glad/gl.h"
#include "GLFW/glfw3.h"
#include "glm/geometric.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/mat4x4.hpp"
#include "glm/trigonometric.hpp"
#include "glm/vec3.hpp"

// User headers
#include "src/model.h"
#include "src/renderer/program.h"
#include "src/renderer/shader.h"

// GLFW callback functions
namespace glfw {
void ErrorCallback(int error_code, const char* description);
void FramebufferSizeCallback(GLFWwindow* window, int width, int height);
}

// OpenGL callback functions
namespace gl {
void APIENTRY DebugMessageCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length,
                                   const GLchar* message, const void* user_param);
}

int main() {
  // Set GLFW error callback
  (void)glfwSetErrorCallback(glfw::ErrorCallback);

  // Initialize GLFW
  if (!glfwInit()) {
    std::cerr << "glfwInit failed" << std::endl;
    return 1;
  }

  // Configure window hints
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);

  // Initialize window
  GLFWwindow* window = glfwCreateWindow(1280, 720, "glEngine", nullptr, nullptr);

  if (!window) {
    std::cerr << "glfwCreateWindow failed" << std::endl;
    glfwTerminate();
    return 1;
  }

  glfwMakeContextCurrent(window);

  // Set remaining callbacks
  (void)glfwSetFramebufferSizeCallback(window, glfw::FramebufferSizeCallback);

  // Load function pointers
  if (!gladLoadGL(glfwGetProcAddress)) {
    std::cerr << "gladLoadGL failed" << std::endl;
    glfwDestroyWindow(window);
    glfwTerminate();
    return 1;
  }

  // Set OpenGL error callback
  glEnable(GL_DEBUG_OUTPUT | GL_DEBUG_OUTPUT_SYNCHRONOUS);
  glDebugMessageCallback(gl::DebugMessageCallback, nullptr);

  // Enable OpenGL capabilities
  glEnable(GL_DEPTH_TEST);

  // Load shaders
  glEngine::renderer::Shader default_vertex(GL_VERTEX_SHADER, "../shaders/default.vert");
  glEngine::renderer::Shader default_fragment(GL_FRAGMENT_SHADER, "../shaders/default.frag");

  // Link shaders
  glEngine::renderer::Program default_program({default_vertex, default_fragment});

  // Load glTF
  glEngine::Model model("../assets/Triangle/Triangle.gltf");

  // MVP Matrices
  glm::mat4 model_matrix(1.0F);

  glm::vec3 camera_position(0.0F, 0.0F, 3.5F);
  float camera_yaw = 270.0F;
  float camera_pitch = 0.0F;
  glm::vec3 camera_front(glm::normalize(glm::vec3(glm::cos(glm::radians(camera_yaw)) * glm::cos(glm::radians(camera_pitch)),
                                                  glm::sin(glm::radians(camera_pitch)),
                                                  glm::sin(glm::radians(camera_yaw)) * glm::cos(glm::radians(camera_pitch)))));
  glm::vec3 camera_up(glm::normalize(glm::cross(glm::normalize(glm::cross(camera_front, glm::vec3(0.0F, 1.0F, 0.0F))), camera_front)));
  glm::mat4 view_matrix = glm::lookAt(camera_position, camera_position + camera_front, camera_up);

  float camera_fov = 45.0F;
  float camera_aspect = 1280.0F / 720.0F;
  float camera_near = 0.1F;
  float camera_far = 100.0F;
  glm::mat4 projection_matrix = glm::perspective(glm::radians(camera_fov),
                                                 camera_aspect,
                                                 camera_near, camera_far);

  // Main loop
  while (!glfwWindowShouldClose(window)) {
    // Handle events
    glfwPollEvents();

    // Update

    // Render
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Get default scene
    if (model.GetGltf().scene_.has_value()) {
      int default_scene_index = model.GetGltf().scene_.value();

      // Get nodes from default scene
      const auto& node_indices = model.GetGltf().scenes_[default_scene_index].nodes_;

      // Iterate through nodes
      for (int node_index : node_indices) {
        const auto& node = model.GetGltf().nodes_[node_index];

        // Mesh
        if (node.mesh_.has_value()) {
          int mesh_index = node.mesh_.value();
          const auto& mesh = model.GetGltf().meshes_[mesh_index];

          // Mesh primitive
          for (const auto& mesh_primitive : mesh.primitives_) {
            // Use program
            unsigned int program_id = default_program.GetProgram();
            glUseProgram(program_id);

            // Set transformation matrices
            glUniformMatrix4fv(glGetUniformLocation(program_id, "u_model_matrix"), 1, false, glm::value_ptr(model_matrix));
            glUniformMatrix4fv(glGetUniformLocation(program_id, "u_view_matrix"), 1, false, glm::value_ptr(view_matrix));
            glUniformMatrix4fv(glGetUniformLocation(program_id, "u_projection_matrix"), 1, false, glm::value_ptr(projection_matrix));

            // Bind VAO
            glBindVertexArray(mesh_primitive.vao_);
            if (mesh_primitive.indices_.has_value()) {
              // Render indexed geometry
              const auto& accessor = model.GetGltf().accessors_[mesh_primitive.indices_.value()];

              glDrawElements(mesh_primitive.mode_.value_or(4),
                             accessor.count_,
                             accessor.component_type_,
                             static_cast<char*>(nullptr) + accessor.byte_offset_.value_or(0));
            } else {
              // TO-DO : render non-indexed geometry
            }
          }
        }

        // TO-DO : Apply transformation matrices of parent nodes
        // TO-DO : Iterate through children nodes
      }
    }

    // Swap buffers
    glfwSwapBuffers(window);
  }

  // Cleanup
  glfwDestroyWindow(window);
  glfwTerminate();

  return 0;
}

// GLFW callback functions
namespace glfw {
void ErrorCallback(int error_code, const char* description) {
  std::cerr << "(" << error_code << ") " << description << std::endl;
}

void FramebufferSizeCallback(GLFWwindow* window, int width, int height) {
  glViewport(0, 0, width, height);
}
}

// OpenGL callback functions
namespace gl {
void APIENTRY DebugMessageCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length,
                                   const GLchar* message, const void* user_param) {
  std::cerr << "(" << id << ") " << message << std::endl;
}
}
