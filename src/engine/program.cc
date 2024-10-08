#include "program.h"

// System headers
#include <iostream>
#include <string>
#include <unordered_map>

// Vendor headers
#include "glad/gl.h"

// User headers
#include "shader.h"

namespace glEngine {
Program::Program() {
  id_ = glCreateProgram();
}

Program::~Program() {
  glDeleteProgram(id_);
}

void Program::AddShader(const Shader& shader) {
  glAttachShader(id_, shader.GetId());
}

void Program::Link() const {
  glLinkProgram(id_);
  PrintLinkStatus();
}

void Program::PrintLinkStatus() const {
  int success;
  glGetProgramiv(id_, GL_LINK_STATUS, &success);

  if (!success) {
    int info_log_length;
    glGetProgramiv(id_, GL_INFO_LOG_LENGTH, &info_log_length);

    std::string info_log;
    info_log.resize(info_log_length);

    std::cerr << "Failed to link program" << std::endl;
    glGetProgramInfoLog(id_, info_log_length, nullptr, &info_log[0U]);
    std::cerr << info_log << std::endl;
  }
}

unsigned int Program::GetId() const {
  return id_;
}

int Program::GetUniformLocation(const std::string& name) {
  if (uniforms_.find(name) == uniforms_.end()) {
    (void)uniforms_.emplace(name, glGetUniformLocation(id_, name.c_str()));
  }
  return uniforms_[name];
}
}
