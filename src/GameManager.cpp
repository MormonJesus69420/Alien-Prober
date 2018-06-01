#include "include/GameManager.hpp"

namespace alien_prober {

GameManager::GameManager()
{
  _gen = std::mt19937(_dev());
  _f_dist = std::uniform_real_distribution<float>(-100, 100);
  _i_dist = std::uniform_int_distribution<int>(0, 2);
}

GameManager::~GameManager()
{
}

void GameManager::initSelf()
{
  // Set default OpenGL states
  glEnable(GL_CULL_FACE);

  // Set light position vector
  float lightPosition[] = { 15.0f, 10.0f, 35.0f, 0.0f };
  glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);

  // Adding the camera to the scene
  _camera.reset(new Camera());
  _skybox.reset(new Skybox(_camera));
  addSubObject(_skybox);

  _wahah.reset(new WahAh(256));
  addSubObject(_wahah);

  _battlefield1.reset(new Battlefield(0));
  addSubObject(_battlefield1);
  _battlefield2.reset(new Battlefield(-5100));
  addSubObject(_battlefield2);

  _spaceship.reset(new Spaceship());
  addSubObject(_spaceship);
}

void GameManager::renderSelf()
{
}

void GameManager::updateSelf()
{
  if (_spaceship->gaymOver()) {
    if (++_death_counter > 500)
      _game_over = true;

    return;
  }

  // Instead of adding all objects in the scene as subobjects to the camera they are added as subobjects
  // to the game manager. Therefore, we set the game manager matrix equal to the camera matrix.
  this->_matrix = _camera->getMatrix();

  for (auto it = _player_projectiles.begin(); !_spaceship->pepsi() && it != _player_projectiles.end();) {
    // Checks if bullet hit enemy, if true it will be deleted in the method
    if (!checkHitEnemy(*it, it)) {
      // Check if bullet out of range, delete if so, else increment counter
      if ((*it)->getPosition().z < (*it)->getRange()) {
        removeSubObject(*it);
        it = _player_projectiles.erase(it);
      }
      else
        ++it;
    }
  }

  for (auto it = _enemy_projectiles.begin(); !_spaceship->pepsi() && it != _enemy_projectiles.end();) {
    // Checks if bullet hit player, if true it will be deleted in the method
    if (!checkHitPlayer(*it, it)) {
      // Check if bullet out of range, delete if so, else increment counter
      if ((*it)->getPosition().z > (*it)->getRange()) {
        removeSubObject(*it);
        it = _enemy_projectiles.erase(it);
      }
      else
        ++it;
    }
  }

  for (auto it = _enemies.begin(); !_spaceship->pepsi() && it != _enemies.end();) {
    // Checks if enemy hit player, if true it will be deleted in the method
    if (!checkHitPlayer(*it, it)) {
      // Check if enemy out of range, delete if so, else increment counter
      if ((*it)->getPosition().z > 150.0f) {
        removeSubObject(*it);
        it = _enemies.erase(it);
      }
      else
        ++it;
    }
  }

  for (auto it = _particles.begin(); it != _particles.end();) {
    if ((*it)->faded) {
      removeSubObject(*it);
      it = _particles.erase(it);
    }
    else
      ++it;
  }

  if (clock() > _enemy_timer) {
    spawnOfDevil();
    enemyFire();
    _enemy_timer = clock() + static_cast<int>(CLOCKS_PER_SEC *1.5);
  }

  if (_battlefield1->getPosition().z >= 5100) {
    removeSubObject(_battlefield1);
    _battlefield1 = _battlefield2;
    _battlefield2.reset(new Battlefield(-5100));
    addSubObject(_battlefield2);
    _battlefield2->init();
  }
}

bool GameManager::checkHitEnemy(std::shared_ptr<Projectile>& p, std::vector<std::shared_ptr<Projectile>>::iterator& it)
{
  for (auto ei = _enemies.begin(); ei != _enemies.end(); ++ei) {
    auto e = *ei;

    if (collision(e->getMatrix(), e->getSize(), p->getMatrix(), p->getSize())) {
      auto particle = std::make_shared<Particle>();
      particle->setMatrix(e->getMatrix());
      addSubObject(particle);
      _particles.push_back(particle);

      removeSubObject(p);
      it = _player_projectiles.erase(it);

      removeSubObject(e);
      _enemies.erase(ei);
      return true;
    }
  }

  return false;
}

bool GameManager::checkHitPlayer(std::shared_ptr<Projectile>& p, std::vector<std::shared_ptr<Projectile>>::iterator& it)
{
  if (collision(_spaceship->getMatrix(), _spaceship->getSize(), p->getMatrix(), p->getSize())) {
    auto particle = std::make_shared<Particle>();
    particle->setMatrix(_spaceship->getMatrix());
    addSubObject(particle);
    _particles.push_back(particle);

    _spaceship->hit(p->getDamage());

    removeSubObject(p);
    it = _enemy_projectiles.erase(it);

    if (_spaceship->pepsi())
      cleanup();

    return true;
  }

  return false;
}

bool GameManager::checkHitPlayer(std::shared_ptr<Enemy>& e, std::vector<std::shared_ptr<Enemy>>::iterator& it)
{
  if (collision(e->getMatrix(), e->getSize(), _spaceship->getMatrix(), _spaceship->getSize())) {
    auto particle = std::make_shared<Particle>();
    particle->setMatrix(_spaceship->getMatrix());
    addSubObject(particle);
    _particles.push_back(particle);

    removeSubObject(e);
    it = _enemies.erase(it);

    _spaceship->hit(50);

    if (_spaceship->pepsi())
      cleanup();

    return true;
  }

  return false;
}

bool GameManager::collision(glm::mat4 pos1, float rad1, glm::mat4 pos2, float rad2)
{
  auto x1 = pos1[3].x, y1 = pos1[3].y, z1 = pos1[3].z;
  auto x2 = pos2[3].x, y2 = pos2[3].y, z2 = pos2[3].z;
  auto d1 = x1 - x2, d2 = y1 - y2, d3 = z1 - z2;

  return sqrtf(d1 * d1 + d2 * d2 + d3 * d3) <= rad1 + rad2;
}

void GameManager::enemyFire()
{
  for (auto enemy : _enemies) {
    std::shared_ptr<Projectile> projectile = std::make_shared<EnemyProjectile>();
    projectile->setMatrix(enemy->getMatrix());

    addSubObject(projectile);
    _enemy_projectiles.push_back(projectile);
  }
}

void GameManager::shotsFired()
{
  if (clock() > _timer && !_spaceship->pepsi() && !_spaceship->gaymOver()) {
    std::shared_ptr<Projectile> projectile;
    if (_weapon_type == WeaponType::MachineGun) {
      projectile = std::make_shared<MachineProjectile>();
      projectile->setMatrix(getSpaceship()->getMatrix());
      addSubObject(projectile);
      _player_projectiles.push_back(projectile);
    }
    else if (_weapon_type == WeaponType::FanGun) {
      for (auto i = -2; i <= 2; ++i) {
        projectile = std::make_shared<FanProjectile>(i / 10.0);
        projectile->setMatrix(getSpaceship()->getMatrix());
        addSubObject(projectile);
        _player_projectiles.push_back(projectile);
      }
    }

    _timer = static_cast<long>(clock() + projectile->getFireRate() * CLOCKS_PER_SEC);
  }
}

void GameManager::spawnOfDevil()
{
  int type = _i_dist(_gen);

  std::shared_ptr<Enemy> enemy;
  if (type == 0)
    enemy = std::make_shared<Enemy>(MovementPattern::sinus);
  else
    enemy = std::make_shared<Enemy>(MovementPattern::straight);

  addSubObject(enemy);
  _enemies.push_back(enemy);
  enemy->init();

  auto matrix = enemy->getMatrix();
  matrix = glm::translate(matrix, glm::vec3{ _f_dist(_gen), 0, 0 });
  enemy->setMatrix(matrix);
}

void GameManager::cleanup()
{
  for (auto p : _enemy_projectiles)
    removeSubObject(p);
  for (auto p : _player_projectiles)
    removeSubObject(p);
  for (auto e : _enemies)
    removeSubObject(e);

  _enemy_projectiles.clear();
  _player_projectiles.clear();
  _enemies.clear();

  if (_spaceship->gaymOver())
    removeSubObject(_spaceship);
}

std::shared_ptr<Camera> GameManager::getCamera()
{
  return _camera;
}

std::shared_ptr<Spaceship> GameManager::getSpaceship()
{
  return _spaceship;
}

void GameManager::changeWeapon(WeaponType type)
{
  _weapon_type = type;
}

} // namespace alien_prober
