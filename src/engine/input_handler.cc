#include "input_handler.h"

// System headers
#include <iostream>
#include <unordered_map>

// Vendor headers
#include "GLFW/glfw3.h"

namespace glEngine {
void InputHandler::Update() {
  // Cursor pos
  xpos_.previous_ = xpos_.current_;
  ypos_.previous_ = ypos_.current_;

  xpos_.delta_ = 0.0;
  ypos_.delta_ = 0.0;

  // Key
  pressed_keys_.clear();
  released_keys_.clear();

  // Mouse button
  pressed_mouse_buttons_.clear();
  released_mouse_buttons_.clear();

  // Scroll
  xoffset_ = 0.0;
  yoffset_ = 0.0;
}

void InputHandler::OnCursorPos(double xpos, double ypos) {
  xpos_.current_ = xpos;
  ypos_.current_ = ypos;

  xpos_.delta_ = xpos_.current_ - xpos_.previous_;
  ypos_.delta_ = ypos_.current_ - ypos_.previous_;
}

const CursorPos& InputHandler::GetXPos() const {
  return xpos_;
}

const CursorPos& InputHandler::GetYPos() const {
  return ypos_;
}

void InputHandler::OnKey(int key, int action) {
  switch (action) {
    case GLFW_RELEASE : {
      held_keys_[key] = false;
      released_keys_[key] = true;
      break;
    }
    case GLFW_PRESS : {
      pressed_keys_[key] = true;
      held_keys_[key] = true;
      break;
    }
    case GLFW_REPEAT : {
      // Do nothing
      break;
    }
    default : {
      std::cerr << "key input not recognized" << std::endl;
      break;
    }
  }
}

bool InputHandler::WasKeyPressed(int key) const {
  bool result = false;
  const auto& iter = pressed_keys_.find(key);
  if (iter != pressed_keys_.end()) {
    result = iter->second;
  }
  return result;
}

bool InputHandler::IsKeyHeld(int key) const {
  bool result = false;
  const auto& iter = held_keys_.find(key);
  if (iter != held_keys_.end()) {
    result = iter->second;
  }
  return result;
}

bool InputHandler::WasKeyReleased(int key) const {
  bool result = false;
  const auto& iter = released_keys_.find(key);
  if (iter != released_keys_.end()) {
    result = iter->second;
  }
  return result;
}

void InputHandler::OnMouseButton(int button, int action) {
  switch (action) {
    case GLFW_RELEASE : {
      held_mouse_buttons_[button] = false;
      released_mouse_buttons_[button] = true;
      break;
    }
    case GLFW_PRESS : {
      pressed_mouse_buttons_[button] = true;
      held_mouse_buttons_[button] = true;
      break;
    }
    case GLFW_REPEAT : {
      // Do nothing
      break;
    }
    default : {
      std::cerr << "mouse button input not recognized" << std::endl;
      break;
    }
  }
}

bool InputHandler::WasMouseButtonPressed(int button) const {
  bool result = false;
  const auto& iter = pressed_mouse_buttons_.find(button);
  if (iter != pressed_mouse_buttons_.end()) {
    result = iter->second;
  }
  return result;
}

bool InputHandler::IsMouseButtonHeld(int button) const {
  bool result = false;
  const auto& iter = held_mouse_buttons_.find(button);
  if (iter != held_mouse_buttons_.end()) {
    result = iter->second;
  }
  return result;
}

bool InputHandler::WasMouseButtonReleased(int button) const {
  bool result = false;
  const auto& iter = released_mouse_buttons_.find(button);
  if (iter != released_mouse_buttons_.end()) {
    result = iter->second;
  }
  return result;
}

void InputHandler::OnScroll(double xoffset, double yoffset) {
  xoffset_ = xoffset;
  yoffset_ = yoffset;
}

double InputHandler::GetXOffset() const {
  return xoffset_;
}

double InputHandler::GetYOffset() const {
  return yoffset_;
}
}
