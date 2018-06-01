#include "include/SceneObject.hpp"

namespace alien_prober {

// using Iterator = std::vector<std::shared_ptr<SceneObject>>::iterator;

// NB! Check matrix mult and scoped_ptr

SceneObject::SceneObject()
{
  // setIdentity(_matrix);
  _matrix = glm::mat4();
}

SceneObject::~SceneObject()
{
}

void SceneObject::render()
{
  glPushMatrix();

  // this->matrix_.multMatrix();
  glMultMatrixf(glm::value_ptr(_matrix));

  this->renderSelf();

  for (auto child : _children)
    child->render();

  //  for (Iterator it = _children.begin(); it != _children.end(); it++)
  //    (*it)->render();

  glPopMatrix();
}

void SceneObject::update(float fps)
{
  this->_fps = fps;
  this->updateSelf();

  for (auto child : _children)
    child->update(fps);

  //  for (Iterator it = _children.begin(); it != _children.end(); it++)
  //    (*it)->update(fps);
}

void SceneObject::init()
{
  this->initSelf();

  for (auto child : _children)
    child->init();

  //  for (Iterator it = _children.begin(); it != _children.end(); it++)
  //    (*it)->init();
}

void SceneObject::addSubObject(std::shared_ptr<SceneObject> new_child)
{
  auto position = std::find(_children.begin(), _children.end(), new_child);

  if (position == _children.end())
    _children.push_back(new_child);

  // Old implementation, I think mine is a bit better, since I avoid duplicate objects
  //
  // _children.push_back(new_child);
}

void SceneObject::removeSubObject(const std::shared_ptr<SceneObject> child)
{
  auto position = std::find(_children.begin(), _children.end(), child);

  if (position != _children.end())
    _children.erase(position);

  // Old implementation, I think mine is a bit better, since it relies on stl, not my own code.
  //
  //  for (Iterator it = _children.begin(); it != _children.end(); it++) {
  //    if (*it == child) {
  //      _children.erase(it);
  //      break;
  //    }
  //  }
}

} // namespace alien_prober
