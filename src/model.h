#ifndef GLENGINE_SRC_MODEL_H_
#define GLENGINE_SRC_MODEL_H_

// System headers
#include <string>

// Vendor headers
#include "glm/mat4x4.hpp"
#include "nlohmann/json.hpp"

// User headers
#include "engine/renderer/program.h"
#include "gltf/gltf.h"
#include "gltf/node.h"

namespace glEngine {
class Model {
 public:
  explicit Model(const std::string& file_path);

  void Render(renderer::Program& program) const;

  void ImportModelFromFile(const std::string& file_path);

  [[nodiscard]] const gltf::Gltf& GetGltf() const;

 private:
  void Initialize();

  void Clear();

  void RenderNode(renderer::Program& program, const gltf::Node& node, const glm::mat4& TRS) const;

  std::string file_path_;
  nlohmann::json json_;
  gltf::Gltf gltf_;
};
}

#endif //GLENGINE_SRC_MODEL_H_
