#pragma once

#include <random>
#include <time.h>

#include "Battlefield.hpp"
#include "Camera.hpp"
#include "Enemy.hpp"
#include "Particle.hpp"
#include "Projectile.hpp"
#include "SceneObject.hpp"
#include "Skybox.hpp"
#include "Spaceship.hpp"
#include "WahAh.hpp"

namespace alien_prober {

class GameManager : public SceneObject {
  public:
  GameManager();
  ~GameManager();

  std::shared_ptr<Spaceship> getSpaceship();
  std::shared_ptr<Camera> getCamera();

  bool _paused{ false };
  bool _game_over{ false };

  void changeWeapon(WeaponType type);
  void shotsFired();
  void enemyFire();
  void spawnOfDevil();

  protected:
  virtual void initSelf();
  virtual void renderSelf();
  virtual void updateSelf();

  private:
  std::shared_ptr<Battlefield> _battlefield1;
  std::shared_ptr<Battlefield> _battlefield2;
  std::shared_ptr<Spaceship> _spaceship;
  std::shared_ptr<Camera> _camera;
  std::shared_ptr<Skybox> _skybox;
  std::shared_ptr<WahAh> _wahah;

  std::vector<std::shared_ptr<Projectile>> _player_projectiles;
  std::vector<std::shared_ptr<Projectile>> _enemy_projectiles;
  std::vector<std::shared_ptr<Particle>> _particles;
  std::vector<std::shared_ptr<Enemy>> _enemies;

  WeaponType _weapon_type{ WeaponType::MachineGun };

  bool checkHitEnemy(std::shared_ptr<Projectile>&, std::vector<std::shared_ptr<Projectile>>::iterator&);
  bool checkHitPlayer(std::shared_ptr<Projectile>&, std::vector<std::shared_ptr<Projectile>>::iterator&);
  bool checkHitPlayer(std::shared_ptr<Enemy>&, std::vector<std::shared_ptr<Enemy>>::iterator&);
  bool collision(glm::mat4, float, glm::mat4, float);

  void cleanup();

  clock_t _timer;
  clock_t _enemy_timer;
  int _death_counter = 0;

  std::random_device _dev;
  std::mt19937 _gen;
  std::uniform_real_distribution<float> _f_dist;
  std::uniform_int_distribution<int> _i_dist;
};
} // namespace alien_prober
