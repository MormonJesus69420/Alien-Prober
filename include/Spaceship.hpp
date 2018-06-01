#pragma once

#include "SceneObject.hpp"
#include "Shader.hpp"

namespace alien_prober {

class Spaceship : public SceneObject {
  public:
  Spaceship();
  ~Spaceship();

  void hit(int);
  bool pepsi();
  bool gaymOver();
  float getSize();
  void moveRight();
  void moveLeft();
  void moveForward();
  void moveBackward();
  glm::vec4 getPosition() const;

  protected:
  void initSelf();
  void renderSelf();
  void updateSelf();

  private:
  std::vector<glm::vec2> _texture_array;
  std::vector<glm::vec3> _normal_array;
  std::vector<glm::vec3> _vertex_array;
  std::vector<glm::uint> _index_array;

  GLuint _texture;

  float _speed, _life, _armor, _size;
  bool _dead, _game_over;
  int _lifes;

  Shader _shader;
};

} // namespace alien_prober
