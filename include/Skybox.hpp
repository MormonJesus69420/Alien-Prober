#pragma once

#include "Camera.hpp"
#include "SceneObject.hpp"
#include "Shader.hpp"

namespace alien_prober {

class Skybox : public SceneObject {
  public:
  Skybox(std::shared_ptr<Camera> camera);
  ~Skybox();

  GLuint getSkybox();

  protected:
  void initSelf();
  void renderSelf();
  void updateSelf();

  private:
  std::shared_ptr<Camera> _camera;

  std::vector<float> _vertex_array;
  std::vector<glm::uint> _index_array;

  GLuint _skybox_id;

  Shader _shader;
};

} // namespace alien_prober
