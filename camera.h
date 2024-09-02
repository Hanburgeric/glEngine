#ifndef GRAPICAR__CAMERA_H_
#define GRAPICAR__CAMERA_H_

#include <glm/gtc/matrix_transform.hpp>

#include "InputManager.h"

class InputManager;

class Camera
{
 public:
  Camera(const glm::vec3& position, const glm::vec3& world_up, const float& yaw, const float& pitch, const float& fov, const float& near, const float& far)
      : position_(position),
        front_(),
        up_(),
        right_(),
        world_up_(world_up),
        yaw_(yaw),
        pitch_(pitch),
        fov_(fov),
        near_(near),
        far_(far) {
    Update();
  }

  void HandleInput(const InputManager& inputManager) {
    if (inputManager.isMouseHeld(GLFW_MOUSE_BUTTON_RIGHT))
    {
      if (inputManager.isKeyHeld(GLFW_KEY_LEFT_ALT))
      {
        yaw_ = glm::mod(yaw_ + 0.15F * static_cast<float>(inputManager.getCursorX().m_deltaPos), 360.0F);
        pitch_ = glm::mod(pitch_ - 0.15F * static_cast<float>(inputManager.getCursorY().m_deltaPos), 360.0F);
      }

      else
      {
        position_ -= 0.05F * static_cast<float>(inputManager.getCursorX().m_deltaPos) * right_;
        position_ += 0.05F * static_cast<float>(inputManager.getCursorY().m_deltaPos) * up_;
      }
    }

    position_ += 2.5F * static_cast<float>(inputManager.getScrollOffsetY()) * front_;
  }

  void Update() {
    float sinYaw = glm::sin(glm::radians(yaw_));
    float cosYaw = glm::cos(glm::radians(yaw_));
    float sinPitch = glm::sin(glm::radians(pitch_));
    float cosPitch = glm::cos(glm::radians(pitch_));

    front_ = glm::normalize(glm::vec3(cosYaw * cosPitch, sinPitch, sinYaw * cosPitch));
    right_ = glm::normalize(glm::cross(front_, world_up_));
    up_ = glm::normalize(glm::cross(right_, front_));
  }

  glm::mat4 GetProjectionMatrix(const float& aspectRatio) const {
    return glm::perspective(glm::radians(fov_), aspectRatio, near_, far_);
  }

  glm::mat4 GetViewMatrix() const {
    return glm::lookAt(position_, position_ + front_, up_);
  }

  glm::vec3 position_;
  glm::vec3 front_;
  glm::vec3 up_;
  glm::vec3 right_;
  glm::vec3 world_up_;

  float yaw_;
  float pitch_;

  float fov_;
  float near_;
  float far_;
};

#endif
