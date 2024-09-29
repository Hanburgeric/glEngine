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
#include "src/engine/engine.h"
#include "src/engine/renderer/program.h"
#include "src/engine/renderer/shader.h"

// OpenGL callback functions
namespace gl {
void APIENTRY DebugMessageCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length,
                                   const GLchar* message, const void* user_param);
}

// GLFW callback functions
namespace glfw {
void CursorPosCallback(GLFWwindow* window, double xpos, double ypos);
void ErrorCallback(int error_code, const char* description);
void FramebufferSizeCallback(GLFWwindow* window, int width, int height);
void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
void ScrollCallback(GLFWwindow* window, double xoffset, double yoffset);
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
  GLFWwindow* window = glfwCreateWindow(1600, 900, "glEngine", nullptr, nullptr);

  if (!window) {
    std::cerr << "glfwCreateWindow failed" << std::endl;
    glfwTerminate();
    return 1;
  }

  glfwMakeContextCurrent(window);

  // Set remaining GLFW callbacks
  (void)glfwSetCursorPosCallback(window, glfw::CursorPosCallback);
  (void)glfwSetFramebufferSizeCallback(window, glfw::FramebufferSizeCallback);
  (void)glfwSetKeyCallback(window, glfw::KeyCallback);
  (void)glfwSetMouseButtonCallback(window, glfw::MouseButtonCallback);
  (void)glfwSetScrollCallback(window, glfw::ScrollCallback);

  // Load function pointers
  if (!gladLoadGL(glfwGetProcAddress)) {
    std::cerr << "gladLoadGL failed" << std::endl;
    glfwDestroyWindow(window);
    glfwTerminate();
    return 1;
  }

  // Enable and set OpenGL debug message callback
  glEnable(GL_DEBUG_OUTPUT);
  glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
  glDebugMessageCallback(gl::DebugMessageCallback, nullptr);

  // Enable remaining OpenGL capabilities
  glEnable(GL_CULL_FACE);
  glEnable(GL_DEPTH_TEST);

  // Create engine instance and link with window
  glEngine::Engine engine;
  glfwSetWindowUserPointer(window, &engine);

  // Load shaders
  glEngine::renderer::Shader vertex(GL_VERTEX_SHADER, "../shaders/default.vert");
  glEngine::renderer::Shader fragment(GL_FRAGMENT_SHADER, "../shaders/default.frag");

  // Link shaders
  glEngine::renderer::Program program({vertex, fragment});

  // Use program
  glUseProgram(program.GetProgram());

  // Load glTF
  // TO-DO : each model should have its own camera position/sensitivity, as well as a dedicated shader
//  glEngine::Model model("../assets/ABeautifulGame/glTF/ABeautifulGame.gltf");
//  glEngine::Model model("../assets/BrainStem/glTF/BrainStem.gltf");
  glEngine::Model model("../assets/CesiumMilkTruck/glTF/CesiumMilkTruck.gltf");
//  glEngine::Model model("../assets/DamagedHelmet/glTF/DamagedHelmet.gltf");
//  glEngine::Model model("../assets/Triangle/glTF/Triangle.gltf");
//  glEngine::Model model("../assets/TriangleWithoutindices/glTF/TriangleWithoutIndices.gltf");
//  glEngine::Model model("../assets/VirtualCity/glTF/VirtualCity.gltf");

  // Main loop
  while (!glfwWindowShouldClose(window)) {
    // Handle events
    glfwPollEvents();

    // Update
    engine.Update();

    // Render
    glClearColor(0.0F, 0.0F, 0.0F, 1.0F);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Set projection matrix
    int width;
    int height;
    glfwGetFramebufferSize(window, &width, &height);
    glm::mat4 P = glm::perspective(glm::radians(45.0F),
                                            static_cast<float>(width) / static_cast<float>(height),
                                            0.1F, 100.0F);
    glUniformMatrix4fv(program.GetUniformLocation("projection"), 1, false, glm::value_ptr(P));

    // Set view matrix
    glm::mat4 V = engine.GetCamera().CalcViewMatrix();
    glUniformMatrix4fv(program.GetUniformLocation("view"), 1, false, glm::value_ptr(V));

    // Render model
    model.Render(program);

    // Swap buffers
    glfwSwapBuffers(window);
  }

  // Cleanup
  glfwDestroyWindow(window);
  glfwTerminate();

  return 0;
}

// OpenGL callback functions
namespace gl {
void APIENTRY DebugMessageCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length,
                                   const GLchar* message, const void* user_param) {
  std::cerr << "(" << id << ") " << message << std::endl;
}
}

// GLFW callback functions
namespace glfw {
void CursorPosCallback(GLFWwindow* window, double xpos, double ypos) {
  auto* engine = static_cast<glEngine::Engine*>(glfwGetWindowUserPointer(window));
  engine->OnCursorPos(xpos, ypos);
}

void ErrorCallback(int error_code, const char* description) {
  std::cerr << "(" << error_code << ") " << description << std::endl;
}

void FramebufferSizeCallback(GLFWwindow* window, int width, int height) {
  glViewport(0, 0, width, height);
}

void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
  auto* engine = static_cast<glEngine::Engine*>(glfwGetWindowUserPointer(window));
  engine->OnKey(key, action);
}

void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
  auto* engine = static_cast<glEngine::Engine*>(glfwGetWindowUserPointer(window));
  engine->OnMouseButton(button, action);
}

void ScrollCallback(GLFWwindow* window, double xoffset, double yoffset) {
  auto* engine = static_cast<glEngine::Engine*>(glfwGetWindowUserPointer(window));
  engine->OnScroll(xoffset, yoffset);
}
}
