#ifndef GLENGINE_SRC_ENGINE_TEXTURE_H_
#define GLENGINE_SRC_ENGINE_TEXTURE_H_

// System headers
#include <string>

namespace glEngine {
class Texture {
 public:
  Texture();
  ~Texture();

  void LoadImage(const std::string& file_name) const;

  [[nodiscard]] unsigned int GetId() const;

 private:
  unsigned int id_;
};
}

#endif //GLENGINE_SRC_ENGINE_TEXTURE_H_
