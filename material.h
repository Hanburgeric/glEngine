#ifndef GRAPICAR__MATERIAL_H_
#define GRAPICAR__MATERIAL_H_

#include <array>
#include <cstdint>
#include <string>

struct TextureInfo {
  std::int32_t index_;
  std::int32_t tex_coord_;
};

struct MaterialOcclusionTextureInfo {
  std::int32_t index_;
  std::int32_t tex_coord_;
  float strength_;
};

struct MaterialNormalTextureInfo {
  std::int32_t index_;
  std::int32_t tex_coord_;
  float scale_;
};

struct MaterialPBRMetallicRoughness {
  std::array<float, 4U> base_color_factor_; //Number assumed to be a float
  TextureInfo base_color_texture_;
  float metallic_factor_; //Number assumed to be a float
  float roughness_factor_; //Number assumed to be a float
  TextureInfo metallic_roughness_texture_;
};

struct Material {
  std::string name_;
  MaterialPBRMetallicRoughness pbr_metallic_roughness_;
  MaterialNormalTextureInfo normal_texture_;
  MaterialOcclusionTextureInfo occlusion_texture_;
  TextureInfo emissive_texture_;
  std::array<float, 3U> emissive_factor_; //Number assumed to be a float
  std::string alpha_mode_;
  float alpha_cutoff_; //Number assumed to be a float
  bool double_sided_;
};

#endif //GRAPICAR__MATERIAL_H_
