#include "include/Projectile.hpp"

namespace alien_prober {

Projectile::Projectile()
{
  _type = ProjectileType::Bullet;
  _speed = -500.0f;
  _range = 300.0f;
  _fire_rate = 0.5f;
  _size = 2.0f;
  _damage = 1;
}

Projectile::Projectile(float speed, float range, float size, float fire_rate, int damage, ProjectileType type)
{
  _fire_rate = fire_rate;
  _damage = damage;
  _speed = speed;
  _range = range;
  _size = size;
  _type = type;
}

Projectile::~Projectile()
{
}

void Projectile::initSelf()
{
}

void Projectile::renderSelf()
{
  glColor3f(1.0, 1.0, 1.0);
  glutSolidSphere(static_cast<double>(_size), 5, 5);
  glClearColor(0.0, 0.0, 0.0, 0.0);
}

void Projectile::updateSelf()
{
  _matrix = glm::translate(_matrix, glm::vec3(0.0, 0.0, _speed / _fps));
}

int Projectile::getDamage()
{
  switch (_type) {
  case ProjectileType::Bullet:
    return 1;
  case ProjectileType::Laser:
    return 2;
  case ProjectileType::Missle:
    return 5;
  }
}

float Projectile::getFireRate()
{
  return _fire_rate;
}

float Projectile::getRange()
{
  return _range;
}

float Projectile::getSize()
{
  return _size;
}

glm::vec4 Projectile::getPosition() const
{
  return glm::vec4{ _matrix[3][0], _matrix[3][1], _matrix[3][2], _matrix[3][3] };
}

EnemyProjectile::EnemyProjectile()
    : Projectile(900.0f, 100.0f, 2.0f, 1.0f, 1, ProjectileType::Bullet)
{
}

EnemyProjectile::~EnemyProjectile()
{
}

void EnemyProjectile::renderSelf()
{
  glColor3f(1.0f, 0.0f, 0.0f);
  glutSolidSphere(static_cast<double>(_size), 5, 5);
  glClearColor(0.0, 0.0, 0.0, 0.0);
}

MachineProjectile::MachineProjectile()
    : Projectile(-900.0f, -1000.0f, 2.0f, 0.3f, 1, ProjectileType::Bullet)
{
}

MachineProjectile::~MachineProjectile()
{
}

void MachineProjectile::renderSelf()
{
  glColor3f(1.0, 1.0, 1.0);
  glutSolidSphere(static_cast<double>(_size), 5, 5);
  glClearColor(0.0, 0.0, 0.0, 0.0);
}

FanProjectile::FanProjectile(float angle)
    : Projectile(-700.0f, -750.0f, 2.0f, 0.75f, 1, ProjectileType::Bullet)
{
  _angle = angle * 2;
}

FanProjectile::~FanProjectile()
{
}

void FanProjectile::renderSelf()
{
  glColor3f(0.0, 1.0, 0.0);
  glutSolidSphere(static_cast<double>(_size), 5, 5);
  glClearColor(0.0, 0.0, 0.0, 0.0);
}

void FanProjectile::updateSelf()
{
  _matrix = glm::translate(_matrix, glm::vec3(_angle, 0, _speed / _fps));
}

} // namespace alien_prober
