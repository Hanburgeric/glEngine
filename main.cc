#define STB_IMAGE_IMPLEMENTATION

#include <iostream>
#include <string>

#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <glm/gtx/quaternion.hpp>
#include <stb_image.h>

#include "camera.h"
#include "importer.h"
#include "InputManager.h"
#include "shader.h"

//Global variables
int screen_width = 1280;
int screen_height = 720;
std::string screen_name = "GrapiCar";

//Cube VAO, VBO
std::uint32_t cubeVAO_ = 0U;
std::uint32_t cubeVBO_ = 0U;

//Quads VAO, VBO
std::uint32_t quadVAO_ = 0U;
std::uint32_t quadVBO_ = 0U;

//TEMPORARY: Load texture
std::uint32_t LoadTexture(const std::string& path);

//Renders a 1x1 3D cube in NDC
void RenderCube();
void RenderQuad();

//Callback functions
void CursorPosCallback(GLFWwindow* window, double xpos, double ypos);
void ErrorCallback(int error, const char* description);
void FramebufferSizeCallBack(GLFWwindow* window, int width, int height);
void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
void ScrollCallback(GLFWwindow* window, double xoffset, double yoffset);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);

//TEMPORARY: Input manager class
InputManager input_manager;

int main() {
  //Initialize glfw
  if (glfwInit() == GLFW_TRUE) {
    glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_SAMPLES, 4);

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
      (void)glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

      //Initialize glad
      if (gladLoadGL(static_cast<GLADloadfunc>(&glfwGetProcAddress)) != 0) {
        //Enable or disable OpenGL capabilities
        glEnable(static_cast<GLenum>(GL_DEPTH_TEST));
        glDepthFunc(static_cast<GLenum>(GL_LEQUAL));
        glEnable(static_cast<GLenum>(GL_TEXTURE_CUBE_MAP_SEAMLESS));

        //Load model
        GLTF gltf;
        Importer importer;
        importer.LoadASCIIFromFile(gltf, "../DamagedHelmet/DamagedHelmet.gltf");

        //Load shaders
        Shader default_shader;
        default_shader.AddShader(static_cast<GLenum>(GL_VERTEX_SHADER),
                                 "../DamagedHelmet/default.vert");
        default_shader.AddShader(static_cast<GLenum>(GL_FRAGMENT_SHADER),
                                 "../DamagedHelmet/default.frag");
        default_shader.CreateProgram();

        Shader equirectangular_to_cubemap_shader;
        equirectangular_to_cubemap_shader.AddShader(static_cast<GLenum>(GL_VERTEX_SHADER),
                                                    "../DamagedHelmet/cubemap.vert");
        equirectangular_to_cubemap_shader.AddShader(static_cast<GLenum>(GL_FRAGMENT_SHADER),
                                                    "../DamagedHelmet/cubemap.frag");
        equirectangular_to_cubemap_shader.CreateProgram();

        Shader irradiance_shader;
        irradiance_shader.AddShader(static_cast<GLenum>(GL_VERTEX_SHADER),
                                    "../DamagedHelmet/cubemap.vert");
        irradiance_shader.AddShader(static_cast<GLenum>(GL_FRAGMENT_SHADER),
                                    "../DamagedHelmet/irradiance_convolution.frag");
        irradiance_shader.CreateProgram();

        Shader prefilter_shader;
        prefilter_shader.AddShader(static_cast<GLenum>(GL_VERTEX_SHADER),
                                   "../DamagedHelmet/cubemap.vert");
        prefilter_shader.AddShader(static_cast<GLenum>(GL_FRAGMENT_SHADER),
                                   "../DamagedHelmet/prefilter.frag");
        prefilter_shader.CreateProgram();

        Shader brdf_shader;
        brdf_shader.AddShader(static_cast<GLenum>(GL_VERTEX_SHADER),
                             "../DamagedHelmet/brdf.vert");
        brdf_shader.AddShader(static_cast<GLenum>(GL_FRAGMENT_SHADER),
                             "../DamagedHelmet/brdf.frag");
        brdf_shader.CreateProgram();

        Shader background_shader;
        background_shader.AddShader(static_cast<GLenum>(GL_VERTEX_SHADER),
                                    "../DamagedHelmet/background.vert");
        background_shader.AddShader(static_cast<GLenum>(GL_FRAGMENT_SHADER),
                                    "../DamagedHelmet/background.frag");
        background_shader.CreateProgram();

        //TEMPORARY : Load textures
        std::uint32_t albedo = LoadTexture("../DamagedHelmet/Default_albedo.jpg");
        std::uint32_t normal = LoadTexture("../DamagedHelmet/Default_normal.jpg");
        std::uint32_t metal_roughness = LoadTexture("../DamagedHelmet/Default_metalRoughness.jpg");
        std::uint32_t emissive = LoadTexture("../DamagedHelmet/Default_emissive.jpg");
        std::uint32_t ambient_occlusion = LoadTexture("../DamagedHelmet/Default_AO.jpg");

        //Setup Framebuffer
        std::uint32_t capture_fbo;
        std::uint32_t capture_rbo;
        glGenFramebuffers(1, &capture_fbo);
        glGenRenderbuffers(1, &capture_rbo);
        glBindFramebuffer(GL_FRAMEBUFFER, capture_fbo);
        glBindRenderbuffer(GL_RENDERBUFFER, capture_rbo);
        glRenderbufferStorage(GL_RENDERBUFFER, static_cast<GLenum>(GL_DEPTH_COMPONENT24), 512, 512);
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, static_cast<GLenum>(GL_DEPTH_ATTACHMENT),
                                  GL_RENDERBUFFER, capture_rbo);

        //Load the HDR environment map
        stbi_set_flip_vertically_on_load(true);
        std::int32_t x;
        std::int32_t y;
        std::int32_t comp;
        float* data = stbi_loadf("../DamagedHelmet/resources/Newport_Loft_Ref.hdr", &x, &y, &comp, 0);
        std::uint32_t hdr_texture;
        if (data != nullptr) {
          glGenTextures(1, &hdr_texture);
          glBindTexture(GL_TEXTURE_2D, hdr_texture);
          glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, x, y, 0,
                       static_cast<GLenum>(GL_RGB), static_cast<GLenum>(GL_FLOAT), data);
          glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
          glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
          glTexParameteri(GL_TEXTURE_2D, static_cast<GLenum>(GL_TEXTURE_MIN_FILTER), GL_LINEAR);
          glTexParameteri(GL_TEXTURE_2D, static_cast<GLenum>(GL_TEXTURE_MAG_FILTER), GL_LINEAR);
          stbi_image_free(data);
        } else {
          std::cout << "Failed to load HDR image." << std::endl;
        }

        //Setup cubemap to render to and attach to framebuffer
        std::uint32_t env_cube_map;
        glGenTextures(1, &env_cube_map);
        glBindTexture(GL_TEXTURE_CUBE_MAP, env_cube_map);
        for (std::size_t i = 0U; i < 6U; i++) {
          glTexImage2D(static_cast<GLenum>(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i),
                       0, GL_RGB16F, 512, 512, 0, static_cast<GLenum>(GL_RGB),
                       static_cast<GLenum>(GL_FLOAT), nullptr);
        }
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, static_cast<GLenum>(GL_TEXTURE_MIN_FILTER), GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, static_cast<GLenum>(GL_TEXTURE_MAG_FILTER), GL_LINEAR);

        //Set up projection and view matrices for capturing data onto the 6 cubemap face directions
        glm::mat4 capture_projection = glm::perspective(glm::radians(90.0F), 1.0F, 0.1F, 10.0F);
        glm::mat4 capture_views[] = {
            glm::lookAt(glm::vec3(0.0F, 0.0F, 0.0F), glm::vec3( 1.0F,  0.0F,  0.0F), glm::vec3(0.0F, -1.0F,  0.0F)),
            glm::lookAt(glm::vec3(0.0F, 0.0F, 0.0F), glm::vec3(-1.0F,  0.0F,  0.0F), glm::vec3(0.0F, -1.0F,  0.0F)),
            glm::lookAt(glm::vec3(0.0F, 0.0F, 0.0F), glm::vec3( 0.0F,  1.0F,  0.0F), glm::vec3(0.0F,  0.0F,  1.0F)),
            glm::lookAt(glm::vec3(0.0F, 0.0F, 0.0F), glm::vec3( 0.0F, -1.0F,  0.0F), glm::vec3(0.0F,  0.0F, -1.0F)),
            glm::lookAt(glm::vec3(0.0F, 0.0F, 0.0F), glm::vec3( 0.0F,  0.0F,  1.0F), glm::vec3(0.0F, -1.0F,  0.0F)),
            glm::lookAt(glm::vec3(0.0F, 0.0F, 0.0F), glm::vec3( 0.0F,  0.0F, -1.0F), glm::vec3(0.0F, -1.0F,  0.0F))
        };

        //Convert HDR equirectangular environment map to cubemap equivalent
        equirectangular_to_cubemap_shader.BindProgram();
        equirectangular_to_cubemap_shader.SetUniform1i("equirectangularMap", static_cast<int>(hdr_texture));
        equirectangular_to_cubemap_shader.SetUniformMatrix4fv("projection", 1, GL_FALSE, capture_projection);
        glActiveTexture(GL_TEXTURE0 + hdr_texture);
        glBindTexture(GL_TEXTURE_2D, hdr_texture);
        glViewport(0, 0, 512, 512);
        glBindFramebuffer(GL_FRAMEBUFFER, capture_fbo);
        for (std::size_t i = 0U; i < 6U; ++i) {
          equirectangular_to_cubemap_shader.SetUniformMatrix4fv("view", 1, GL_FALSE, capture_views[i]);
          glFramebufferTexture2D(GL_FRAMEBUFFER, static_cast<GLenum>(GL_COLOR_ATTACHMENT0),
                                 static_cast<GLenum>(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i), env_cube_map, 0);
          glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
          RenderCube();
        }
        glBindBuffer(GL_FRAMEBUFFER, 0U);
        glBindTexture(GL_TEXTURE_CUBE_MAP, env_cube_map);
        glGenerateMipmap(GL_TEXTURE_CUBE_MAP);

        //Create an irradiance cubemap, and re-scale capture FBO to irradiance scale
        std::uint32_t irradiance_map;
        glGenTextures(1, &irradiance_map);
        glBindTexture(GL_TEXTURE_CUBE_MAP, irradiance_map);
        for (std::size_t i = 0U; i < 6U; i++) {
          glTexImage2D(static_cast<GLenum>(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i), 0, GL_RGB16F,
                       32, 32, 0, static_cast<GLenum>(GL_RGB), static_cast<GLenum>(GL_FLOAT), nullptr);
        }
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, static_cast<GLenum>(GL_TEXTURE_MIN_FILTER), GL_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, static_cast<GLenum>(GL_TEXTURE_MAG_FILTER), GL_LINEAR);
        glBindFramebuffer(GL_FRAMEBUFFER, capture_fbo);
        glBindRenderbuffer(GL_RENDERBUFFER, capture_rbo);
        glRenderbufferStorage(GL_RENDERBUFFER, static_cast<GLenum>(GL_DEPTH_COMPONENT24), 32, 32);

        //Solve diffuse integral by convolution to create an irradiance (cube)map
        irradiance_shader.BindProgram();
        irradiance_shader.SetUniform1i("environmentMap", static_cast<int>(env_cube_map));
        irradiance_shader.SetUniformMatrix4fv("projection", 1, false, capture_projection);
        glActiveTexture(GL_TEXTURE0 + env_cube_map);
        glBindTexture(GL_TEXTURE_CUBE_MAP, env_cube_map);
        glViewport(0, 0, 32, 32);
        glBindFramebuffer(GL_FRAMEBUFFER, capture_fbo);
        for (std::size_t i = 0U; i < 6U; ++i) {
          irradiance_shader.SetUniformMatrix4fv("view", 1, false, capture_views[i]);
          glFramebufferTexture2D(GL_FRAMEBUFFER, static_cast<GLenum>(GL_COLOR_ATTACHMENT0),
                                 static_cast<GLenum>(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i), irradiance_map, 0);
          glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
          RenderCube();
        }
        glBindFramebuffer(GL_FRAMEBUFFER, 0U);

        //Create a pre-filter cubemap, and re-scale capture FBO to pre-filter scale
        std::uint32_t prefilter_map;
        glGenTextures(1, &prefilter_map);
        glBindTexture(GL_TEXTURE_CUBE_MAP, prefilter_map);
        for (std::size_t i = 0U; i < 6U; i++) {
          glTexImage2D(static_cast<GLenum>(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i), 0, GL_RGB16F, 128, 128, 0,
                       static_cast<GLenum>(GL_RGB), static_cast<GLenum>(GL_FLOAT), nullptr);
        }
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, static_cast<GLenum>(GL_TEXTURE_MIN_FILTER), GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, static_cast<GLenum>(GL_TEXTURE_MAG_FILTER), GL_LINEAR);
        glGenerateMipmap(GL_TEXTURE_CUBE_MAP);

        //Run a quasi monte-carlo simulation on the environment lighting to creat a prefilter (cube)map
        prefilter_shader.BindProgram();
        prefilter_shader.SetUniform1i("environmentMap", static_cast<int>(env_cube_map));
        prefilter_shader.SetUniformMatrix4fv("projection", 1, false, capture_projection);
        glActiveTexture(GL_TEXTURE0 + env_cube_map);
        glBindTexture(GL_TEXTURE_CUBE_MAP, env_cube_map);
        glBindFramebuffer(GL_FRAMEBUFFER, capture_fbo);
        std::size_t max_mip_levels = 5U;
        for (std::size_t mip = 0U; mip < max_mip_levels; mip++) {
          auto mipWidth = static_cast<unsigned int>(128.0F * std::pow(0.5F, mip));
          auto mipHeight = static_cast<unsigned int>(128.0F * std::pow(0.5F, mip));
          glBindRenderbuffer(GL_RENDERBUFFER, capture_rbo);
          glRenderbufferStorage(GL_RENDERBUFFER, static_cast<GLenum>(GL_DEPTH_COMPONENT24),
                                static_cast<std::int32_t>(mipWidth), static_cast<std::int32_t>(mipHeight));
          glViewport(0, 0, static_cast<std::int32_t>(mipWidth), static_cast<std::int32_t>(mipHeight));
          float roughness = static_cast<float>(mip) / static_cast<float>(max_mip_levels - 1U);
          prefilter_shader.SetUniform1f("roughness", roughness);
          for (std::size_t i = 0U; i < 6U; i++) {
            prefilter_shader.SetUniformMatrix4fv("view", 1, false, capture_views[i]);
            glFramebufferTexture2D(GL_FRAMEBUFFER, static_cast<GLenum>(GL_COLOR_ATTACHMENT0),
                                   static_cast<GLenum>(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i),
                                   prefilter_map, static_cast<std::int32_t>(mip));
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            RenderCube();
          }
        }
        glBindFramebuffer(GL_FRAMEBUFFER, 0U);

        //Generate a 2D LUT from the BRDF equations used.
        std::uint32_t brdf_lut_texture;
        glGenTextures(1, &brdf_lut_texture);
        glBindTexture(GL_TEXTURE_2D, brdf_lut_texture);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RG16F, 512, 512, 0,
                     static_cast<GLenum>(GL_RG), static_cast<GLenum>(GL_FLOAT), nullptr);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, static_cast<GLenum>(GL_TEXTURE_MIN_FILTER), GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, static_cast<GLenum>(GL_TEXTURE_MAG_FILTER), GL_LINEAR);
        glBindFramebuffer(GL_FRAMEBUFFER, capture_fbo);
        glBindRenderbuffer(GL_RENDERBUFFER, capture_rbo);
        glRenderbufferStorage(GL_RENDERBUFFER, static_cast<GLenum>(GL_DEPTH_COMPONENT24), 512, 512);
        glFramebufferTexture2D(GL_FRAMEBUFFER, static_cast<GLenum>(GL_COLOR_ATTACHMENT0),
                               GL_TEXTURE_2D, brdf_lut_texture, 0);
        glViewport(0, 0, 512, 512);
        brdf_shader.BindProgram();
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        RenderQuad();
        glBindFramebuffer(GL_FRAMEBUFFER, 0U);

        glfwGetFramebufferSize(window, &screen_width, &screen_height);
        glViewport(0, 0, screen_width, screen_height);

        //Camera
        Camera camera(glm::vec3(3.0F, 0.5F, 1.75F),
                      glm::vec3(0.0F, 1.0F, 0.0F),
                      212.5F, 350.0F, 45.0F,
                      0.1F, 100.0F);

        //Main loop
        while (glfwWindowShouldClose(window) == GLFW_FALSE) {
          //TEMPORARY: Input handling
          camera.HandleInput(input_manager);
          camera.Update();
          input_manager.update();

          //TEMPORARY: Render
          glClearColor(0.1F, 0.1F, 0.1F, 1.0F);
          glClear(static_cast<GLenum>(GL_COLOR_BUFFER_BIT) | static_cast<GLenum>(GL_DEPTH_BUFFER_BIT));

          default_shader.BindProgram();

          const Node& node = gltf.nodes_[0U];
          glm::vec3 translate(node.translation_[0U], node.translation_[1U], node.translation_[2U]);
          glm::quat rotate(node.rotation_[3U], node.rotation_[0U], node.rotation_[1U], node.rotation_[2U]);
          glm::vec3 scale(node.scale_[0U], node.scale_[1U], node.scale_[2U]);
          glm::mat4 T = glm::translate(glm::mat4(1.0F), translate);
          glm::mat4 R = glm::toMat4(rotate);
          glm::mat4 S = glm::scale(glm::mat4(1.0F), scale);
          glm::mat4 model = T * R * S;
          default_shader.SetUniformMatrix4fv("model", 1, false, model);

          glm::mat4 view = camera.GetViewMatrix();
          default_shader.SetUniformMatrix4fv("view", 1, false, view);

          glm::mat4 projection = camera.GetProjectionMatrix(static_cast<float>(screen_width) / static_cast<float>(screen_height));
          default_shader.SetUniformMatrix4fv("projection", 1, false, projection);

          default_shader.SetUniform1i("albedoMap", static_cast<int>(albedo));
          glActiveTexture(GL_TEXTURE0 + albedo);
          glBindTexture(GL_TEXTURE_2D, albedo);

          default_shader.SetUniform1i("AOMap", static_cast<int>(ambient_occlusion));
          glActiveTexture(GL_TEXTURE0 + ambient_occlusion);
          glBindTexture(GL_TEXTURE_2D, ambient_occlusion);

          default_shader.SetUniform1i("emissiveMap", static_cast<int>(emissive));
          glActiveTexture(GL_TEXTURE0 + emissive);
          glBindTexture(GL_TEXTURE_2D, emissive);

          default_shader.SetUniform1i("metalRoughnessMap", static_cast<int>(metal_roughness));
          glActiveTexture(GL_TEXTURE0 + metal_roughness);
          glBindTexture(GL_TEXTURE_2D, metal_roughness);

          default_shader.SetUniform1i("normalMap", static_cast<int>(normal));
          glActiveTexture(GL_TEXTURE0 + normal);
          glBindTexture(GL_TEXTURE_2D, normal);

          default_shader.SetUniform3fv("viewPos", 1, camera.position_);

          const Mesh& mesh = gltf.meshes_[0U];
          const MeshPrimitive& primitive = mesh.primitives_[0U];
          const Accessor& index_accessor = gltf.accessors_[static_cast<std::size_t>(primitive.indices_)];

          glBindVertexArray(primitive.vao_);
          glDrawElements(static_cast<GLenum>(primitive.mode_),
                         static_cast<GLsizei>(index_accessor.count_),
                         static_cast<GLenum>(index_accessor.component_type_),
                         static_cast<char*>(nullptr) + index_accessor.byte_offset_);

          default_shader.SetUniform1i("irradianceMap", static_cast<int>(irradiance_map));
          glActiveTexture(GL_TEXTURE0 + irradiance_map);
          glBindTexture(GL_TEXTURE_CUBE_MAP, irradiance_map);

          default_shader.SetUniform1i("prefilterMap", static_cast<int>(prefilter_map));
          glActiveTexture(GL_TEXTURE0 + prefilter_map);
          glBindTexture(GL_TEXTURE_CUBE_MAP, prefilter_map);

          default_shader.SetUniform1i("brdfLUT", static_cast<int>(brdf_lut_texture));
          glActiveTexture(GL_TEXTURE0 + brdf_lut_texture);
          glBindTexture(GL_TEXTURE_2D, brdf_lut_texture);

          background_shader.BindProgram();
          background_shader.SetUniformMatrix4fv("projection", 1, false, projection);
          background_shader.SetUniform1i("environmentMap", static_cast<std::int32_t>(env_cube_map));
          background_shader.SetUniformMatrix4fv("view", 1, false, view);
          glActiveTexture(GL_TEXTURE0 + env_cube_map);
          glBindTexture(GL_TEXTURE_CUBE_MAP, env_cube_map);
          RenderCube();

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

std::uint32_t LoadTexture(const std::string& path) {
  std::uint32_t texture;
  glGenTextures(1, &texture);
  int width;
  int height;
  int num_components;
  std::uint8_t* data = stbi_load(path.c_str(), &width, &height, &num_components, 0);
  if (data != nullptr) {
    int format;
    if (num_components == 1) {
      format = GL_RED;
    } else if (num_components == 3) {
      format = GL_RGB;
    } else {
      format = GL_RGBA;
    }
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, static_cast<GLenum>(format), GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, format == GL_RGBA ? GL_CLAMP_TO_EDGE : GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, format == GL_RGBA ? GL_CLAMP_TO_EDGE : GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, static_cast<GLenum>(GL_TEXTURE_MIN_FILTER), GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, static_cast<GLenum>(GL_TEXTURE_MAG_FILTER), GL_LINEAR);
  } else {
    std::cerr << "Failed to load shader at: " << path << std::endl;
  }
  stbi_image_free(data);
  return texture;
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

void RenderCube()
{
  // initialize (if necessary)
  if (cubeVAO_ == 0U)
  {
    float vertices[] = {
        // back face
        -1.0F, -1.0F, -1.0F,  0.0F,  0.0F, -1.0F, 0.0F, 0.0F, // bottom-left
        1.0F,  1.0F, -1.0F,  0.0F,  0.0F, -1.0F, 1.0F, 1.0F, // top-right
        1.0F, -1.0F, -1.0F,  0.0F,  0.0F, -1.0F, 1.0F, 0.0F, // bottom-right
        1.0F,  1.0F, -1.0F,  0.0F,  0.0F, -1.0F, 1.0F, 1.0F, // top-right
        -1.0F, -1.0F, -1.0F,  0.0F,  0.0F, -1.0F, 0.0F, 0.0F, // bottom-left
        -1.0F,  1.0F, -1.0F,  0.0F,  0.0F, -1.0F, 0.0F, 1.0F, // top-left
        // front face
        -1.0F, -1.0F,  1.0F,  0.0F,  0.0F,  1.0F, 0.0F, 0.0F, // bottom-left
        1.0F, -1.0F,  1.0F,  0.0F,  0.0F,  1.0F, 1.0F, 0.0F, // bottom-right
        1.0F,  1.0F,  1.0F,  0.0F,  0.0F,  1.0F, 1.0F, 1.0F, // top-right
        1.0F,  1.0F,  1.0F,  0.0F,  0.0F,  1.0F, 1.0F, 1.0F, // top-right
        -1.0F,  1.0F,  1.0F,  0.0F,  0.0F,  1.0F, 0.0F, 1.0F, // top-left
        -1.0F, -1.0F,  1.0F,  0.0F,  0.0F,  1.0F, 0.0F, 0.0F, // bottom-left
        // left face
        -1.0F,  1.0F,  1.0F, -1.0F,  0.0F,  0.0F, 1.0F, 0.0F, // top-right
        -1.0F,  1.0F, -1.0F, -1.0F,  0.0F,  0.0F, 1.0F, 1.0F, // top-left
        -1.0F, -1.0F, -1.0F, -1.0F,  0.0F,  0.0F, 0.0F, 1.0F, // bottom-left
        -1.0F, -1.0F, -1.0F, -1.0F,  0.0F,  0.0F, 0.0F, 1.0F, // bottom-left
        -1.0F, -1.0F,  1.0F, -1.0F,  0.0F,  0.0F, 0.0F, 0.0F, // bottom-right
        -1.0F,  1.0F,  1.0F, -1.0F,  0.0F,  0.0F, 1.0F, 0.0F, // top-right
        // right face
        1.0F,  1.0F,  1.0F,  1.0F,  0.0F,  0.0F, 1.0F, 0.0F, // top-left
        1.0F, -1.0F, -1.0F,  1.0F,  0.0F,  0.0F, 0.0F, 1.0F, // bottom-right
        1.0F,  1.0F, -1.0F,  1.0F,  0.0F,  0.0F, 1.0F, 1.0F, // top-right
        1.0F, -1.0F, -1.0F,  1.0F,  0.0F,  0.0F, 0.0F, 1.0F, // bottom-right
        1.0F,  1.0F,  1.0F,  1.0F,  0.0F,  0.0F, 1.0F, 0.0F, // top-left
        1.0F, -1.0F,  1.0F,  1.0F,  0.0F,  0.0F, 0.0F, 0.0F, // bottom-left
        // bottom face
        -1.0F, -1.0F, -1.0F,  0.0F, -1.0F,  0.0F, 0.0F, 1.0F, // top-right
        1.0F, -1.0F, -1.0F,  0.0F, -1.0F,  0.0F, 1.0F, 1.0F, // top-left
        1.0F, -1.0F,  1.0F,  0.0F, -1.0F,  0.0F, 1.0F, 0.0F, // bottom-left
        1.0F, -1.0F,  1.0F,  0.0F, -1.0F,  0.0F, 1.0F, 0.0F, // bottom-left
        -1.0F, -1.0F,  1.0F,  0.0F, -1.0F,  0.0F, 0.0F, 0.0F, // bottom-right
        -1.0F, -1.0F, -1.0F,  0.0F, -1.0F,  0.0F, 0.0F, 1.0F, // top-right
        // top face
        -1.0F,  1.0F, -1.0F,  0.0F,  1.0F,  0.0F, 0.0F, 1.0F, // top-left
        1.0F,  1.0F , 1.0F,  0.0F,  1.0F,  0.0F, 1.0F, 0.0F, // bottom-right
        1.0F,  1.0F, -1.0F,  0.0F,  1.0F,  0.0F, 1.0F, 1.0F, // top-right
        1.0F,  1.0F,  1.0F,  0.0F,  1.0F,  0.0F, 1.0F, 0.0F, // bottom-right
        -1.0F,  1.0F, -1.0F,  0.0F,  1.0F,  0.0F, 0.0F, 1.0F, // top-left
        -1.0F,  1.0F,  1.0F,  0.0F,  1.0F,  0.0F, 0.0F, 0.0F  // bottom-left
    };
    glGenVertexArrays(1, &cubeVAO_);
    glGenBuffers(1, &cubeVBO_);
    // fill buffer
    glBindBuffer(GL_ARRAY_BUFFER, cubeVBO_);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    // link vertex attributes
    glBindVertexArray(cubeVAO_);
    glEnableVertexAttribArray(0U);
    glVertexAttribPointer(0U, 3, static_cast<GLenum>(GL_FLOAT),
                          (GL_FALSE), 8U * sizeof(float), (void*)0U);
    glEnableVertexAttribArray(1U);
    glVertexAttribPointer(1U, 3, static_cast<GLenum>(GL_FLOAT),
                          GL_FALSE, 8U * sizeof(float), (void*)(3U * sizeof(float)));
    glEnableVertexAttribArray(2U);
    glVertexAttribPointer(2U, 2, static_cast<GLenum>(GL_FLOAT),
                          GL_FALSE, 8U * sizeof(float), (void*)(6U * sizeof(float)));
    glBindBuffer(GL_ARRAY_BUFFER, 0U);
    glBindVertexArray(0U);
  }
  // render Cube
  glBindVertexArray(cubeVAO_);
  glDrawArrays(static_cast<GLenum>(GL_TRIANGLES), 0, 36);
  glBindVertexArray(0U);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
  // make sure the viewport matches the new window dimensions; note that width and
  // height will be significantly larger than specified on retina displays.
  glViewport(0, 0, width, height);
}
void RenderQuad()
{
  if (quadVAO_ == 0U)
  {
    float quadVertices[] = {
        // positions        // texture Coords
        -1.0F,  1.0F, 0.0F, 0.0F, 1.0F,
        -1.0F, -1.0F, 0.0F, 0.0F, 0.0F,
        1.0F,  1.0F, 0.0F, 1.0F, 1.0F,
        1.0F, -1.0F, 0.0F, 1.0F, 0.0F,
    };
    // setup plane VAO
    glGenVertexArrays(1, &quadVAO_);
    glGenBuffers(1, &quadVBO_);
    glBindVertexArray(quadVAO_);
    glBindBuffer(GL_ARRAY_BUFFER, quadVBO_);
    glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, static_cast<GLenum>(GL_STATIC_DRAW));
    glEnableVertexAttribArray(0U);
    glVertexAttribPointer(0U, 3, static_cast<GLenum>(GL_FLOAT), static_cast<GLboolean>(GL_FALSE)
        , 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1U);
    glVertexAttribPointer(1U, 2, static_cast<GLenum>(GL_FLOAT), static_cast<GLboolean>(GL_FALSE)
        , 5 * sizeof(float), (void*)(3 * sizeof(float)));
  }
  glBindVertexArray(quadVAO_);
  glDrawArrays(static_cast<GLenum>(GL_TRIANGLE_STRIP), 0, 4);
  glBindVertexArray(0U);
}