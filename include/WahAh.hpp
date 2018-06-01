#pragma once

#include "SceneObject.hpp"
#include "Shader.hpp"

namespace alien_prober {

class WahAh : public SceneObject {

  public:
  WahAh(int);
  ~WahAh();

  protected:
  void initSelf();
  void renderSelf();
  void updateSelf();

  private:
  void initTexture();
  void initArrays();

  std::vector<glm::vec3> _vertex_array;
  std::vector<glm::uint> _index_array;

  int _size;

  float _time = 1.0f;

  GLuint _colour_map, _time_id;

  Shader _shader;
};

} // namespace alien_prober
