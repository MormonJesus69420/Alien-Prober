#include "include/Spaceship.hpp"
#include "include/OBJLoader.hpp"

namespace alien_prober {

Spaceship::Spaceship()
{
  _size = 25.0f;
  _speed = 1.0f;
  _armor = 0.0f;
  _life = 100.0f;
  _lifes = 3;
  _dead = false;
  _game_over = false;
}

Spaceship::~Spaceship()
{
}

void Spaceship::initSelf()
{
  _shader.loadShaders("shaders/object.vert", "shaders/object.frag");

  _texture = SOIL_load_OGL_texture("textures/trident.tga", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);

  objl::Loader loader;
  auto is_loaded = loader.LoadFile("textures/trident.obj");

  auto scale = 30.0f;

  if (is_loaded) {
    for (ulong i = 0; i < loader.LoadedMeshes.size(); ++i) {
      objl::Mesh curMesh = loader.LoadedMeshes[i];
      for (ulong j = 0; j < curMesh.Vertices.size(); ++j) {
        _vertex_array.push_back(glm::vec3(curMesh.Vertices[j].Position.X * scale, curMesh.Vertices[j].Position.Y * scale, curMesh.Vertices[j].Position.Z * scale));
        _normal_array.push_back(glm::vec3(curMesh.Vertices[j].Normal.X * scale, curMesh.Vertices[j].Normal.Y * scale, curMesh.Vertices[j].Normal.Z * scale));
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
    printf("FAILED LOADING PLAYER OBJECT\n");
  }
}

void Spaceship::renderSelf()
{
  _shader.enableProgram();

  glDisable(GL_COLOR_MATERIAL);

  glClearColor(0.0, 0.0, 0.0, 0.0);

  glActiveTexture(GL_TEXTURE0);
  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, _texture);

  glEnableClientState(GL_TEXTURE_COORD_ARRAY);
  glEnableClientState(GL_VERTEX_ARRAY);

  glEnable(GL_PRIMITIVE_RESTART);

  glTexCoordPointer(2, GL_FLOAT, 0, &_texture_array[0]);
  glVertexPointer(3, GL_FLOAT, 0, &_vertex_array[0]);

  glDrawElements(GL_TRIANGLES, static_cast<int>(_index_array.size()), GL_UNSIGNED_INT, &_index_array[0]);

  glDisable(GL_PRIMITIVE_RESTART);

  glDisableClientState(GL_VERTEX_ARRAY);
  glDisableClientState(GL_TEXTURE_COORD_ARRAY);

  glActiveTexture(GL_TEXTURE0);
  glDisable(GL_TEXTURE_2D);

  _shader.disableProgram();
}

void Spaceship::updateSelf()
{
  if (_dead) {
    _matrix = glm::translate(_matrix, glm::vec3(0.0f, 0.0f, 0.5f));

    if (_matrix[3][2] >= 10) {
      _dead = false;
    }
  }
}

void Spaceship::hit(int damage)
{
  float temp = damage * _armor;
  _armor += damage / 5.0f;
  _life -= temp;

  if (_life < 0) {
    if (--_lifes <= 0) {
      _game_over = true;
    }
    _dead = true;
    _life = 100.0f;
    _armor = 0.0f;

    _matrix = glm::translate(glm::mat4(), glm::vec3(0.0f, 0.0f, -50.0f));
  }
}

bool Spaceship::pepsi()
{
  return _dead;
}

bool Spaceship::gaymOver()
{
  return _game_over;
}

float Spaceship::getSize()
{
  return _size;
}

void Spaceship::moveRight()
{
  if (_matrix[3].x <= 125 && !_dead)
    _matrix = glm::translate(_matrix, glm::vec3(_speed, 0.0f, 0.0f));
}

void Spaceship::moveLeft()
{
  if (_matrix[3].x >= -125 && !_dead)
    _matrix = glm::translate(_matrix, glm::vec3(-_speed, 0.0f, 0.0f));
}

void Spaceship::moveForward()
{
  if (_matrix[3].z >= -50 && !_dead)
    _matrix = glm::translate(_matrix, glm::vec3(0.0f, 0.0f, -_speed));
}
void Spaceship::moveBackward()
{
  if (_matrix[3].z <= 50 && !_dead)
    _matrix = glm::translate(_matrix, glm::vec3(0.0f, 0.0f, _speed));
}

glm::vec4 Spaceship::getPosition() const
{
  return glm::vec4{ _matrix[3][0], _matrix[3][1], _matrix[3][2], _matrix[3][3] };
}

} // namespace alien_prober
