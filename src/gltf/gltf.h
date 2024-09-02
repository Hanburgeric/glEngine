#ifndef GLENGINE_SRC_GLTF_GLTF_H_
#define GLENGINE_SRC_GLTF_GLTF_H_

// System headers
#include <optional>
#include <vector>

// User headers
#include "accessor.h"
#include "buffer.h"
#include "buffer_view.h"
#include "mesh.h"
#include "node.h"
#include "scene.h"

namespace glEngine::gltf {
struct Gltf {
  // extensionsUsed
  // extensionsRequired
  std::vector<Accessor> accessors_;
  // animations
  // asset
  std::vector<Buffer> buffers_;
  std::vector<BufferView> buffer_views_;
  // cameras
  // images
  // materials
  std::vector<Mesh> meshes_;
  std::vector<Node> nodes_;
  // samplers
  std::optional<int> scene_;
  std::vector<Scene> scenes_;
  // scenes
  // skins
  // textures
  // extensions
  // extras
};
}

#endif //GLENGINE_SRC_GLTF_GLTF_H_
