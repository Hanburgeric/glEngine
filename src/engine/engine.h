#ifndef GLENGINE_SRC_ENGINE_ENGINE_H_
#define GLENGINE_SRC_ENGINE_ENGINE_H_

// User headers
#include "camera.h"
#include "input_handler.h"

namespace glEngine {
class Engine {
 public:
  // Handle events
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
  InputHandler input_handler_;

  Camera camera_;
};
}

#endif //GLENGINE_SRC_ENGINE_ENGINE_H_
