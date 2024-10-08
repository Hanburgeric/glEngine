#include "shader.h"

// System headers
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

// Vendor headers
#include "glad/gl.h"

namespace glEngine {
Shader::Shader(unsigned int shader_type) {
  id_ = glCreateShader(shader_type);
}

void Shader::AddSource(const std::string& file_name) {
  std::ifstream file(file_name);

  if (!file) {
    std::cerr << "Failed to open shader file at " << file_name << std::endl;
    return;
  }

  std::stringstream stream;
  stream << file.rdbuf();
  (void)srcs_.emplace_back(stream.str());
}

Shader::~Shader() {
  glDeleteShader(id_);
}

void Shader::Compile() const {
  // TODO : refactor O(n) space complexity
  std::vector<const char*> c_srcs;
  c_srcs.reserve(srcs_.size());
  for (const auto& src : srcs_) {
    (void)c_srcs.emplace_back(src.c_str());
  }
  glShaderSource(id_, c_srcs.size(), &c_srcs[0U], nullptr);
  glCompileShader(id_);
  PrintCompileStatus();
}

void Shader::PrintCompileStatus() const {
  int success;
  glGetShaderiv(id_, GL_COMPILE_STATUS, &success);

  if (!success) {
    int info_log_length;
    glGetShaderiv(id_, GL_INFO_LOG_LENGTH, &info_log_length);

    std::string info_log;
    info_log.resize(info_log_length);

    std::cerr << "Failed to compile shader" << std::endl;
    glGetShaderInfoLog(id_, info_log_length, nullptr, &info_log[0U]);
    std::cerr << info_log << std::endl;
  }
}

unsigned int Shader::GetId() const {
  return id_;
}
}
