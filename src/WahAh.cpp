#include "include/WahAh.hpp"

namespace alien_prober {

WahAh::WahAh(int size)
{
  _size = size;
}

WahAh::~WahAh()
{
}

void WahAh::initSelf()
{
  initTexture();
  initArrays();
}

void WahAh::initTexture()
{
  _shader.loadShaders("shaders/wahah.vert", "shaders/wahah.frag");

  _colour_map = SOIL_load_OGL_cubemap(
      "textures/space_lf.tga",
      "textures/space_rt.tga",
      "textures/space_up.tga",
      "textures/space_dn.tga",
      "textures/space_ft.tga",
      "textures/space_bk.tga",
      SOIL_LOAD_RGB,
      SOIL_CREATE_NEW_ID,
      SOIL_FLAG_MIPMAPS);
  _shader.enableProgram();

  _time_id = glGetUniformLocation(_shader.getProgram(), "_time");
  glUniform1f(_time_id, _time);

  _shader.disableProgram();
}

void WahAh::initArrays()
{
  for (auto i = 0; i > -_size; --i) {
    for (auto j = -_size / 2.0; j < _size / 2.0; ++j) {
      _vertex_array.push_back(glm::vec3{ j * 2, 0, i * 10 });
    }
  }

  unsigned int size = _size;
  for (auto i = 1U; i < size; ++i) {
    for (auto j = 0U; j < size; ++j) {
      _index_array.push_back(size * i + j);
      _index_array.push_back(size * (i - 1) + j);
    }
    _index_array.push_back(UINT_MAX); // Used as primary restart variable
  }
}

void WahAh::renderSelf()
{
  _shader.enableProgram();

  glActiveTexture(_colour_map);
  glEnable(GL_TEXTURE_CUBE_MAP);
  glBindTexture(GL_TEXTURE_CUBE_MAP, _colour_map);

  glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_NORMAL_MAP);
  glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_NORMAL_MAP);
  glTexGeni(GL_R, GL_TEXTURE_GEN_MODE, GL_NORMAL_MAP);
  glEnable(GL_TEXTURE_GEN_S);
  glEnable(GL_TEXTURE_GEN_T);
  glEnable(GL_TEXTURE_GEN_R);

  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

  glEnable(GL_PRIMITIVE_RESTART);
  glPrimitiveRestartIndex(UINT_MAX);

  glEnableClientState(GL_VERTEX_ARRAY);
  glVertexPointer(3, GL_FLOAT, 0, &_vertex_array[0]);

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  glDrawElements(GL_TRIANGLE_STRIP, static_cast<int>(_index_array.size()), GL_UNSIGNED_INT, &_index_array[0]); // draw a triangle strip for battlefield

  glDisable(GL_BLEND);

  glDisableClientState(GL_VERTEX_ARRAY); // Disable vertex arrays
  glDisable(GL_PRIMITIVE_RESTART);

  glDisable(GL_TEXTURE_GEN_R);
  glDisable(GL_TEXTURE_GEN_T);
  glDisable(GL_TEXTURE_GEN_S);

  glDisable(GL_TEXTURE_CUBE_MAP);

  _shader.disableProgram();
}

void WahAh::updateSelf()
{
  _shader.enableProgram();

  _time += 0.05f;
  glUniform1f(_time_id, _time);

  _shader.disableProgram();
}

} // namespace alien_prober
