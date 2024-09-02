#ifndef GLENGINE_SRC_GLTF_NODE_H_
#define GLENGINE_SRC_GLTF_NODE_H_

// System headers
#include <optional>
#include <string>

namespace glEngine::gltf {
struct Node {
  // camera
  // children
  // skin
  // matrix
  std::optional<int> mesh_;
  // rotation
  // scale
  // translation
  // weights
  std::string name_;
  // extensions
  // extras
};
}

#endif //GLENGINE_SRC_GLTF_NODE_H_
