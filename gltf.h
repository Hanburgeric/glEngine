#ifndef GRAPICAR__GLTF_H_
#define GRAPICAR__GLTF_H_

#include <cstdint>
#include <vector>

#include "accessor.h"
#include "animation.h"
#include "buffer.h"
#include "buffer_view.h"
//#include "camera.h"
#include "image.h"
#include "material.h"
#include "mesh.h"
#include "node.h"
#include "sampler.h"
#include "scene.h"
//#include "skin.h"
#include "texture.h"

struct GLTF {
  std::vector<Accessor> accessors_;
  std::vector<Animation> animations_;
//  Asset asset_;
  std::vector<Buffer> buffers_;
  std::vector<BufferView> buffer_views_;
//  std::vector<Camera> cameras_;
  std::vector<Image> images_;
  std::vector<Material> materials_;
  std::vector<Mesh> meshes_;
  std::vector<Node> nodes_;
  std::vector<Sampler> samplers_;
  std::int32_t scene_;
  std::vector<Scene> scenes_;
//  std::vector<Skin> skins_;
  std::vector<Texture> textures_;
};

#endif //GRAPICAR__GLTF_H_
