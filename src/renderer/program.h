#ifndef GLENGINE_SRC_RENDERER_PROGRAM_H_
#define GLENGINE_SRC_RENDERER_PROGRAM_H_

// System headers
#include <initializer_list>

// User headers
#include "shader.h"

namespace glEngine::renderer {
class Program {
 public:
  Program(std::initializer_list<Shader> shaders);
  ~Program();

  [[nodiscard]] unsigned int GetProgram() const;

 private:
  unsigned int program_;
};
}

#endif //GLENGINE_SRC_RENDERER_PROGRAM_H_
