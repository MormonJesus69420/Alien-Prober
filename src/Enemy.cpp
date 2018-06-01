#include "include/Enemy.hpp"
#include "include/GameManager.hpp"
#include "include/OBJLoader.hpp"
#include <random>

namespace alien_prober {

Enemy::Enemy(MovementPattern pattern)
{
  _pattern = pattern;
  _size = 25;
}

Enemy::~Enemy()
{
}

void Enemy::initSelf()
{
  _matrix = glm::translate(_matrix, glm::vec3(0, 0, -3000));

  _shader.loadShaders("shaders/phong.vert", "shaders/phong.frag");

  objl::Loader loader;

  auto is_loaded = loader.LoadFile("textures/pinnace.obj");
  auto scale = 10;

  if (is_loaded) {
    for (ulong i = 0; i < loader.LoadedMeshes.size(); ++i) {
      objl::Mesh curMesh = loader.LoadedMeshes[i];
      for (ulong j = 0; j < curMesh.Vertices.size(); ++j) {
        _vertex_array.push_back(glm::vec3(curMesh.Vertices[j].Position.X * scale, curMesh.Vertices[j].Position.Y * scale, curMesh.Vertices[j].Position.Z * scale));
        _normal_array.push_back(glm::vec3(curMesh.Vertices[j].Normal.X * -scale, curMesh.Vertices[j].Normal.Y * -scale, curMesh.Vertices[j].Normal.Z * -scale));
        _texture_array.push_back(glm::vec2(curMesh.Vertices[j].TextureCoordinate.X, curMesh.Vertices[j].TextureCoordinate.Y));
      }

      for (ulong j = 0; j < curMesh.Indices.size(); j += 3) {
        _index_array.push_back(curMesh.Indices[j]);
        _index_array.push_back(curMesh.Indices[j + 1]);
        _index_array.push_back(curMesh.Indices[j + 2]);
      }
    }
  }
  else {
    printf("FAILED LOADING ENEMY OBJECT\n");
  }
}

void Enemy::renderSelf()
{
  glClearColor(0.0, 0.0, 0.0, 0.0);

  if (_pattern == MovementPattern::sinus) {
    float materialDiffuse[] = { 0.0f, 0.4f, 0.6f };
    glMaterialfv(GL_FRONT, GL_DIFFUSE, materialDiffuse);
  }
  else {
    float materialDiffuse[] = { 0.9f, 0.0f, 0.6f };
    glMaterialfv(GL_FRONT, GL_DIFFUSE, materialDiffuse);
  }

  float materialSpecular[] = { 1.0f, 1.0f, 1.0f };
  glMaterialfv(GL_FRONT, GL_SPECULAR, materialSpecular);

  _shader.enableProgram();

  glDisable(GL_COLOR_MATERIAL);

  glEnableClientState(GL_VERTEX_ARRAY);
  glEnableClientState(GL_NORMAL_ARRAY);

  glEnable(GL_PRIMITIVE_RESTART);

  glVertexPointer(3, GL_FLOAT, 0, &_vertex_array[0]);
  glNormalPointer(GL_FLOAT, 0, &_normal_array[0]);

  glDrawElements(GL_TRIANGLES, static_cast<int>(_index_array.size()), GL_UNSIGNED_INT, &_index_array[0]);

  glDisable(GL_PRIMITIVE_RESTART);

  glDisableClientState(GL_NORMAL_ARRAY);
  glDisableClientState(GL_VERTEX_ARRAY);

  _shader.disableProgram();
}

void Enemy::updateSelf()
{
  auto SPEED = 420 / _fps;

  switch (_pattern) {
  case MovementPattern::straight:
    _matrix = glm::translate(_matrix, glm::vec3(0.0f, 0.0f, SPEED));
    break;
  case MovementPattern::sinus:
    _matrix = glm::translate(_matrix, glm::vec3(glm::cos(_move_counter += 0.01), 0.0f, SPEED));
    break;
  }
}

float Enemy::getSize()
{
  return _size;
}

glm::vec4 Enemy::getPosition() const
{
  return glm::vec4{ _matrix[3][0], _matrix[3][1], _matrix[3][2], _matrix[3][3] };
}
} // namespace alien_prober
