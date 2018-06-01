#pragma once

#include "SceneObject.hpp"
#include "Shader.hpp"

// Made with help from Kent

namespace alien_prober {

class Particle : public SceneObject {

  public:
  Particle();
  ~Particle();

  bool faded{ false };

  protected:
  void initSelf();
  void renderSelf();
  void updateSelf();

  private:
  static constexpr int MAX_PARTICLES{ 500 };
  GLint _fade_effect;
  GLuint _texture;

  float _slowdown = 2000.0f;

  Shader _shader;

  struct ParticleContainer {
    bool active;
    float life;
    float fade;
    // Position values
    float x, y, z;
    // Direction values
    float xi, yi, zi;
    // Gravity values
    float xg, yg, zg;
  };

  ParticleContainer _particles[MAX_PARTICLES];

  void prepareRender();
  void disableRender();
};

} // namespace alien_prober
