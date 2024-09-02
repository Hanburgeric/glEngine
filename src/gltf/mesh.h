#ifndef GLENGINE_SRC_GLTF_MESH_H_
#define GLENGINE_SRC_GLTF_MESH_H_

// System headers
#include <map>
#include <optional>
#include <string>
#include <vector>

namespace glEngine::gltf {
struct MeshPrimitive {
  std::map<std::string, int> attributes_; // REQUIRED
  std::optional<int> indices_;
  std::optional<int> material_;
  std::optional<int> mode_;               // DEFAULT : 4
  // targets

  unsigned int vao_;
  std::vector<unsigned int> vbos_;
  unsigned int ibo_;
};

struct Mesh {
  std::vector<MeshPrimitive> primitives_;
  // weights
  std::string name_;
  // extensions
  // extras
};
}

#endif //GLENGINE_SRC_GLTF_MESH_H_
