#ifndef GLENGINE_SRC_GLTF_NODE_H_
#define GLENGINE_SRC_GLTF_NODE_H_

// System headers
#include <array>
#include <optional>
#include <string>
#include <vector>

namespace glEngine::gltf {
struct Node {
  // camera
  std::vector<int> children_;
  // skin
  std::optional<std::array<float, 16U>> matrix_;      // DEFAULT : [1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1]
  std::optional<int> mesh_;
  std::optional<std::array<float, 4U>> rotation_;     // DEFAULT : [0,0,0,1]
  std::optional<std::array<float, 3U>> scale_;        // DEFAULT : [1,1,1]
  std::optional<std::array<float, 3U>> translation_;  // DEFAULT : [0,0,0]
  // weights
  std::string name_;
  // extensions
  // extras
};
}

#endif //GLENGINE_SRC_GLTF_NODE_H_
