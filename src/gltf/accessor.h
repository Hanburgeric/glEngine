#ifndef GLENGINE_SRC_GLTF_ACCESSOR_H_
#define GLENGINE_SRC_GLTF_ACCESSOR_H_

// System headers
#include <optional>
#include <string>

namespace glEngine::gltf {
struct Accessor {
  std::optional<int> buffer_view_;
  std::optional<int> byte_offset_;  // DEFAULT : 0
  int component_type_;              // REQUIRED
  std::optional<bool> normalized_;  // DEFAULT : false
  int count_;                       // REQUIRED
  std::string type_;                // REQUIRED
  // max
  // min
  // sparse
  std::string name_;
  // extensions
  // extras
};
}

#endif //GLENGINE_SRC_GLTF_ACCESSOR_H_
