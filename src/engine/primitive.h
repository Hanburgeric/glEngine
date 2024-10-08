#ifndef GLENGINE_SRC_ENGINE_PRIMITIVE_H_
#define GLENGINE_SRC_ENGINE_PRIMITIVE_H_

// System headers
#include <array>
#include <vector>

// Vendor headers
#include "glm/vec2.hpp"
#include "glm/vec3.hpp"
#include "glm/vec4.hpp"

// User headers
#include "material.h"

namespace glEngine {
struct Vertex {
  glm::vec3 position_;
  glm::vec3 normal_;
  glm::vec4 tangent_;
  std::array<glm::vec2, 2U> tex_coords_;
  std::array<glm::vec4, 1U> colors_;
  std::array<glm::vec4, 1U> joints_;
  std::array<glm::vec4, 1U> weights_;
};

class Primitive {
 public:
  explicit Primitive(const glm::vec3& position = glm::vec3());
  ~Primitive();

  void Setup() const;

  void CalcNormals();
  void CalcTangents();

  [[nodiscard]] unsigned int GetId() const;

  [[nodiscard]] const glm::vec3& GetPosition() const;

  void Render() const;

 protected:
  std::vector<Vertex> vertices_;
  std::vector<glm::uvec3> indices_;
  Material material_;
  unsigned int mode_{4U};

  unsigned int vao_;
  unsigned int vbo_;
  unsigned int ebo_;

  glm::vec3 position_;
};
}

#endif //GLENGINE_SRC_ENGINE_PRIMITIVE_H_
