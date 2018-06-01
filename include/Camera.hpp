#pragma once

#include "SceneObject.hpp"
#include <vector>

namespace alien_prober {

class Camera : public SceneObject {
  public:
  Camera();
  ~Camera();

  void moveRight();
  void moveLeft();
  void moveUp();
  void moveDown();
  void moveBackward();
  void moveForward();

  protected:
  void initSelf();
  void renderSelf();
  void updateSelf();

  private:
};

} // namespace alien_prober
