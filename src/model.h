#ifndef GLENGINE_SRC_MODEL_H_
#define GLENGINE_SRC_MODEL_H_

// System headers
#include <string>

// Vendor headers
#include "nlohmann/json.hpp"

// User headers
#include "gltf/gltf.h"

namespace glEngine {
class Model {
 public:
  explicit Model(const std::string& file_path);

  void ImportGltf(const std::string& file_path);

  [[nodiscard]] gltf::Gltf GetGltf() const;

 private:
  void Clear();

  void ImportAccessors();
  void ImportBuffers(const std::string& file_path);
  void ImportBufferViews();
  void ImportMeshes();
  void ImportNodes();
  void ImportScenes();

  void Initialize();

  std::string path_;
  nlohmann::json json_;
  gltf::Gltf gltf_;
};
}

#endif //GLENGINE_SRC_MODEL_H_
