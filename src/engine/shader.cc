#include "shader.h"

// System headers
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

// Vendor headers
#include "glad/gl.h"

namespace glEngine::renderer {
Shader::Shader(GLenum shader_type, const std::string &file_name) {
  // Create shader
  shader_ = glCreateShader(shader_type);

  // Open shader file
  std::ifstream file(file_name);

  if (!file) {
    std::cerr << "Failed to open shader file at " << file_name << std::endl;
    return;
  }

  // Cache shader text
  std::stringstream stream;
  stream << file.rdbuf();
  std::string str = stream.str();
  const char* c_str = str.c_str();

  // Compile shader
  glShaderSource(shader_, 1, &c_str, nullptr);
  glCompileShader(shader_);

  // Log info
  int success;
  glGetShaderiv(shader_, GL_COMPILE_STATUS, &success);

  if (!success) {
    int info_log_length;
    glGetShaderiv(shader_, GL_INFO_LOG_LENGTH, &info_log_length);

    std::string info_log;
    info_log.resize(info_log_length);

    std::cerr << "Failed to compile shader file at " << file_name << std::endl;
    glGetShaderInfoLog(shader_, info_log_length, nullptr, &info_log[0U]);
    std::cerr << info_log << std::endl;
  }
}

Shader::~Shader() {
  glDeleteShader(shader_);
}

unsigned int Shader::GetShader() const {
  return shader_;
}
}
