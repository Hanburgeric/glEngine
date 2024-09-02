#ifndef GRAPICAR__INPUTMANAGER_H_
#define GRAPICAR__INPUTMANAGER_H_

#include <GLFW/glfw3.h>
#include <unordered_map>

struct CursorPos
{
  double m_prevPos;
  double m_currPos;
  double m_deltaPos;
};

class InputManager
{
 public:
  InputManager()
      : m_cursorX({ 0.0, 0.0, 0.0 }),
        m_cursorY({ 0.0, 0.0, 0.0 }),
        m_wasKeyPressed(),
        m_isKeyHeld(),
        m_wasKeyReleased(),
        m_wasMousePressed(),
        m_isMouseHeld(),
        m_wasMouseReleased(),
        m_scrollOffsetX(0.0),
        m_scrollOffsetY(0.0) {}

  void update() {
    m_cursorX.m_prevPos = m_cursorX.m_currPos;
    m_cursorX.m_deltaPos = 0.0;
    m_cursorY.m_prevPos = m_cursorY.m_currPos;
    m_cursorY.m_deltaPos = 0.0;

    m_wasKeyPressed.clear();
    m_wasKeyReleased.clear();

    m_wasMousePressed.clear();
    m_wasMouseReleased.clear();

    m_scrollOffsetX = 0.0;
    m_scrollOffsetY = 0.0;
  }

  void cursorPosEvent(const double& xpos, const double& ypos) {
    m_cursorX.m_prevPos += m_cursorX.m_deltaPos;
    m_cursorY.m_prevPos += m_cursorY.m_deltaPos;

    m_cursorX.m_currPos = xpos;
    m_cursorY.m_currPos = ypos;

    m_cursorX.m_deltaPos = m_cursorX.m_currPos - m_cursorX.m_prevPos;
    m_cursorY.m_deltaPos = m_cursorY.m_currPos - m_cursorY.m_prevPos;
  }

  void keyEvent(const int& key, const int& action) {
    if (action == GLFW_PRESS)
    {
      m_wasKeyPressed[key] = true;
      m_isKeyHeld[key] = true;
    } else if (action == GLFW_RELEASE)
    {
      m_isKeyHeld[key] = false;
      m_wasKeyReleased[key] = true;
    } else {} // GLFW_REPEAT
  }

  void mouseButtonEvent(const int& button, const int& action) {
    if (action == GLFW_PRESS)
    {
      m_wasMousePressed[button] = true;
      m_isMouseHeld[button] = true;
    } else if (action == GLFW_RELEASE)
    {
      m_isMouseHeld[button] = false;
      m_wasMouseReleased[button] = true;
    } else {} // GLFW_REPEAT
  }

  void scrollEvent(const double& xoffset, const double& yoffset) {
    m_scrollOffsetX = xoffset;
    m_scrollOffsetY = yoffset;
  }

  CursorPos getCursorX() const {
    return m_cursorX;
  }

  CursorPos getCursorY() const {
    return m_cursorY;
  }

  bool wasKeyPressed(const int& key) const {
    bool result = false;
    auto iter = m_wasKeyPressed.find(key);
    if (iter != m_wasKeyPressed.end())
    {
      result = iter->second;
    }
    return result;
  }

  bool isKeyHeld(const int& key) const {
    bool result = false;
    auto iter = m_isKeyHeld.find(key);
    if (iter != m_isKeyHeld.end())
    {
      result = iter->second;
    }
    return result;
  }

  bool wasKeyReleased(const int& key) const {
    bool result = false;
    auto iter = m_wasKeyReleased.find(key);
    if (iter != m_wasKeyReleased.end())
    {
      result = iter->second;
    }
    return result;
  }

  bool wasMousePressed(const int& button) const {
    bool result = false;
    auto iter = m_wasMousePressed.find(button);
    if (iter != m_wasMousePressed.end())
    {
      result = iter->second;
    }
    return result;
  }

  bool isMouseHeld(const int& button) const {
    bool result = false;
    auto iter = m_isMouseHeld.find(button);
    if (iter != m_isMouseHeld.end())
    {
      result = iter->second;
    }
    return result;
  }

  bool wasMouseReleased(const int& button) const {
    bool result = false;
    auto iter = m_wasMouseReleased.find(button);
    if (iter != m_wasMouseReleased.end())
    {
      result = iter->second;
    }
    return result;
  }

  double getScrollOffsetX() const {
    return m_scrollOffsetX;
  }

  double getScrollOffsetY() const {
    return m_scrollOffsetY;
  }

 private:
  CursorPos m_cursorX;
  CursorPos m_cursorY;

  std::unordered_map<int, bool> m_wasKeyPressed;
  std::unordered_map<int, bool> m_isKeyHeld;
  std::unordered_map<int, bool> m_wasKeyReleased;

  std::unordered_map<int, bool> m_wasMousePressed;
  std::unordered_map<int, bool> m_isMouseHeld;
  std::unordered_map<int, bool> m_wasMouseReleased;

  double m_scrollOffsetX;
  double m_scrollOffsetY;
};

#endif
