#include "cube.h"

// System headers
#include <vector>

// Vendor headers
#include "glad/gl.h"
#include "glm/vec2.hpp"
#include "glm/vec3.hpp"
#include "glm/vec4.hpp"

// User headers
#include "primitive.h"

namespace glEngine {
Cube::Cube() {
  // Indices setup
  indices_.reserve(12U);
  (void)indices_.emplace_back( 0U,  1U,  2U);
  (void)indices_.emplace_back( 3U,  2U,  1U);
  (void)indices_.emplace_back( 4U,  5U,  6U);
  (void)indices_.emplace_back( 7U,  6U,  5U);
  (void)indices_.emplace_back( 8U,  9U, 10U);
  (void)indices_.emplace_back(11U, 10U,  9U);
  (void)indices_.emplace_back(12U, 13U, 14U);
  (void)indices_.emplace_back(15U, 14U, 13U);
  (void)indices_.emplace_back(16U, 17U, 18U);
  (void)indices_.emplace_back(19U, 18U, 17U);
  (void)indices_.emplace_back(20U, 21U, 22U);
  (void)indices_.emplace_back(23U, 22U, 21U);

  // Vertices setup
  vertices_.resize(24U);

  // Positions
  vertices_[ 0U].position_ = glm::vec3(-0.5F, -0.5F,  0.5F);
  vertices_[ 1U].position_ = glm::vec3( 0.5F, -0.5F,  0.5F);
  vertices_[ 2U].position_ = glm::vec3(-0.5F,  0.5F,  0.5F);
  vertices_[ 3U].position_ = glm::vec3( 0.5F,  0.5F,  0.5F);
  vertices_[ 4U].position_ = glm::vec3( 0.5F, -0.5F,  0.5F);
  vertices_[ 5U].position_ = glm::vec3(-0.5F, -0.5F,  0.5F);
  vertices_[ 6U].position_ = glm::vec3( 0.5F, -0.5F, -0.5F);
  vertices_[ 7U].position_ = glm::vec3(-0.5F, -0.5F, -0.5F);
  vertices_[ 8U].position_ = glm::vec3( 0.5F,  0.5F,  0.5F);
  vertices_[ 9U].position_ = glm::vec3( 0.5F, -0.5F,  0.5F);
  vertices_[10U].position_ = glm::vec3( 0.5F,  0.5F, -0.5F);
  vertices_[11U].position_ = glm::vec3( 0.5F, -0.5F, -0.5F);
  vertices_[12U].position_ = glm::vec3(-0.5F,  0.5F,  0.5F);
  vertices_[13U].position_ = glm::vec3( 0.5F,  0.5F,  0.5F);
  vertices_[14U].position_ = glm::vec3(-0.5F,  0.5F, -0.5F);
  vertices_[15U].position_ = glm::vec3( 0.5F,  0.5F, -0.5F);
  vertices_[16U].position_ = glm::vec3(-0.5F, -0.5F,  0.5F);
  vertices_[17U].position_ = glm::vec3(-0.5F,  0.5F,  0.5F);
  vertices_[18U].position_ = glm::vec3(-0.5F, -0.5F, -0.5F);
  vertices_[19U].position_ = glm::vec3(-0.5F,  0.5F, -0.5F);
  vertices_[20U].position_ = glm::vec3(-0.5F, -0.5F, -0.5F);
  vertices_[21U].position_ = glm::vec3(-0.5F,  0.5F, -0.5F);
  vertices_[22U].position_ = glm::vec3( 0.5F, -0.5F, -0.5F);
  vertices_[23U].position_ = glm::vec3( 0.5F,  0.5F, -0.5F);

  // Normals
  CalcNormals();

  // Tangents
  CalcTangents();

  // Tex coords
  vertices_[ 0U].tex_coords_[0U] = glm::vec2(6.0F, 0.0F);
  vertices_[ 1U].tex_coords_[0U] = glm::vec2(5.0F, 0.0F);
  vertices_[ 2U].tex_coords_[0U] = glm::vec2(6.0F, 1.0F);
  vertices_[ 3U].tex_coords_[0U] = glm::vec2(5.0F, 1.0F);
  vertices_[ 4U].tex_coords_[0U] = glm::vec2(4.0F, 0.0F);
  vertices_[ 5U].tex_coords_[0U] = glm::vec2(5.0F, 0.0F);
  vertices_[ 6U].tex_coords_[0U] = glm::vec2(4.0F, 1.0F);
  vertices_[ 7U].tex_coords_[0U] = glm::vec2(5.0F, 1.0F);
  vertices_[ 8U].tex_coords_[0U] = glm::vec2(2.0F, 0.0F);
  vertices_[ 9U].tex_coords_[0U] = glm::vec2(1.0F, 0.0F);
  vertices_[10U].tex_coords_[0U] = glm::vec2(2.0F, 1.0F);
  vertices_[11U].tex_coords_[0U] = glm::vec2(1.0F, 1.0F);
  vertices_[12U].tex_coords_[0U] = glm::vec2(3.0F, 0.0F);
  vertices_[13U].tex_coords_[0U] = glm::vec2(4.0F, 0.0F);
  vertices_[14U].tex_coords_[0U] = glm::vec2(3.0F, 1.0F);
  vertices_[15U].tex_coords_[0U] = glm::vec2(4.0F, 1.0F);
  vertices_[16U].tex_coords_[0U] = glm::vec2(3.0F, 0.0F);
  vertices_[17U].tex_coords_[0U] = glm::vec2(2.0F, 0.0F);
  vertices_[18U].tex_coords_[0U] = glm::vec2(3.0F, 1.0F);
  vertices_[19U].tex_coords_[0U] = glm::vec2(2.0F, 1.0F);
  vertices_[20U].tex_coords_[0U] = glm::vec2(0.0F, 0.0F);
  vertices_[21U].tex_coords_[0U] = glm::vec2(0.0F, 1.0F);
  vertices_[22U].tex_coords_[0U] = glm::vec2(1.0F, 0.0F);
  vertices_[23U].tex_coords_[0U] = glm::vec2(1.0F, 1.0F);

  // Colors
  for (auto& vertex : vertices_) {
    vertex.colors_[0U] = glm::vec4(0.5F);
  }

  // Joints

  // Weights

  // Initialize geometry data
  Setup();
}
}
