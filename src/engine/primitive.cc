#include "primitive.h"

// System headers
#include <array>
#include <vector>

// Vendor headers
#include "glad/gl.h"
#include "glm/geometric.hpp"
#include "glm/vec2.hpp"
#include "glm/vec3.hpp"
#include "glm/vec4.hpp"

namespace glEngine {
Primitive::Primitive() {
  glGenVertexArrays(1, &vao_);
  glGenBuffers(1, &vbo_);
  glGenBuffers(1, &ebo_);
}

Primitive::~Primitive() {
  glDeleteBuffers(1, &ebo_);
  glDeleteBuffers(1, &vbo_);
  glDeleteVertexArrays(1, &vao_);
}

void Primitive::Setup() const {
  // Calculate VBO size
  std::size_t vbo_offset = 0U;
  std::size_t vbo_stride = (3U + 3U + 4U + (2U * 2U) + (1U * 4U) + (1U * 4U) + (1U * 4U)) * sizeof(float);
  std::size_t vbo_size = vertices_.size() * vbo_stride;

  // Calculate EBO size
  std::size_t ebo_size = indices_.size() * 3U * sizeof(unsigned int);

  // VAO setup
  glBindVertexArray(vao_);

  // VBO setup
  glBindBuffer(GL_ARRAY_BUFFER, vbo_);
  glBufferData(GL_ARRAY_BUFFER, vbo_size, &vertices_[0U], GL_STATIC_DRAW);

  unsigned int attrib_index = 0U;

  // Position
  glEnableVertexAttribArray(attrib_index);
  glVertexAttribPointer(attrib_index, 3, GL_FLOAT, GL_FALSE, vbo_stride, (void *) vbo_offset);
  ++attrib_index;
  vbo_offset += 3U * sizeof(float);

  // Normal
  glEnableVertexAttribArray(attrib_index);
  glVertexAttribPointer(attrib_index, 3, GL_FLOAT, GL_FALSE, vbo_stride, (void *) vbo_offset);
  ++attrib_index;
  vbo_offset += 3U * sizeof(float);

  // Tangent
  glEnableVertexAttribArray(attrib_index);
  glVertexAttribPointer(attrib_index, 4, GL_FLOAT, GL_FALSE, vbo_stride, (void *) vbo_offset);
  ++attrib_index;
  vbo_offset += 4U * sizeof(float);

  // Tex coords
  for (std::size_t i = 0U; i < 2U; ++i) {
    glEnableVertexAttribArray(attrib_index);
    glVertexAttribPointer(attrib_index, 2, GL_FLOAT, GL_FALSE, vbo_stride, (void *) vbo_offset);
    ++attrib_index;
    vbo_offset += 2U * sizeof(float);
  }

  // Colors
  for (std::size_t i = 0U; i < 1U; ++i) {
    glEnableVertexAttribArray(attrib_index);
    glVertexAttribPointer(attrib_index, 4, GL_FLOAT, GL_FALSE, vbo_stride, (void *) vbo_offset);
    ++attrib_index;
    vbo_offset += 4U * sizeof(float);
  }

  // Joints
  for (std::size_t i = 0U; i < 1U; ++i) {
    glEnableVertexAttribArray(attrib_index);
    glVertexAttribPointer(attrib_index, 4, GL_FLOAT, GL_FALSE, vbo_stride, (void *) vbo_offset);
    ++attrib_index;
    vbo_offset += 4U * sizeof(float);
  }

  // Weights
  for (std::size_t i = 0U; i < 1U; ++i) {
    glEnableVertexAttribArray(attrib_index);
    glVertexAttribPointer(attrib_index, 4, GL_FLOAT, GL_FALSE, vbo_stride, (void *) vbo_offset);
    ++attrib_index;
    vbo_offset += 4U * sizeof(float);
  }

  // EBO setup
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo_);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, ebo_size, &indices_[0U], GL_STATIC_DRAW);
}

void Primitive::CalcNormals() {
  for (auto& vertex : vertices_) {
    vertex.normal_ = glm::vec3();
  }

  if (!indices_.empty()) {
    for (const auto& index : indices_) {
      auto xy = vertices_[index.y].position_ - vertices_[index.x].position_;
      auto yz = vertices_[index.z].position_ - vertices_[index.y].position_;
      auto zx = vertices_[index.x].position_ - vertices_[index.z].position_;
      vertices_[index.x].normal_ += glm::cross(xy, -zx);
      vertices_[index.y].normal_ += glm::cross(yz, -xy);
      vertices_[index.z].normal_ += glm::cross(zx, -yz);
    }
  } else {
    // Do unindexed geometry
  }

  for (auto& vertex : vertices_) {
    vertex.normal_ = glm::normalize(vertex.normal_);
  }
}

void Primitive::CalcTangents() {

}

void Primitive::Render() const {
  glBindVertexArray(vao_);
  if (!indices_.empty()) {
    glDrawElements(4U, indices_.size() * 3U, GL_UNSIGNED_INT, nullptr);
  } else {
    glDrawArrays(4U, 0, vertices_.size());
  }
}
}
