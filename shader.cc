#include "shader.h"

#include <fstream>
#include <iostream>
#include <sstream>

#include <glm/gtc/type_ptr.hpp>

Shader::Shader() {
  program_id_ = glCreateProgram();
}

Shader::~Shader() {
  glDeleteProgram(program_id_);
}

void Shader::BindProgram() const {
  glUseProgram(program_id_);
}

void Shader::UnbindProgram() const {
  glUseProgram(0U);
}

void Shader::AddShader(const GLenum& type, const std::string& path) {
  std::string str = ParseShaderSource(path);
  const char* c_str = str.c_str();
  uint32_t shader_id = glCreateShader(type);
  glShaderSource(shader_id, 1, &c_str, nullptr);
  glCompileShader(shader_id);
  if (!IsShaderCompiled(shader_id)) {
    std::cerr << "Failed to compile shader at: " << path << std::endl;
  } else {
    shader_ids_.push_back(shader_id);
  }
}

void Shader::CreateProgram() {
  for (const auto& shader_id : shader_ids_) {
    glAttachShader(program_id_, shader_id);
  }

  glLinkProgram(program_id_);
  if (!IsProgramLinked()) {
    std::cerr << "Failed to link shader program" << std::endl;
  }

  glValidateProgram(program_id_);
  if (!IsProgramValidated()) {
    std::cerr << "Failed to validate shader program" << std::endl;
  }

  for (const auto& shader_id : shader_ids_) {
    glDetachShader(program_id_, shader_id);
    glDeleteShader(shader_id);
  }

  shader_ids_.clear();
}

void Shader::SetUniform1f(const std::string& name, const float& value) {
  glUniform1f(GetUniformLocation(name), value);
}

void Shader::SetUniform2f(const std::string& name, const glm::vec2& value) {
  glUniform2f(GetUniformLocation(name), value.x, value.y);
}

void Shader::SetUniform3f(const std::string& name, const glm::vec3& value) {
  glUniform3f(GetUniformLocation(name), value.x, value.y, value.z);
}

void Shader::SetUniform4f(const std::string& name, const glm::vec4& value) {
  glUniform4f(GetUniformLocation(name), value.x, value.y, value.z, value.w);
}

void Shader::SetUniform1i(const std::string& name, const std::int32_t& value) {
  glUniform1i(GetUniformLocation(name), value);
}

void Shader::SetUniform2i(const std::string& name, const glm::ivec2& value) {
  glUniform2i(GetUniformLocation(name), value.x, value.y);
}

void Shader::SetUniform3i(const std::string& name, const glm::ivec3& value) {
  glUniform3i(GetUniformLocation(name), value.x, value.y, value.z);
}

void Shader::SetUniform4i(const std::string& name, const glm::ivec4& value) {
  glUniform4i(GetUniformLocation(name), value.x, value.y, value.z, value.w);
}

void Shader::SetUniform1ui(const std::string& name, const std::uint32_t& value) {
  glUniform1ui(GetUniformLocation(name), value);
}

void Shader::SetUniform2ui(const std::string& name, const glm::uvec2& value) {
  glUniform2ui(GetUniformLocation(name), value.x, value.y);
}

void Shader::SetUniform3ui(const std::string& name, const glm::uvec3& value) {
  glUniform3ui(GetUniformLocation(name), value.x, value.y, value.z);
}

void Shader::SetUniform4ui(const std::string& name, const glm::uvec4& value) {
  glUniform4ui(GetUniformLocation(name), value.x, value.y, value.z, value.w);
}

void Shader::SetUniform1fv(const std::string& name, std::int32_t count, const float* value) {
  glUniform1fv(GetUniformLocation(name), count, value);
}

void Shader::SetUniform2fv(const std::string& name, std::int32_t count, const glm::vec2& value) {
  glUniform2fv(GetUniformLocation(name), count, glm::value_ptr(value));
}

void Shader::SetUniform3fv(const std::string& name, std::int32_t count, const glm::vec3& value) {
  glUniform3fv(GetUniformLocation(name), count, glm::value_ptr(value));
}

void Shader::SetUniform4fv(const std::string& name, std::int32_t count, const glm::vec4& value) {
  glUniform4fv(GetUniformLocation(name), count, glm::value_ptr(value));
}

void Shader::SetUniform1iv(const std::string& name, std::int32_t count, const std::int32_t* value) {
  glUniform1iv(GetUniformLocation(name), count, value);
}

void Shader::SetUniform2iv(const std::string& name, std::int32_t count, const glm::ivec2& value) {
  glUniform2iv(GetUniformLocation(name), count, glm::value_ptr(value));
}

void Shader::SetUniform3iv(const std::string& name, std::int32_t count, const glm::ivec3& value) {
  glUniform3iv(GetUniformLocation(name), count, glm::value_ptr(value));
}

void Shader::SetUniform4iv(const std::string& name, std::int32_t count, const glm::ivec4& value) {
  glUniform4iv(GetUniformLocation(name), count, glm::value_ptr(value));
}

void Shader::SetUniform1uiv(const std::string& name, std::int32_t count, const std::uint32_t* value) {
  glUniform1uiv(GetUniformLocation(name), count, value);
}

void Shader::SetUniform2uiv(const std::string& name, std::int32_t count, const glm::uvec2& value) {
  glUniform2uiv(GetUniformLocation(name), count, glm::value_ptr(value));
}

void Shader::SetUniform3uiv(const std::string& name, std::int32_t count, const glm::uvec3& value) {
  glUniform3uiv(GetUniformLocation(name), count, glm::value_ptr(value));
}

void Shader::SetUniform4uiv(const std::string& name, std::int32_t count, const glm::uvec4& value) {
  glUniform4uiv(GetUniformLocation(name), count, glm::value_ptr(value));
}

void Shader::SetUniformMatrix2fv(const std::string& name, std::int32_t count, bool transpose,
                                 const glm::mat2& value) {
  glUniformMatrix2fv(GetUniformLocation(name), count, transpose, glm::value_ptr(value));
}

void Shader::SetUniformMatrix3fv(const std::string& name, std::int32_t count, bool transpose,
                                 const glm::mat3& value) {
  glUniformMatrix3fv(GetUniformLocation(name), count, transpose, glm::value_ptr(value));
}

void Shader::SetUniformMatrix4fv(const std::string& name, std::int32_t count, bool transpose,
                                 const glm::mat4& value) {
  glUniformMatrix4fv(GetUniformLocation(name), count, transpose, glm::value_ptr(value));
}

void Shader::SetUniformMatrix2x3fv(const std::string& name, std::int32_t count, bool transpose,
                                   const glm::mat2x3& value) {
  glUniformMatrix2x3fv(GetUniformLocation(name), count, transpose, glm::value_ptr(value));
}

void Shader::SetUniformMatrix3x2fv(const std::string& name, std::int32_t count, bool transpose,
                                   const glm::mat3x2& value) {
  glUniformMatrix3x2fv(GetUniformLocation(name), count, transpose, glm::value_ptr(value));
}

void Shader::SetUniformMatrix2x4fv(const std::string& name, std::int32_t count, bool transpose,
                                   const glm::mat2x4& value) {
  glUniformMatrix2x4fv(GetUniformLocation(name), count, transpose, glm::value_ptr(value));
}

void Shader::SetUniformMatrix4x2fv(const std::string& name, std::int32_t count, bool transpose,
                                   const glm::mat4x2& value) {
  glUniformMatrix4x2fv(GetUniformLocation(name), count, transpose, glm::value_ptr(value));
}

void Shader::SetUniformMatrix3x4fv(const std::string& name, std::int32_t count, bool transpose,
                                   const glm::mat3x4& value) {
  glUniformMatrix3x4fv(GetUniformLocation(name), count, transpose, glm::value_ptr(value));
}

void Shader::SetUniformMatrix4x3fv(const std::string& name, std::int32_t count, bool transpose,
                                   const glm::mat4x3& value) {
  glUniformMatrix4x3fv(GetUniformLocation(name), count, transpose, glm::value_ptr(value));
}

std::string Shader::ParseShaderSource(const std::string& path) const {
  std::stringstream stream;
  std::ifstream file(path);
  if (file.fail()) {
    std::cerr << "Failed to read shader file at: " << path << std::endl;
  } else {
    stream << file.rdbuf();
    file.close();
  }
  return stream.str();
}

bool Shader::IsShaderCompiled(const std::uint32_t& shader_id) const {
  int is_compiled;
  glGetShaderiv(shader_id, static_cast<GLenum>(GL_COMPILE_STATUS), &is_compiled);
  return is_compiled;
}

bool Shader::IsProgramLinked() const {
  int is_linked;
  glGetProgramiv(program_id_, static_cast<GLenum>(GL_LINK_STATUS), &is_linked);
  return is_linked;
}

bool Shader::IsProgramValidated() const {
  int is_validated;
  glGetProgramiv(program_id_, static_cast<GLenum>(GL_VALIDATE_STATUS), &is_validated);
  return is_validated;
}

int Shader::GetUniformLocation(const std::string& name) {
  if (uniform_locations_.find(name) == uniform_locations_.end()) {
    (void)uniform_locations_.emplace(name, glGetUniformLocation(program_id_, name.c_str()));
  }
  return uniform_locations_[name];
}
