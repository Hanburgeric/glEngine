#ifndef GLENGINE_SRC_ENGINE_ENGINE_H_
#define GLENGINE_SRC_ENGINE_ENGINE_H_

// User headers
#include "camera.h"
#include "input_manager.h"

namespace glEngine {
class Engine {
 public:
  // Events
  void OnCursorPos(double xpos, double ypos);
  void OnKey(int key, int action);
  void OnMouseButton(int button, int action);
  void OnScroll(double xoffset, double yoffset);

  // Update
  void Update();

  // Render
  void Render();

  // Camera
  const Camera& GetCamera() const;

 private:
  Camera camera_;
  float camera_rotate_speed_ = 0.08F;
  float camera_move_speed_ = 0.01F;
  float camera_zoom_speed_ = 0.64F;

  InputManager input_manager_;
};
}

#endif //GLENGINE_SRC_ENGINE_ENGINE_H_
