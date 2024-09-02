#include "program.h"

// System headers
#include <initializer_list>
#include <iostream>
#include <string>

// Vendor headers
#include "glad/gl.h"

// User headers
#include "shader.h"

namespace glEngine::renderer {
Program::Program(std::initializer_list<Shader> shaders) {
  // Create program
  program_ = glCreateProgram();

  // Link program
  for (const Shader& shader : shaders) {
    glAttachShader(program_, shader.GetShader());
  }

  glLinkProgram(program_);

  // Log info
  int success;
  glGetProgramiv(program_, GL_LINK_STATUS, &success);

  if (!success) {
    int info_log_length;
    glGetProgramiv(program_, GL_INFO_LOG_LENGTH, &info_log_length);

    std::string info_log;
    info_log.resize(info_log_length);

    std::cerr << "Failed to link program" << std::endl;
    glGetProgramInfoLog(program_, info_log_length, nullptr, &info_log[0U]);
    std::cerr << info_log << std::endl;
  }
}

Program::~Program() {
  glDeleteProgram(program_);
}

unsigned int Program::GetProgram() const {
  return program_;
}
}
