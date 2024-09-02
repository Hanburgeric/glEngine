#ifndef GLENGINE_SRC_GLTF_SCENE_H_
#define GLENGINE_SRC_GLTF_SCENE_H_

// System headers
#include <string>
#include <vector>

namespace glEngine::gltf {
struct Scene {
  std::vector<int> nodes_;
  std::string name_;
  // extensions
  // extras
};
}

#endif //GLENGINE_SRC_GLTF_SCENE_H_
