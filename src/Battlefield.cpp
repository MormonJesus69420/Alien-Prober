#include "include/Battlefield.hpp"

namespace alien_prober {

Battlefield::Battlefield(int z)
{
  _matrix = glm::translate(_matrix, glm::vec3(0, 0, z));
}

Battlefield::~Battlefield()
{
}

void Battlefield::initSelf()
{
  _shader.loadShaders("shaders/height.vert", "shaders/height.frag");

  _height_map = SOIL_load_OGL_texture("textures/battlefield_height_map.bmp", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
  _normal_map = SOIL_load_OGL_texture("textures/battlefield_normal_map.bmp", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
  _colour_map = SOIL_load_OGL_texture("textures/battlefield_colour_map.bmp", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);

  _shader.enableProgram();

  _shader_height_map = glGetUniformLocation(_shader.getProgram(), "_height_map");
  _shader_normal_map = glGetUniformLocation(_shader.getProgram(), "_normal_map");
  _shader_colour_map = glGetUniformLocation(_shader.getProgram(), "_colour_map");
  glUniform1i(_shader_height_map, 0);
  glUniform1i(_shader_normal_map, 1);
  glUniform1i(_shader_colour_map, 2);

  _shader.disableProgram();

  // Helper values, change them to change how battlefield is drawn
  auto const X_LENGTH = 10, Z_LENGTH = 10, Y = -50;
  auto const X_ELEMENTS = 64, Z_ELEMNETS = 512, HALF_X_ELEMENTS = X_ELEMENTS / 2;

  // Create vertex array, x and z are multiplied by specified value to spread them out
  // X values go from -HALF_X_ELEMENTS to HALF_X_ELEMENTS so that battlefield is centered on z axis
  // Textures work with help from Kent Arne Larsen & Victor Lindback
  for (auto i = 0; i > -Z_ELEMNETS; --i) {
    for (auto j = -HALF_X_ELEMENTS; j < HALF_X_ELEMENTS; ++j) {
      _vertex_array.push_back(glm::vec3{ j * X_LENGTH, Y, i * Z_LENGTH });
      _texture_array.push_back(glm::vec2{ (j + HALF_X_ELEMENTS) / 63.0f, -i / 511.0f });
    }
  }

  // Create index array telling order of going through vertices
  //
  //  32   33   34   35  ...
  //
  //   0    1    2    3  ...
  //
  //  index array will be then : 32, 0, 33, 1, ..., UNIT_MAX, 64, 32, ...
  for (auto i = 1U; i < Z_ELEMNETS; ++i) {
    for (auto j = 0U; j < X_ELEMENTS; ++j) {
      _index_array.push_back(X_ELEMENTS * i + j);
      _index_array.push_back(X_ELEMENTS * (i - 1) + j);
    }
    _index_array.push_back(UINT_MAX); // Used as primary restart variable
  }
}

void Battlefield::renderSelf()
{
  _shader.enableProgram();

  glActiveTexture(GL_TEXTURE0);
  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, _height_map);

  glActiveTexture(GL_TEXTURE1);
  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, _normal_map);

  glActiveTexture(GL_TEXTURE2);
  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, _colour_map);


  glEnable(GL_PRIMITIVE_RESTART); // Enable primitve restart mode to draw triangle strip
  glPrimitiveRestartIndex(UINT_MAX); // Set reset index to UINT_MAX that is pushed to _inde_array in initSelf

  glEnableClientState(GL_VERTEX_ARRAY); // Enable vertex arrays
  glEnableClientState(GL_TEXTURE_COORD_ARRAY);

  glVertexPointer(3, GL_FLOAT, 0, &_vertex_array[0]); // Set vertex pointer
  glTexCoordPointer(2, GL_FLOAT, 0, &_texture_array[0]);

  glDrawElements(GL_TRIANGLE_STRIP, static_cast<int>(_index_array.size()), GL_UNSIGNED_INT, &_index_array[0]); // draw a triangle strip for battlefield

  glDisableClientState(GL_TEXTURE_COORD_ARRAY);
  glDisableClientState(GL_VERTEX_ARRAY); // Disable vertex arrays
  glDisable(GL_PRIMITIVE_RESTART);


  glDisable(GL_TEXTURE_2D);
  glActiveTexture(GL_TEXTURE1);
  glDisable(GL_TEXTURE_2D);
  glActiveTexture(GL_TEXTURE0);
  glDisable(GL_TEXTURE_2D);

  glClearColor(0.0, 0.0, 0.0, 0.0);
  _shader.disableProgram();
}

void Battlefield::updateSelf()
{
  _matrix = glm::translate(_matrix, glm::vec3(0, 0, 7));
}


glm::vec4 Battlefield::getPosition() const
{
  return glm::vec4{ _matrix[3][0], _matrix[3][1], _matrix[3][2], _matrix[3][3] };
}
} // namespace alien_prober
