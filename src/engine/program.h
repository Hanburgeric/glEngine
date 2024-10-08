#ifndef GLENGINE_SRC_ENGINE_PROGRAM_H_
#define GLENGINE_SRC_ENGINE_PROGRAM_H_

// System headers
#include <string>
#include <unordered_map>

// User headers
#include "shader.h"

namespace glEngine {
class Program {
 public:
  Program();
  ~Program();

  void AddShader(const Shader& shader);

  void Link() const;

  void PrintLinkStatus() const;

  [[nodiscard]] unsigned int GetId() const;

  int GetUniformLocation(const std::string& name);

 private:
  unsigned int id_;

  std::unordered_map<std::string, int> uniforms_;
};
}

#endif //GLENGINE_SRC_ENGINE_PROGRAM_H_
