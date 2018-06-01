#pragma once

#include "SceneObject.hpp"
#include "Shader.hpp"
namespace alien_prober {

class Battlefield : public SceneObject {
  public:
  Battlefield(int);
  ~Battlefield();
  glm::vec4 getPosition() const;

  protected:
  virtual void initSelf();
  virtual void renderSelf();
  virtual void updateSelf();

  private:
  std::vector<glm::vec2> _texture_array;
  std::vector<glm::vec3> _vertex_array;
  std::vector<glm::uint> _index_array;

  GLuint _height_map, _normal_map, _colour_map;
  GLuint _shader_height_map, _shader_normal_map, _shader_colour_map;
  Shader _shader;
};

} // namespace alien_prober
