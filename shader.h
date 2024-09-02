#ifndef GRAPICAR__SHADER_H_
#define GRAPICAR__SHADER_H_

#include <cstdint>
#include <string>
#include <unordered_map>
#include <vector>

#include <glad/gl.h>

#include <glm/matrix.hpp>

class Shader {
 public:
  Shader();
  ~Shader();

  void BindProgram() const;
  void UnbindProgram() const;

  void AddShader(const GLenum& type, const std::string& path);

  void CreateProgram();

  void SetUniform1f(const std::string& name, const float& value);
  void SetUniform2f(const std::string& name, const glm::vec2& value);
  void SetUniform3f(const std::string& name, const glm::vec3& value);
  void SetUniform4f(const std::string& name, const glm::vec4& value);

  void SetUniform1i(const std::string& name, const std::int32_t& value);
  void SetUniform2i(const std::string& name, const glm::ivec2& value);
  void SetUniform3i(const std::string& name, const glm::ivec3& value);
  void SetUniform4i(const std::string& name, const glm::ivec4& value);

  void SetUniform1ui(const std::string& name, const std::uint32_t& value);
  void SetUniform2ui(const std::string& name, const glm::uvec2& value);
  void SetUniform3ui(const std::string& name, const glm::uvec3& value);
  void SetUniform4ui(const std::string& name, const glm::uvec4& value);

  void SetUniform1fv(const std::string& name, std::int32_t count, const float* value);
  void SetUniform2fv(const std::string& name, std::int32_t count, const glm::vec2& value);
  void SetUniform3fv(const std::string& name, std::int32_t count, const glm::vec3& value);
  void SetUniform4fv(const std::string& name, std::int32_t count, const glm::vec4& value);

  void SetUniform1iv(const std::string& name, std::int32_t count, const std::int32_t* value);
  void SetUniform2iv(const std::string& name, std::int32_t count, const glm::ivec2& value);
  void SetUniform3iv(const std::string& name, std::int32_t count, const glm::ivec3& value);
  void SetUniform4iv(const std::string& name, std::int32_t count, const glm::ivec4& value);

  void SetUniform1uiv(const std::string& name, std::int32_t count, const std::uint32_t* value);
  void SetUniform2uiv(const std::string& name, std::int32_t count, const glm::uvec2& value);
  void SetUniform3uiv(const std::string& name, std::int32_t count, const glm::uvec3& value);
  void SetUniform4uiv(const std::string& name, std::int32_t count, const glm::uvec4& value);

  void SetUniformMatrix2fv(const std::string& name, std::int32_t count, bool transpose, const glm::mat2& value);
  void SetUniformMatrix3fv(const std::string& name, std::int32_t count, bool transpose, const glm::mat3& value);
  void SetUniformMatrix4fv(const std::string& name, std::int32_t count, bool transpose, const glm::mat4& value);
  void SetUniformMatrix2x3fv(const std::string& name, std::int32_t count, bool transpose, const glm::mat2x3& value);
  void SetUniformMatrix3x2fv(const std::string& name, std::int32_t count, bool transpose, const glm::mat3x2& value);
  void SetUniformMatrix2x4fv(const std::string& name, std::int32_t count, bool transpose, const glm::mat2x4& value);
  void SetUniformMatrix4x2fv(const std::string& name, std::int32_t count, bool transpose, const glm::mat4x2& value);
  void SetUniformMatrix3x4fv(const std::string& name, std::int32_t count, bool transpose, const glm::mat3x4& value);
  void SetUniformMatrix4x3fv(const std::string& name, std::int32_t count, bool transpose, const glm::mat4x3& value);

// private:
  std::string ParseShaderSource(const std::string& path) const;

  bool IsShaderCompiled(const std::uint32_t& shader_id) const;

  bool IsProgramLinked() const;
  bool IsProgramValidated() const;

  int GetUniformLocation(const std::string& name);

  std::uint32_t program_id_;
  std::vector<std::uint32_t> shader_ids_;
  std::unordered_map<std::string, std::int32_t> uniform_locations_;
};

#endif //GRAPICAR__SHADER_H_
