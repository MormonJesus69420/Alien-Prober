#include "include/Camera.hpp"

//#define PIOVER180 0.0174532925199

namespace alien_prober {

Camera::Camera()
{
  _matrix = glm::translate(glm::mat4(), glm::vec3(0.0f, -75.0f, -200.0f));
}

Camera::~Camera()
{
}

void Camera::initSelf()
{
}

void Camera::renderSelf()
{
}

void Camera::updateSelf()
{
}

void Camera::moveRight()
{
  _matrix = glm::translate(_matrix, glm::vec3(-1.0f, 0.0f, 0.0f));
}
void Camera::moveLeft()
{
  _matrix = glm::translate(_matrix, glm::vec3(1.0f, 0.0f, 0.0f));
}
void Camera::moveUp()
{
  _matrix = glm::translate(_matrix, glm::vec3(0.0f, -1.0f, 0.0f));
}
void Camera::moveDown()
{
  _matrix = glm::translate(_matrix, glm::vec3(0.0f, 1.0f, 0.0f));
}
void Camera::moveForward()
{
  _matrix = glm::translate(_matrix, glm::vec3(0.0f, 0.0f, 10.0f));
}
void Camera::moveBackward()
{
  _matrix = glm::translate(_matrix, glm::vec3(0.0f, 0.0f, -20.0f));
}

} // namespace alien_prober
