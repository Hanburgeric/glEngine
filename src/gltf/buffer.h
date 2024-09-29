#ifndef GLENGINE_SRC_GLTF_BUFFER_H_
#define GLENGINE_SRC_GLTF_BUFFER_H_

// System headers
#include <string>
#include <vector>

namespace glEngine::gltf {
struct Buffer {
  std::string uri_;
  int byte_length_;   // REQUIRED
  std::string name_;
  // extensions
  // extras

  std::vector<unsigned char> data_;
};
}

#endif //GLENGINE_SRC_GLTF_BUFFER_H_
