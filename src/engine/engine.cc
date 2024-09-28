#include "engine.h"

// Vendor headers
#include "GLFW/glfw3.h"
#include "glm/common.hpp"

// User headers
#include "camera.h"
#include "input_handler.h"

namespace glEngine {
void Engine::OnCursorPos(double xpos, double ypos) {
  input_handler_.OnCursorPos(xpos, ypos);
}

void Engine::OnKey(int key, int action) {
  input_handler_.OnKey(key, action);
}

void Engine::OnMouseButton(int button, int action) {
  input_handler_.OnMouseButton(button, action);
}

void Engine::OnScroll(double xoffset, double yoffset) {
  input_handler_.OnScroll(xoffset, yoffset);
}

void Engine::Update() {
  // Camera
  if (input_handler_.IsMouseButtonHeld(GLFW_MOUSE_BUTTON_RIGHT)) {
    if (input_handler_.IsKeyHeld(GLFW_KEY_LEFT_ALT)) {
      camera_.SetYaw() = glm::mod(camera_.GetYaw() + 0.15F * static_cast<float>(input_handler_.GetXPos().delta_), 360.0F);
      camera_.SetPitch() = glm::mod(camera_.GetPitch() - 0.15F * static_cast<float>(input_handler_.GetYPos().delta_), 360.0F);
    } else {
      camera_.SetPosition() -= 0.05F * static_cast<float>(input_handler_.GetXPos().delta_) * camera_.GetRight();
      camera_.SetPosition() += 0.05F * static_cast<float>(input_handler_.GetYPos().delta_) * camera_.GetUp();
    }
  }
  camera_.SetPosition() += 2.5F * static_cast<float>(input_handler_.GetYOffset()) * camera_.GetFront();

  camera_.Update();

  // Input Handler
  input_handler_.Update();

  // ???
}

void Engine::Render() {
  // ???
}

const Camera& Engine::GetCamera() const {
  return camera_;
}
}
