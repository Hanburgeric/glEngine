#ifndef GLENGINE_SRC_ENGINE_PROGRAM_H_
#define GLENGINE_SRC_ENGINE_PROGRAM_H_

// System headers
#include <initializer_list>
#include <string>
#include <unordered_map>

// User headers
#include "shader.h"

namespace glEngine::renderer {
class Program {
 public:
  Program(const std::initializer_list<Shader>& shaders);
  ~Program();

  [[nodiscard]] unsigned int GetProgram() const;

  int GetUniformLocation(const std::string& name);

 private:
  unsigned int program_;
  std::unordered_map<std::string, int> uniforms_;
};
}

#endif //GLENGINE_SRC_ENGINE_PROGRAM_H_
