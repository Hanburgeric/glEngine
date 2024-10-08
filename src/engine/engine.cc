#include "engine.h"

// Vendor headers
#include "GLFW/glfw3.h"
#include "glm/common.hpp"

// User headers
#include "camera.h"
#include "input_manager.h"

namespace glEngine {
void Engine::OnCursorPos(double xpos, double ypos) {
  input_manager_.OnCursorPos(xpos, ypos);
}

void Engine::OnKey(int key, int action) {
  input_manager_.OnKey(key, action);
}

void Engine::OnMouseButton(int button, int action) {
  input_manager_.OnMouseButton(button, action);
}

void Engine::OnScroll(double xoffset, double yoffset) {
  input_manager_.OnScroll(xoffset, yoffset);
}

void Engine::Update() {
  // Camera
  if (input_manager_.IsMouseButtonHeld(GLFW_MOUSE_BUTTON_RIGHT)) {
    auto delta_x = static_cast<float>(input_manager_.GetCursorX().delta_pos_);
    auto delta_y = static_cast<float>(input_manager_.GetCursorY().delta_pos_);
    if (input_manager_.IsKeyHeld(GLFW_KEY_LEFT_ALT)) {
      camera_.SetYaw() = glm::mod(camera_.GetYaw() + camera_rotate_speed_ * delta_x, 360.0F);
      camera_.SetPitch() = glm::mod(camera_.GetPitch() - camera_rotate_speed_ * delta_y, 360.0F);
    } else {
      camera_.SetPosition() -= camera_move_speed_ * delta_x * camera_.GetRight();
      camera_.SetPosition() += camera_move_speed_ * delta_y * camera_.GetUp();
    }
  }
  camera_.SetPosition() += camera_zoom_speed_ * static_cast<float>(input_manager_.GetScrollY()) * camera_.GetFront();

  camera_.Update();

  // Input Handler
  input_manager_.Update();
}

void Engine::Render() {
}

const Camera& Engine::GetCamera() const {
  return camera_;
}
}
