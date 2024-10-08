#ifndef GLENGINE_SRC_GLTF_MATERIAL_H_
#define GLENGINE_SRC_GLTF_MATERIAL_H_

// System headers
#include <array>
#include <optional>
#include <string>

namespace glEngine::glTF {
struct PbrMetallicRoughness {
  std::optional<std::array<float, 4U>> base_color_factor_;

};

struct Material {
  std::string name_;
  // extensions
  // extras
  PbrMetallicRoughness pbr_metallic_roughness_;
  // normal_texture_;
  // occlusion_texture_;
  // emissive_texture_;
  std::string alpha_mode_;
  std::optional<float> alpha_cutoff_;
  std::optional<bool> double_sided_;
};
}

#endif //GLENGINE_SRC_GLTF_MATERIAL_H_
