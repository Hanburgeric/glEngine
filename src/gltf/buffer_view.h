#ifndef GLENGINE_SRC_GLTF_BUFFER_VIEW_H_
#define GLENGINE_SRC_GLTF_BUFFER_VIEW_H_

// System headers
#include <optional>
#include <string>

namespace glEngine::gltf {
struct BufferView {
  int buffer_;                      // REQUIRED
  std::optional<int> byte_offset_;  // DEFAULT : 0
  int byte_length_;                 // REQUIRED
  std::optional<int> byte_stride_;
  std::optional<int> target_;
  std::string name_;
  // extensions
  // extras
};
}

#endif //GLENGINE_SRC_GLTF_BUFFER_VIEW_H_
