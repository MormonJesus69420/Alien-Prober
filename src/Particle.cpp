#include "../include/Particle.hpp"

// Made with help from Kent

namespace alien_prober {

Particle::Particle()
{
  initSelf();
}

Particle::~Particle()
{
}

void Particle::initSelf()
{
  _texture = SOIL_load_OGL_texture("textures/particle.bmp", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
  _shader.loadShaders("shaders/particle.vert", "shaders/particle.frag");

  for (auto i = 0; i < MAX_PARTICLES; ++i) {
    _particles[i].active = true;
    _particles[i].life = 1.0f;
    _particles[i].fade = float(rand() % 100) / 1000.0f + 0.003f;
    _particles[i].xi = float((rand() % 50) - 26.0f) * 25.0f;
    _particles[i].yi = float((rand() % 50) - 25.0f) * 25.0f;
    _particles[i].zi = float((rand() % 50) - 25.0f) * 25.0f;
    _particles[i].xg = 0.0f;
    _particles[i].yg = -0.941f;
    _particles[i].zg = 0.0f;
    _particles[i].x = _matrix[3].x;
    _particles[i].y = _matrix[3].y;
    _particles[i].z = _matrix[3].z;
  }
}

void Particle::updateSelf()
{
}

void Particle::renderSelf()
{
  prepareRender();

  for (auto i = 0; i < MAX_PARTICLES; i++) {
    if (_particles[i].active) {
      float x = _particles[i].x;
      float y = _particles[i].y;
      float z = _particles[i].z;

      glBegin(GL_TRIANGLES);
      glTexCoord2d(1, 1);
      glVertex3f(x + 0.5f, y + 0.5f, z);
      glTexCoord2d(0, 1);
      glVertex3f(x - 0.5f, y + 0.5f, z);
      glTexCoord2d(1, 0);
      glVertex3f(x + 0.5f, y - 0.5f, z);
      glTexCoord2d(0, 0);
      glVertex3f(x - 0.5f, y - 0.5f, z);
      glEnd();

      _particles[i].x += _particles[i].xi / _slowdown;
      _particles[i].y += _particles[i].yi / _slowdown;
      _particles[i].z += _particles[i].zi / _slowdown;

      _particles[i].xi += _particles[i].xg;
      _particles[i].yi += _particles[i].yg;
      _particles[i].zi += _particles[i].zg;

      _particles[i].life -= 0.01;
      glUniform1f(_fade_effect, _particles[i].life);

      if (_particles[i].life < 0.0f) {
        faded = true;
      }

      glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
      glEnd();
    }
  }

  disableRender();
}

void Particle::prepareRender()
{
  _shader.enableProgram();
  glShadeModel(GL_SMOOTH);
  glDisable(GL_DEPTH_TEST);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE);
  glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
  glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
  glActiveTexture(GL_TEXTURE0);
  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, _texture);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  _fade_effect = glGetUniformLocation(_shader.getProgram(), "_fade");
}

void Particle::disableRender()
{
  glDisable(GL_TEXTURE_2D);
  glDisable(GL_BLEND);
  glEnable(GL_DEPTH_TEST);
  _shader.disableProgram();
}
} // namespace alien_prober
