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

  // Lights
  glEngine::Shader point_light_vert(GL_VERTEX_SHADER);
  point_light_vert.AddSource("../shaders/point_light_vert.glsl");
  point_light_vert.Compile();

  glEngine::Shader point_light_frag(GL_FRAGMENT_SHADER);
  point_light_frag.AddSource("../shaders/point_light_frag.glsl");
  point_light_frag.Compile();

  glEngine::Program point_light_prog;
  point_light_prog.AddShader(point_light_vert);
  point_light_prog.AddShader(point_light_frag);
  point_light_prog.Link();

  std::array<glm::vec3, 4U> point_light_positions {
      glm::vec3( 0.7F,  0.2F,  2.0F ),
      glm::vec3( 2.3F, -3.3F, -4.0F ),
      glm::vec3(-4.0F,  2.0F, -12.0F),
      glm::vec3( 0.0F,  0.0F, -3.0F )
  };

  // Load model
  glEngine::Cube cube;

  // Laod textures
  glEngine::Texture base_color_texture;
  base_color_texture.LoadImage("../textures/container2.png");

  glEngine::Texture specular_texture;
  specular_texture.LoadImage("../textures/container2_specular.png");

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

  // Set lighting data
  glUseProgram(prog.GetId());

  glUniform3fv(prog.GetUniformLocation("direction_light.ambient_"), 1, glm::value_ptr(glm::vec3(0.05F, 0.05F, 0.05F)));
  glUniform3fv(prog.GetUniformLocation("direction_light.diffuse_"), 1, glm::value_ptr(glm::vec3(0.4F, 0.4F, 0.4F)));
  glUniform3fv(prog.GetUniformLocation("direction_light.specular_"), 1, glm::value_ptr(glm::vec3(0.5F, 0.5F, 0.5F)));
  glUniform3fv(prog.GetUniformLocation("direction_light.direction_"), 1, glm::value_ptr(glm::vec3(-0.2F, -1.0F, -0.3F)));

  for (std::size_t i = 0U; i < point_light_positions.size(); ++i) {
    glUniform3fv(prog.GetUniformLocation("point_lights[" + std::to_string(i) + "].ambient_"), 1, glm::value_ptr(glm::vec3(0.05F, 0.05F, 0.05F)));
    glUniform3fv(prog.GetUniformLocation("point_lights[" + std::to_string(i) + "].diffuse_"), 1, glm::value_ptr(glm::vec3(0.8F, 0.8F, 0.8F)));
    glUniform3fv(prog.GetUniformLocation("point_lights[" + std::to_string(i) + "].specular_"), 1, glm::value_ptr(glm::vec3(1.0F, 1.0F, 1.0F)));
    glUniform1f(prog.GetUniformLocation("point_lights[" + std::to_string(i) + "].constant_"), 1.0F);
    glUniform1f(prog.GetUniformLocation("point_lights[" + std::to_string(i) + "].linear_"), 0.09F);
    glUniform1f(prog.GetUniformLocation("point_lights[" + std::to_string(i) + "].quadratic_"), 0.032F);
    glUniform3fv(prog.GetUniformLocation("point_lights[" + std::to_string(i) + "].position_"), 1, glm::value_ptr(point_light_positions[i]));
  }

  glUniform3fv(prog.GetUniformLocation("spot_light.ambient_"), 1, glm::value_ptr(glm::vec3(0.0F, 0.0F, 0.0F)));
  glUniform3fv(prog.GetUniformLocation("spot_light.diffuse_"), 1, glm::value_ptr(glm::vec3(1.0F, 1.0F, 1.0F)));
  glUniform3fv(prog.GetUniformLocation("spot_light.specular_"), 1, glm::value_ptr(glm::vec3(1.0F, 1.0F, 1.0F)));
  glUniform1f(prog.GetUniformLocation("spot_light.constant_"), 1.0F);
  glUniform1f(prog.GetUniformLocation("spot_light.linear_"), 0.09F);
  glUniform1f(prog.GetUniformLocation("spot_light.quadratic_"), 0.032F);
  glUniform3fv(prog.GetUniformLocation("spot_light.position_"), 1, glm::value_ptr(engine.GetCamera().GetPosition()));
  glUniform3fv(prog.GetUniformLocation("spot_light.direction_"), 1, glm::value_ptr(engine.GetCamera().GetFront()));
  glUniform1f(prog.GetUniformLocation("spot_light.inner_cutoff_"), glm::cos(glm::radians(12.5F)));
  glUniform1f(prog.GetUniformLocation("spot_light.outer_cutoff_"), glm::cos(glm::radians(15.0F)));

  glUniform1i(prog.GetUniformLocation("material.base_color_texture_"), base_color_texture.GetId());
  glActiveTexture(GL_TEXTURE0 + base_color_texture.GetId());
  glBindTexture(GL_TEXTURE_2D, base_color_texture.GetId());
  glUniform1i(prog.GetUniformLocation("material.specular_texture_"), specular_texture.GetId());
  glActiveTexture(GL_TEXTURE0 + specular_texture.GetId());
  glBindTexture(GL_TEXTURE_2D, specular_texture.GetId());
  glUniform1f(prog.GetUniformLocation("material.shininess_"), 32.0F);

  // Models
  std::array<glm::vec3, 10U> cube_positions {
      glm::vec3( 0.0F,  0.0F,  0.0F ),
      glm::vec3( 2.0F,  5.0F, -15.0F),
      glm::vec3(-1.5F, -2.2F, -2.5F ),
      glm::vec3(-3.8F, -2.0F, -12.3F),
      glm::vec3( 2.4F, -0.4F, -3.5F ),
      glm::vec3(-1.7F,  3.0F, -7.5F ),
      glm::vec3( 1.3F, -2.0F, -2.5F ),
      glm::vec3( 1.5F,  2.0F, -2.5F ),
      glm::vec3( 1.5F,  0.2F, -1.5F ),
      glm::vec3(-1.3F,  1.0F, -1.5F )
  };

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

    // Lights
    glUseProgram(point_light_prog.GetId());
    glUniformMatrix4fv(point_light_prog.GetUniformLocation("projection"), 1, false, glm::value_ptr(P));
    glUniformMatrix4fv(point_light_prog.GetUniformLocation("view"), 1, false, glm::value_ptr(V));
    for (const auto& position : point_light_positions) {
      glm::mat4 M(1.0F);
      M = glm::translate(M, position);
      M = glm::scale(M, glm::vec3(0.2F));
      glUniformMatrix4fv(point_light_prog.GetUniformLocation("model"), 1, false, glm::value_ptr(M));
      cube.Render();
    }

    // Set model matrix
    glUseProgram(prog.GetId());
    glUniform3fv(prog.GetUniformLocation("spot_light.position_"), 1, glm::value_ptr(engine.GetCamera().GetPosition()));
    glUniform3fv(prog.GetUniformLocation("spot_light.direction_"), 1, glm::value_ptr(engine.GetCamera().GetFront()));
    glUniform3fv(prog.GetUniformLocation("view_position"), 1, glm::value_ptr(engine.GetCamera().GetPosition()));
    for (std::size_t i = 0U; i < cube_positions.size(); i++) {
      glm::mat4 M(1.0F);
      M = glm::translate(M, cube_positions[i]);
      M = glm::rotate(M, glm::radians(20.0F * i), glm::vec3(1.0F, 0.3F, 0.5F));
      glUniformMatrix4fv(prog.GetUniformLocation("model"), 1, false, glm::value_ptr(M));
      cube.Render();
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
