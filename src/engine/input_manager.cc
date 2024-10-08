#include "input_manager.h"

// System headers
#include <iostream>
#include <unordered_map>

// Vendor headers
#include "GLFW/glfw3.h"

namespace glEngine {
void InputManager::Update() {
  // Cursor pos
  cursor_x_.prev_pos_ = cursor_x_.curr_pos_;
  cursor_y_.prev_pos_ = cursor_y_.curr_pos_;

  cursor_x_.delta_pos_ = 0.0;
  cursor_y_.delta_pos_ = 0.0;

  // Keys
  pressed_keys_.clear();
  released_keys_.clear();

  // Mouse buttons
  pressed_mouse_buttons_.clear();
  released_mouse_buttons_.clear();

  // Scroll
  scroll_x_ = 0.0;
  scroll_y_ = 0.0;
}

void InputManager::OnCursorPos(double xpos, double ypos) {
  cursor_x_.curr_pos_ = xpos;
  cursor_y_.curr_pos_ = ypos;

  cursor_x_.delta_pos_ += cursor_x_.curr_pos_ - cursor_x_.prev_pos_;
  cursor_y_.delta_pos_ += cursor_y_.curr_pos_ - cursor_y_.prev_pos_;
}

const CursorPos& InputManager::GetCursorX() const {
  return cursor_x_;
}

const CursorPos& InputManager::GetCursorY() const {
  return cursor_y_;
}

void InputManager::OnKey(int key, int action) {
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

bool InputManager::WasKeyPressed(int key) const {
  bool result = false;
  const auto& iter = pressed_keys_.find(key);
  if (iter != pressed_keys_.end()) {
    result = iter->second;
  }
  return result;
}

bool InputManager::IsKeyHeld(int key) const {
  bool result = false;
  const auto& iter = held_keys_.find(key);
  if (iter != held_keys_.end()) {
    result = iter->second;
  }
  return result;
}

bool InputManager::WasKeyReleased(int key) const {
  bool result = false;
  const auto& iter = released_keys_.find(key);
  if (iter != released_keys_.end()) {
    result = iter->second;
  }
  return result;
}

void InputManager::OnMouseButton(int button, int action) {
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

bool InputManager::WasMouseButtonPressed(int button) const {
  bool result = false;
  const auto& iter = pressed_mouse_buttons_.find(button);
  if (iter != pressed_mouse_buttons_.end()) {
    result = iter->second;
  }
  return result;
}

bool InputManager::IsMouseButtonHeld(int button) const {
  bool result = false;
  const auto& iter = held_mouse_buttons_.find(button);
  if (iter != held_mouse_buttons_.end()) {
    result = iter->second;
  }
  return result;
}

bool InputManager::WasMouseButtonReleased(int button) const {
  bool result = false;
  const auto& iter = released_mouse_buttons_.find(button);
  if (iter != released_mouse_buttons_.end()) {
    result = iter->second;
  }
  return result;
}

void InputManager::OnScroll(double xoffset, double yoffset) {
  scroll_x_ = xoffset;
  scroll_y_ = yoffset;
}

double InputManager::GetScrollX() const {
  return scroll_x_;
}

double InputManager::GetScrollY() const {
  return scroll_y_;
}
}
