#ifdef _WIN32
#include <windows.h>
#endif

#include "include/FpsCounter.hpp"
#include "include/GameManager.hpp"
#include "include/Input.hpp"
#include <GL/freeglut.h>

using namespace alien_prober;

std::shared_ptr<GameManager> _game_manager;
siut::FpsCounter _counter;

int _window;
float _fps;

bool _key_pressed[30];
int _mouse_pos_x, _mouse_pos_y;
float _move_x, _move_y;

void init()
{
  glewInit();
  glClearColor(0.0, 0.0, 0.0, 0.0);
  glShadeModel(GL_SMOOTH);
  glEnable(GL_DEPTH_TEST);

  _game_manager = std::make_shared<GameManager>();
  _game_manager->init();
}

void handleKeys()
{
  if (_game_manager->getSpaceship()->pepsi())
    return;

  if (!_game_manager->_paused) {
    if (_key_pressed[KEY_ID_W])
      _game_manager->getSpaceship()->moveForward();
    if (_key_pressed[KEY_ID_A])
      _game_manager->getSpaceship()->moveLeft();
    if (_key_pressed[KEY_ID_D])
      _game_manager->getSpaceship()->moveRight();
    if (_key_pressed[KEY_ID_S])
      _game_manager->getSpaceship()->moveBackward();
    //    if (_key_pressed[KEY_ID_P])
    //      _game_manager->getCamera()->moveUp();
    //    if (_key_pressed[KEY_ID_C])
    //      _game_manager->getCamera()->moveDown();
    if (_key_pressed[KEY_ID_E] || _key_pressed[MOUSE_LEFT_BUTTON_DOWN])
      _game_manager->shotsFired();
    if (_key_pressed[KEY_ID_1])
      _game_manager->changeWeapon(WeaponType::MachineGun);
    if (_key_pressed[KEY_ID_2])
      _game_manager->changeWeapon(WeaponType::FanGun);
  }
  if (_key_pressed[KEY_ID_SPACE]) {
    _game_manager->_paused = !_game_manager->_paused;
    _key_pressed[KEY_ID_SPACE] = false;
  }
}

void display()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  _fps = _counter.fps();

  if (!_game_manager->_paused && !_game_manager->_game_over)
    _game_manager->update(_fps);

  _game_manager->render();

  handleKeys();
  glutSwapBuffers();
  glutPostRedisplay();
}

void keyDown(unsigned char key, int x, int y)
{
  switch (key) {
  case 'q':
  case 27:
    glutDestroyWindow(_window);
#ifndef _WIN32
    // Must use this with regular glut, since it never returns control to main().
    exit(0);
#endif
  case 'w':
    _key_pressed[KEY_ID_W] = true;
    break;
  case 'a':
    _key_pressed[KEY_ID_A] = true;
    break;
  case 's':
    _key_pressed[KEY_ID_S] = true;
    break;
  case 'd':
    _key_pressed[KEY_ID_D] = true;
    break;
  case ' ':
    _key_pressed[KEY_ID_SPACE] = true;
    break;
  case 'c':
    _key_pressed[KEY_ID_C] = true;
    break;
  case 'e':
    _key_pressed[KEY_ID_E] = true;
    break;
  case 'p':
    _key_pressed[KEY_ID_P] = true;
    break;
  case '1':
    _key_pressed[KEY_ID_1] = true;
    break;
  case '2':
    _key_pressed[KEY_ID_2] = true;
    break;

  default:
    glutPostRedisplay();
  }

  //Just to shut up Clang
  x = y;
}

void keyUp(unsigned char key, int x, int y)
{
  switch (key) {
  case 'w':
    _key_pressed[KEY_ID_W] = false;
    break;
  case 'a':
    _key_pressed[KEY_ID_A] = false;
    break;
  case 's':
    _key_pressed[KEY_ID_S] = false;
    break;
  case 'd':
    _key_pressed[KEY_ID_D] = false;
    break;
  case ' ':
    _key_pressed[KEY_ID_SPACE] = false;
    break;
  case 'c':
    _key_pressed[KEY_ID_C] = false;
    break;
  case 'e':
    _key_pressed[KEY_ID_E] = false;
    break;
  case '1':
    _key_pressed[KEY_ID_1] = false;
    break;
  case '2':
    _key_pressed[KEY_ID_2] = false;
    break;
  }

  //Just to shut up Clang
  x = y;
}

void mousePressed(int button, int state, int posX, int posY)
{
  if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
    _mouse_pos_x = posX;
    _mouse_pos_y = posY;
    _key_pressed[MOUSE_LEFT_BUTTON_DOWN] = true;
  }
  if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
    _key_pressed[MOUSE_LEFT_BUTTON_DOWN] = false;
}

void mouseMoved(int posX, int posY)
{
  if (_key_pressed[MOUSE_LEFT_BUTTON_DOWN]) {
    //int diffX = posX - _mouse_pos_x;
    _mouse_pos_x = posX;
    //int diffY = posY - _mouse_pos_y;
    _mouse_pos_x = posY;

    // Implement quaternion based mouse move
  }
}

void reshape(int w, int h)
{
  glViewport(0, 0, w, h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(60.0, w / h, 0.1, 3000.0);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

int main(int argc, char** argv)
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGB);
  glutInitWindowSize(700, 700);
  glutInitWindowPosition(10, 10);
  _window = glutCreateWindow("Alien Prober");
  init();
  glutKeyboardFunc(keyDown);
  glutKeyboardUpFunc(keyUp);
  glutReshapeFunc(reshape);
  glutDisplayFunc(display);
  glutMouseFunc(mousePressed);
  glutMotionFunc(mouseMoved);

  // Add other callback functions here..

  glutMainLoop();
  return 0;
}
