#pragma once

#include "SceneObject.hpp"
#include "Shader.hpp"
#include <math.h>
#include <random>

namespace alien_prober {

class GameManager;

enum class MovementPattern {
  straight,
  sinus
};

class Enemy : public SceneObject {
  public:
  Enemy(MovementPattern);
  ~Enemy();

  glm::vec4 getPosition() const;
  float getSize();
  MovementPattern _pattern;

  protected:
  void initSelf();
  void renderSelf();
  void updateSelf();

  private:
  std::vector<glm::vec2> _texture_array;
  std::vector<glm::vec3> _normal_array;
  std::vector<glm::vec3> _vertex_array;
  std::vector<glm::uint> _index_array;

  double _move_counter;
  float _size;

  Shader _shader;

  std::random_device _dev;
  std::mt19937_64 _gen;
  std::uniform_int_distribution<> _dist;
};
} // namespace alien_prober
