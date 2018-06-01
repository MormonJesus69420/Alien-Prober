#pragma once

#include "SceneObject.hpp"

namespace alien_prober {

enum class ProjectileType {
  Bullet,
  Laser,
  Missle
};

enum class WeaponType {
  MachineGun,
  FanGun
};

class Projectile : public SceneObject {
  public:
  Projectile();
  Projectile(float, float, float, float, int, ProjectileType);
  ~Projectile();

  float getFireRate();
  float getRange();
  int getDamage();
  float getSize();

  glm::vec4 getPosition() const;

  protected:
  void initSelf();
  void renderSelf();
  void updateSelf();

  float _speed, _range, _size, _fire_rate;
  ProjectileType _type;
  int _damage;
};

class MachineProjectile : public Projectile {
  public:
  MachineProjectile();
  ~MachineProjectile() override;

  void renderSelf() override;
};

class FanProjectile : public Projectile {
  public:
  FanProjectile(float);
  ~FanProjectile() override;

  void renderSelf() override;
  void updateSelf() override;

  private:
  float _angle;
};

class EnemyProjectile : public Projectile {
  public:
  EnemyProjectile();
  ~EnemyProjectile() override;

  void renderSelf() override;
};

} // namespace alien_prober
