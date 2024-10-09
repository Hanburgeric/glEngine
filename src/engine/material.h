#ifndef GLENGINE_SRC_ENGINE_MATERIAL_H_
#define GLENGINE_SRC_ENGINE_MATERIAL_H_

// Vendor headers
#include "glm/vec4.hpp"

// User headers
#include "texture.h"

namespace glEngine {
class Material {
 public:

 private:
  // Base color
  glm::vec4 base_color_factor_;
  Texture base_color_texture_;
  unsigned int base_color_tex_coord_;

  // Metallic roughness
  float metallic_factor_;
  float roughness_factor_;
  Texture metallic_roughness_texture_;
  unsigned int metallic_roughness_tex_coord_;

  // Normal
  float normal_scale_;
  Texture normal_texture_;
  unsigned int normal_texture_tex_coord_;

  // Occlusion
  float occlusion_strength_;
  Texture occlusion_texture_;
  unsigned int occlusion_tex_coord_;

  // Emissive
  Texture emissive_texture_;
  unsigned int emissive_tex_coord_;
};
}

#endif //GLENGINE_SRC_ENGINE_MATERIAL_H_
