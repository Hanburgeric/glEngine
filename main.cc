#include <fstream>
#include <iostream>
#include <string>

#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/type_ptr.hpp>

#include "camera.h"
#include "importer.h"
#include "InputManager.h"
#include "interpolator.h"
#include "renderer.h"
#include "shader.h"
#include "utils.h"

//Global variables
std::int32_t screen_width = 1280;
std::int32_t screen_height = 720;
std::string screen_name = "GrapiCar";

//TEMPORARY : Global functions
void RenderNode(GLTF& gltf, std::int32_t node_index, float t, glm::mat4 transformation);

//Callback functions
void CursorPosCallback(GLFWwindow* window, double xpos, double ypos);
void ErrorCallback(int error, const char* description);
void FramebufferSizeCallBack(GLFWwindow* window, int width, int height);
void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
void ScrollCallback(GLFWwindow* window, double xoffset, double yoffset);

//TEMPORARY: Shaders
std::vector<Shader> shaders;

//TEMPORARY: Input manager class
InputManager input_manager;

int main() {
  //Initialize glfw
  if (glfwInit() == GLFW_TRUE) {
    glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

    //Create window
    GLFWwindow* window = glfwCreateWindow(screen_width, screen_height, screen_name.c_str(), nullptr, nullptr);
    if (window != nullptr) {
      //Set callback functions
      glfwMakeContextCurrent(window);
      (void)glfwSetCursorPosCallback(window, CursorPosCallback);
      (void)glfwSetErrorCallback(ErrorCallback);
      (void)glfwSetFramebufferSizeCallback(window, FramebufferSizeCallBack);
      (void)glfwSetKeyCallback(window, KeyCallback);
      (void)glfwSetMouseButtonCallback(window, MouseButtonCallback);
      (void)glfwSetScrollCallback(window, ScrollCallback);

      //Initialize glad
      if (gladLoadGL(static_cast<GLADloadfunc>(&glfwGetProcAddress)) != 0) {
        //Enable or disable OpenGL capabilities
        glEnable(static_cast<GLenum>(GL_DEPTH_TEST));

        //Model
        GLTF gltf;
        Importer importer;
        //importer.LoadASCIIFromFile(gltf, "../models/TriangleWithoutIndices/TriangleWithoutIndices.gltf");
        //importer.LoadASCIIFromFile(gltf, "../models/Triangle/Triangle.gltf");
        //importer.LoadASCIIFromFile(gltf, "../models/AnimatedTriangle/AnimatedTriangle.gltf");
        //importer.LoadASCIIFromFile(gltf, "../models/AnimatedMorphCube/AnimatedMorphCube.gltf"); // TO-DO
        //importer.LoadASCIIFromFile(gltf, "../models/AnimatedMorphSphere/AnimatedMorphSphere.gltf"); //TO-DO
        //importer.LoadASCIIFromFile(gltf, "../models/SimpleMeshes/SimpleMeshes.gltf");
        //importer.LoadASCIIFromFile(gltf, "../models/MultipleScenes/MultipleScenes.gltf");
        //importer.LoadASCIIFromFile(gltf, "../models/SimpleMorph/SimpleMorph.gltf");
        //importer.LoadASCIIFromFile(gltf, "../models/SimpleSparseAccessor/SimpleSparseAccessor.gltf"); // TO-DO
        //importer.LoadASCIIFromFile(gltf, "../models/SimpleSkin/SimpleSkin.gltf"); // TO-DO
        //importer.LoadASCIIFromFile(gltf, "../models/Cameras/Cameras.gltf"); // TO-DO
        importer.LoadASCIIFromFile(gltf, "../models/InterpolationTest/InterpolationTest.gltf"); // TO-DO
        //importer.LoadASCIIFromFile(gltf, "../models/Unicode❤♻Test.gltf/Unicode❤♻Test.gltf.gltf"); // TO-DO

        Shader default_shader;
        default_shader.AddShader(static_cast<GLenum>(GL_VERTEX_SHADER), "../shaders/primitive.vert");
        default_shader.AddShader(static_cast<GLenum>(GL_FRAGMENT_SHADER), "../shaders/pbr.frag");
        default_shader.CreateProgram();
        shaders.push_back(default_shader);

        //Camera
        Camera camera(glm::vec3(0.0F, 0.0F, 3.5F),
                      glm::vec3(0.0F, 1.0F, 0.0F),
                      270.0F, 0.0F, 45.0F,
                      0.1F, 100.0F);

        //Main loop
        while (glfwWindowShouldClose(window) == GLFW_FALSE) {
          auto curr_time = static_cast<float>(glfwGetTime());

          //TEMPORARY: Input handling
          camera.HandleInput(input_manager);
          camera.Update();
          input_manager.update();

          //TEMPORARY: Render
          glClearColor(48.0F / 255.0F, 53.0F / 255.0F, 66.0F / 255.0F, 1.0F);
          glClear(static_cast<GLenum>(GL_COLOR_BUFFER_BIT) | static_cast<GLenum>(GL_DEPTH_BUFFER_BIT));

          default_shader.BindProgram();

          //View Projection Matrix
          glm::mat4 projection_matrix =
              camera.GetProjectionMatrix(static_cast<float>(screen_width) / static_cast<float>(screen_height));
          glm::mat4 view_matrix = camera.GetViewMatrix();
          default_shader.SetUniformMatrix4fv("u_view_projection_matrix", 1, false,
                                             projection_matrix * view_matrix);

          if (gltf.scene_ >= 0) {
            const Scene& default_scene = gltf.scenes_[static_cast<std::size_t>(gltf.scene_)];
            for (auto node_index : default_scene.nodes_) {
              RenderNode(gltf, node_index, curr_time, glm::mat4(1.0F));
            }
          }

          //Swap buffers and poll IO events
          glfwSwapBuffers(window);
          glfwPollEvents();
        }
      }
      //Destroy window
      glfwDestroyWindow(window);
    }
    //Terminate glfw
    glfwTerminate();
  }
  return 0;
}

void RenderNode(GLTF& gltf, std::int32_t node_index, float t, glm::mat4 transformation) {
  const Node& node = gltf.nodes_[static_cast<std::size_t>(node_index)];
  glm::vec3 translate(node.translation_[0U], node.translation_[1U], node.translation_[2U]);
  glm::quat rotate(node.rotation_[3U], node.rotation_[0U], node.rotation_[1U], node.rotation_[2U]);
  glm::vec3 scale(node.scale_[0U], node.scale_[1U], node.scale_[2U]);

  //Camera

  //Children
  for (const auto& child_index : node.children_) {
    glm::mat4 T = glm::translate(glm::mat4(1.0F), translate);
    glm::mat4 R = glm::toMat4(rotate);
    glm::mat4 S = glm::scale(glm::mat4(1.0F), scale);
    glm::mat4 model = T * R * S;
    RenderNode(gltf, child_index, t, transformation * model);
  }

  //Skin

  //Mesh
  if (node.mesh_ >= 0) {
    std::vector<float> weights;
    std::vector<glm::vec3> targets;
    for (auto& animation : gltf.animations_) {
      for (const auto& channel : animation.channels_) {
        if (channel.target_.node_ == node_index) {
          const AnimationSampler& sampler = animation.samplers_[static_cast<std::size_t>(channel.sampler_)];
          Interpolator& interpolator = animation.interpolators_[static_cast<std::size_t>(channel.sampler_)];
          const std::string& path = channel.target_.path_;
          if (path == "translation") {
            const std::vector<float>& T = interpolator.Interpolate(gltf, channel, sampler, t, 3U, animation.max_time_);
            translate = glm::vec3(T[0U], T[1U], T[2U]);
          } else if (path == "rotation") {
            const std::vector<float>& R = interpolator.Interpolate(gltf, channel, sampler, t, 4U, animation.max_time_);
            rotate = glm::quat(R[3U], R[0U], R[1U], R[2U]);
          } else if (path == "scale"){
            const std::vector<float>& S = interpolator.Interpolate(gltf, channel, sampler, t, 3U, animation.max_time_);
            scale = glm::vec3(S[0U], S[1U], S[2U]);
          } else {
            const Mesh& mesh = gltf.meshes_[static_cast<std::size_t>(node.mesh_)];
            weights = interpolator.Interpolate(gltf, channel, sampler, t, mesh.weights_.size(), animation.max_time_);
            for (const auto& primitive : mesh.primitives_) {
              for (const auto& target : primitive.targets_) {
                const std::int32_t accessor_index = target.at("POSITION");
                const Accessor& accessor = gltf.accessors_[static_cast<std::size_t>(accessor_index)];
                const BufferView& buffer_view = gltf.buffer_views_[static_cast<std::size_t>(accessor.buffer_view_)];
                const Buffer& buffer = gltf.buffers_[static_cast<std::size_t>(buffer_view.buffer_)];
                const std::int32_t byte_offset = buffer_view.byte_offset_ + accessor.byte_offset_;
                const std::int32_t component_size = GetComponentSizeInBytes(accessor.component_type_);
                const std::int32_t component_number = GetNumComponentsInType(accessor);
                for (std::int32_t i = 0; i < accessor.count_; i++) {
                  std::int32_t offset = byte_offset + i * component_size * component_number;
                  targets.push_back(*reinterpret_cast<const glm::vec3*>(buffer.data_.data() + offset));
                }
              }
            }
          }
        }
      }
    }

    glm::mat4 T = glm::translate(glm::mat4(1.0F), translate);
    glm::mat4 R = glm::toMat4(rotate);
    glm::mat4 S = glm::scale(glm::mat4(1.0F), scale);

    glm::mat4 model = T * R * S;
    for (auto& shader : shaders) {
      shader.SetUniformMatrix4fv("u_model_matrix", 1, false, transformation * model);
      shader.SetUniform3fv("u_targets", static_cast<std::int32_t>(targets.size()), *reinterpret_cast<const glm::vec3*>(targets.data()));
      shader.SetUniform1fv("u_weights", static_cast<std::int32_t>(weights.size()), weights.data());
    }

    const Mesh& mesh = gltf.meshes_[static_cast<std::size_t>(node.mesh_)];
    for (const auto& primitive : mesh.primitives_) {
      glBindVertexArray(primitive.vao_);
      if (primitive.indices_ >= 0) {
        //Indexed geometry
        const Accessor& index_accessor = gltf.accessors_[static_cast<std::size_t>(primitive.indices_)];
        glDrawElements(static_cast<GLenum>(primitive.mode_),
                       static_cast<GLsizei>(index_accessor.count_),
                       static_cast<GLenum>(index_accessor.component_type_),
                       static_cast<char*>(nullptr) + index_accessor.byte_offset_);
      } else {
        //Non-indexed geometry
        const Accessor& position_accessor =
            gltf.accessors_[static_cast<std::size_t>(primitive.attributes_.at("POSITION"))];
        glDrawArrays(static_cast<GLenum>(primitive.mode_), 0, position_accessor.count_);
      }
    }
  }
}

void CursorPosCallback(GLFWwindow* window, double xpos, double ypos) {
  input_manager.cursorPosEvent(xpos, ypos);
}

void ErrorCallback(int error, const char* description) {
  std::cerr << "Error: " << description << std::endl;
}

void FramebufferSizeCallBack(GLFWwindow* window, int width, int height) {
  screen_width = width;
  screen_height = height;
  glViewport(0, 0, screen_width, screen_height);
}

void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
  input_manager.keyEvent(key, action);
}

void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
  input_manager.mouseButtonEvent(button, action);
}

void ScrollCallback(GLFWwindow* window, double xoffset, double yoffset) {
  input_manager.scrollEvent(xoffset, yoffset);
}
