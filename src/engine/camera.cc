#include "camera.h"

// Vendor headers
#include "glm/geometric.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/mat4x4.hpp"
#include "glm/trigonometric.hpp"
#include "glm/vec3.hpp"

namespace glEngine {
Camera::Camera() {
  position_ = glm::vec3(0.0F, 0.0F, 5.0F);
  pitch_ = 0.0F;
  yaw_ = 270.0F;
  roll_ = 0.0F;

  Update();
}

void Camera::Update() {
  float x = glm::cos(glm::radians(yaw_)) * glm::cos(glm::radians(pitch_));
  float y = glm::sin(glm::radians(pitch_));
  float z = glm::sin(glm::radians(yaw_)) * glm::cos(glm::radians(pitch_));
  front_ = glm::normalize(glm::vec3(x, y, z));
  right_ = glm::normalize(glm::cross(front_, glm::vec3(0.0F, 1.0F, 0.0F)));
  up_ = glm::normalize(glm::cross(right_, front_));
}

const glm::vec3& Camera::GetPosition() const {
  return position_;
}

glm::vec3& Camera::SetPosition() {
  return position_;
}

float Camera::GetPitch() const {
  return pitch_;
}

float& Camera::SetPitch() {
  return pitch_;
}

float Camera::GetYaw() const {
  return yaw_;
}

float& Camera::SetYaw() {
  return yaw_;
}

float Camera::GetRoll() const {
  return roll_;
}

float& Camera::SetRoll() {
  return roll_;
}

const glm::vec3& Camera::GetFront() const {
  return front_;
}

const glm::vec3& Camera::GetRight() const {
  return right_;
}

const glm::vec3& Camera::GetUp() const {
  return up_;
}

glm::mat4 Camera::CalcViewMatrix() const {
  return glm::lookAt(position_, position_ + front_, up_);
}
}
