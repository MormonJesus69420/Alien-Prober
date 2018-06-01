#pragma once

#include "SOIL/SOIL.h"

#include "glm/glm.hpp"

#include "glm/gtc/matrix_transform.hpp"

#include "glm/gtc/type_ptr.hpp"

#include <GL/glew.h>

#include <GL/glu.h>

#include <GL/gl.h>

#include <GL/freeglut.h>

#include <algorithm>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

// The SceneObject class is the parent of all objects in the scene graph.
// To make an object to use in the scene graph, inherit this class and
// override the methods initSelf, updateSelf and renderSelf.
//
// The rest of the magic creating the scene graph is implemented in the
// methods init, update and render. Do NOT override those methods.
//
// The application is to create a "root" instance of SceneObject (or another
// class inheriting SceneObject). Then:
//  Call the root.init after OpenGL is initialized,
//  call root.update in the render-function, and
//  call root.render after update has been called.
//
// initSelf: Here all the initializer-code is put, this method is called
//      after OpenGL has been initialized.
// updateSelf: This method is called prior to any rendering, animation-
//      code is to be implemented in here (motion, collision-detection). When
//      this method is called, the member sslf_ has been set, so time-dependent
//      animation can use this value.
// renderSelf: This is where the rendering-code is implemented. Here you
//      do all the actual drawing.
//
// _matrix: This is the transformation matrix of the scene-object. This
//      transformation is relative to the object's parent. The transformation
//      is performed as part of the scene graph-magic.
//
// The storage of the children is handled by smart pointers, this is because

namespace alien_prober {

class SceneObject {
  public:
  SceneObject();
  virtual ~SceneObject();

  // This method causes all children to be rendered, don't override this one!
  void render();
  // This method causes all children to be updated, don't override this one!
  void update(float fps);
  // This method causes all children to be initialized, don't override this one!
  void init();

  void addSubObject(std::shared_ptr<SceneObject> new_child);
  void removeSubObject(const std::shared_ptr<SceneObject> child);

  // Dangerous to enable, and use SharedPtr if this is to be used!
  //  std::vector<ScopedPtr<SceneObject> >& getSubObjects();

  void setMatrix(const glm::mat4& m) { _matrix = m; }
  glm::mat4& getMatrix() { return _matrix; }

  protected:
  // Override this method with your own render-implementation.
  virtual void renderSelf() {}
  // Override this method with your own update-implementation.
  virtual void updateSelf() {}
  // Override this method with your own init-implementation.
  virtual void initSelf() {}

  // This member contains the time since last frame. It is set
  // before privateUpdate is called.
  float _fps;

  // This is the transformation-matrix of the scene object.
  // Relative to the object's parent. Defaults to the identity matrix.
  glm::mat4 _matrix;

  private:
  // List of all SceneObjects that belong to the current object.
  std::vector<std::shared_ptr<SceneObject>> _children;
};

} // namespace alien_prober
