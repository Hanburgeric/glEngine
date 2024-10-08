#ifndef GLENGINE_SRC_ENGINE_CUBE_H_
#define GLENGINE_SRC_ENGINE_CUBE_H_

// Vendor headers
#include "glm/vec3.hpp"

// User headers
#include "primitive.h"

namespace glEngine {
class Cube : public Primitive {
 public:
  explicit Cube(const glm::vec3 &position = glm::vec3());
};
}

#endif //GLENGINE_SRC_ENGINE_CUBE_H_
