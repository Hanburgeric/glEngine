#ifndef GLENGINE_SRC_ENGINE_INPUT_MANAGER_H_
#define GLENGINE_SRC_ENGINE_INPUT_MANAGER_H_

// System headers
#include <unordered_map>

namespace glEngine {
// Cursor pos
struct CursorPos {
  double curr_pos_;
  double prev_pos_;
  double delta_pos_;
};

class InputManager {
 public:
  // Update
  void Update();

  // Cursor position
  void OnCursorPos(double xpos, double ypos);

  [[nodiscard]] const CursorPos& GetCursorX() const;
  [[nodiscard]] const CursorPos& GetCursorY() const;

  // Keys
  void OnKey(int key, int action);

  [[nodiscard]] bool WasKeyPressed(int key) const;
  [[nodiscard]] bool IsKeyHeld(int key) const;
  [[nodiscard]] bool WasKeyReleased(int key) const;

  // Mouse buttons
  void OnMouseButton(int button, int action);

  [[nodiscard]] bool WasMouseButtonPressed(int button) const;
  [[nodiscard]] bool IsMouseButtonHeld(int button) const;
  [[nodiscard]] bool WasMouseButtonReleased(int button) const;

  // Scroll
  void OnScroll(double xoffset, double yoffset);

  [[nodiscard]] double GetScrollX() const;
  [[nodiscard]] double GetScrollY() const;

 private:
  // Cursor pos
  CursorPos cursor_x_;
  CursorPos cursor_y_;

  // Key
  std::unordered_map<int, bool> pressed_keys_;
  std::unordered_map<int, bool> held_keys_;
  std::unordered_map<int, bool> released_keys_;

  // Mouse button
  std::unordered_map<int, bool> pressed_mouse_buttons_;
  std::unordered_map<int, bool> held_mouse_buttons_;
  std::unordered_map<int, bool> released_mouse_buttons_;

  // Scroll
  double scroll_x_;
  double scroll_y_;
};
}

#endif //GLENGINE_SRC_ENGINE_INPUT_MANAGER_H_
