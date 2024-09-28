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

  void ImportModelFromFile(const std::string& file_path);

  [[nodiscard]] const gltf::Gltf& GetGltf() const;

 private:
  void Initialize();

  void Clear();

  std::string file_path_;
  nlohmann::json json_;
  gltf::Gltf gltf_;
};
}

#endif //GLENGINE_SRC_MODEL_H_
