#ifndef GLENGINE_SRC_ENGINE_CAMERA_H_
#define GLENGINE_SRC_ENGINE_CAMERA_H_

// Vendor headers
#include "glm/mat4x4.hpp"
#include "glm/vec3.hpp"

namespace glEngine {
class Camera {
 public:
  // Constructor
  Camera();

  // Update
  void Update();

  // Accessors & Mutators
  [[nodiscard]] const glm::vec3& GetPosition() const;
  glm::vec3& SetPosition();

  [[nodiscard]] float GetPitch() const;
  float& SetPitch();

  [[nodiscard]] float GetYaw() const;
  float& SetYaw();

  [[nodiscard]] float GetRoll() const;
  float& SetRoll();

  [[nodiscard]] const glm::vec3& GetFront() const;

  [[nodiscard]] const glm::vec3& GetRight() const;

  [[nodiscard]] const glm::vec3& GetUp() const;

  // View Matrix
  [[nodiscard]] glm::mat4 CalcViewMatrix() const;

 private:
  glm::vec3 position_;

  float pitch_;
  float yaw_;
  float roll_;

  glm::vec3 front_;
  glm::vec3 right_;
  glm::vec3 up_;
};
}

#endif //GLENGINE_SRC_ENGINE_CAMERA_H_
