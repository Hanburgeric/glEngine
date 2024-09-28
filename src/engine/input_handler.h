#ifndef GLENGINE_SRC_ENGINE_INPUT_HANDLER_H_
#define GLENGINE_SRC_ENGINE_INPUT_HANDLER_H_

// System headers
#include <unordered_map>

namespace glEngine {
// Cursor pos
struct CursorPos {
  double current_;
  double previous_;
  double delta_;
};

class InputHandler {
 public:
  // Update
  void Update();

  // Cursor position
  void OnCursorPos(double xpos, double ypos);

  const CursorPos& GetXPos() const;
  const CursorPos& GetYPos() const;

  // Key
  void OnKey(int key, int action);

  bool WasKeyPressed(int key) const;
  bool IsKeyHeld(int key) const;
  bool WasKeyReleased(int key) const;

  // Mouse button
  void OnMouseButton(int button, int action);

  bool WasMouseButtonPressed(int button) const;
  bool IsMouseButtonHeld(int button) const;
  bool WasMouseButtonReleased(int button) const;

  // Scroll
  void OnScroll(double xoffset, double yoffset);

  double GetXOffset() const;
  double GetYOffset() const;

 private:
  // Cursor pos
  CursorPos xpos_;
  CursorPos ypos_;

  // Key
  std::unordered_map<int, bool> pressed_keys_;
  std::unordered_map<int, bool> held_keys_;
  std::unordered_map<int, bool> released_keys_;

  // Mouse button
  std::unordered_map<int, bool> pressed_mouse_buttons_;
  std::unordered_map<int, bool> held_mouse_buttons_;
  std::unordered_map<int, bool> released_mouse_buttons_;

  // Scroll
  double xoffset_;
  double yoffset_;
};
}

#endif //GLENGINE_SRC_ENGINE_INPUT_HANDLER_H_
