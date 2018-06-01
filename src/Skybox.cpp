#include "include/Skybox.hpp"

namespace alien_prober {

Skybox::Skybox(std::shared_ptr<Camera> camera)
{
  _camera = camera;
}

Skybox::~Skybox()
{
}

void Skybox::initSelf()
{
  // Initiate shader
  _shader.loadShaders("shaders/skybox.vert", "shaders/skybox.frag");

  _skybox_id = SOIL_load_OGL_cubemap(
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
  auto _skybox = glGetUniformLocation(_shader.getProgram(), "_skybox");
  glUniform1i(_skybox, 0);
  _shader.disableProgram();

  float size = 1.0f / 2.0f;

  _vertex_array = {
    -size,
    -size,
    -size,
    -size,
    size,
    -size,
    size,
    size,
    -size,
    size,
    -size,
    -size,
    size,
    -size,
    size,
    size,
    size,
    size,
    -size,
    -size,
    size,
    -size,
    size,
    size,
  };

  _index_array = {
    0,
    2,
    1,
    2,
    0,
    3,
    2,
    3,
    4,
    5,
    2,
    4,
    4,
    6,
    5,
    5,
    6,
    7,
    0,
    7,
    6,
    1,
    7,
    0,
    0,
    6,
    3,
    6,
    4,
    3,
    1,
    2,
    7,
    7,
    2,
    5,
  };
}

void Skybox::renderSelf()
{
  _shader.enableProgram();

  glDisable(GL_DEPTH_TEST);

  //glColor3f(1.0f, 0.0f, 0.0f);

  glActiveTexture(_skybox_id);
  glEnable(GL_TEXTURE_CUBE_MAP);
  glBindTexture(GL_TEXTURE_CUBE_MAP, _skybox_id);

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

  glEnableClientState(GL_VERTEX_ARRAY);
  glVertexPointer(3, GL_FLOAT, 0, &_vertex_array[0]);

  glDrawElements(GL_TRIANGLES, static_cast<int>(_index_array.size()), GL_UNSIGNED_INT, &_index_array[0]);

  glDisableClientState(GL_VERTEX_ARRAY);
  glDisable(GL_TEXTURE_CUBE_MAP);
  glDisable(GL_TEXTURE_GEN_S);
  glDisable(GL_TEXTURE_GEN_T);
  glDisable(GL_TEXTURE_GEN_R);

  glEnable(GL_DEPTH_TEST);

  _shader.disableProgram();
}

void Skybox::updateSelf()
{
  auto cam_matrix = _camera->getMatrix();
  auto skybox_matrix = glm::mat4();

  auto pos = cam_matrix[3] - skybox_matrix[3];
  auto temp = glm::vec3(-pos.x, -pos.y, -pos.z);

  setMatrix(glm::translate(skybox_matrix, temp));
}

GLuint Skybox::getSkybox()
{
  return _skybox_id;
}

} // namespace alien_prober
