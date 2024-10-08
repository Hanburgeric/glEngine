#define STB_IMAGE_IMPLEMENTATION

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
#include "stb_image.h"

// User headers
#include "src/engine/cube.h"
#include "src/engine/model.h"
#include "src/engine/engine.h"
#include "src/engine/program.h"
#include "src/engine/shader.h"
#include "src/engine/texture.h"

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

  // Flip images for OpenGL
  stbi_set_flip_vertically_on_load(true);

  // Create engine instance and link with window
  glEngine::Engine engine;
  glfwSetWindowUserPointer(window, &engine);

  // Load shaders
  glEngine::Shader vert(GL_VERTEX_SHADER);
  vert.AddSource("../shaders/vert.glsl");
  vert.Compile();

  glEngine::Shader frag(GL_FRAGMENT_SHADER);
  frag.AddSource("../shaders/frag.glsl");
  frag.Compile();

  // Link shaders
  glEngine::Program prog;
  prog.AddShader(vert);
  prog.AddShader(frag);
  prog.Link();

  // Cubes
  std::vector<glEngine::Cube> cubes;
  cubes.reserve(10U);
  (void)cubes.emplace_back(glm::vec3( 0.0F,  0.0F,  0.0F ));
  (void)cubes.emplace_back(glm::vec3( 2.0F,  5.0F, -15.0F));
  (void)cubes.emplace_back(glm::vec3(-1.5F, -2.2F, -2.5F ));
  (void)cubes.emplace_back(glm::vec3(-3.8F, -2.0F, -12.3F));
  (void)cubes.emplace_back(glm::vec3( 2.4F, -0.4F, -3.5F ));
  (void)cubes.emplace_back(glm::vec3(-1.7F,  3.0F, -7.5F ));
  (void)cubes.emplace_back(glm::vec3( 1.3F, -2.0F, -2.5F ));
  (void)cubes.emplace_back(glm::vec3( 1.5F,  2.0F, -2.5F ));
  (void)cubes.emplace_back(glm::vec3( 1.5F,  0.2F, -1.5F ));
  (void)cubes.emplace_back(glm::vec3(-1.3F,  1.0F, -1.5F ));

  // Textures
  glEngine::Texture tex;
  tex.LoadImage("../assets/BoxTextured/glTF/CesiumLogoFlat.png");

  // Use program
  glUseProgram(prog.GetId());

  // Main loop
  while (!glfwWindowShouldClose(window)) {
    // Handle events
    glfwPollEvents();

    // Update
    engine.Update();

    // Render
    glClearColor(0.0F, 0.0F, 0.0F, 1.0F);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Use program
    glUseProgram(prog.GetId());

    // Set projection matrix
    int width;
    int height;
    glfwGetFramebufferSize(window, &width, &height);
    glm::mat4 P = glm::perspective(glm::radians(45.0F),
                                            static_cast<float>(width) / static_cast<float>(height),
                                            0.1F, 100.0F);
    glUniformMatrix4fv(prog.GetUniformLocation("projection"), 1, false, glm::value_ptr(P));

    // Set view matrix
    glm::mat4 V = engine.GetCamera().CalcViewMatrix();
    glUniformMatrix4fv(prog.GetUniformLocation("view"), 1, false, glm::value_ptr(V));

    // Set texture(s)
    glUniform1i(prog.GetUniformLocation("tex"), tex.GetId());
    glActiveTexture(GL_TEXTURE0 + tex.GetId());
    glBindTexture(GL_TEXTURE_2D, tex.GetId());

    // Set model matrix
    for (std::size_t i = 0U; i < cubes.size(); i++) {
      glBindVertexArray(cubes[i].GetId());

      glm::mat4 M(1.0F);
      M = glm::translate(M, cubes[i].GetPosition());
      M = glm::rotate(M, glm::radians(20.0F * i), glm::vec3(1.0F, 0.3F, 0.5F));
      glUniformMatrix4fv(prog.GetUniformLocation("model"), 1, false, glm::value_ptr(M));

      // Draw cubes
      cubes[i].Render();
    }

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
