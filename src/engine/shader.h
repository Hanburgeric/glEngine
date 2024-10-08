#ifndef GLENGINE_SRC_ENGINE_SHADER_H_
#define GLENGINE_SRC_ENGINE_SHADER_H_

// System headers
#include <string>
#include <vector>

// Vendor headers
#include "glad/gl.h"

namespace glEngine {
class Shader {
 public:
  Shader(unsigned int shader_type);
  ~Shader();

  void AddSource(const std::string& file_name);

  void Compile() const;

  void PrintCompileStatus() const;

  [[nodiscard]] unsigned int GetId() const;

 private:
  unsigned int id_;

  std::vector<std::string> srcs_;
};
}

#endif //GLENGINE_SRC_ENGINE_SHADER_H_
