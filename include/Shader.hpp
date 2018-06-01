#pragma once

#include <GL/glew.h>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

/**
  * Class used to load a vertex and fragment shader to program.
  *
  * Usage:
  *   Use loadVertex(vertexPath, fragmentPath) to load shaders.
  *   Use enable and disable to turn program on and off.
  *   Use getProgram to get it as a variable.
  *
  * Credits:
  *   Based on code by Håvard Kindem, since teacher's code didn't work.
  *   https://badvertex.com/2012/11/20/how-to-load-a-glsl-shader-in-opengl-using-c.html
  *
  * @author <Daniel Aaron Salwerowicz>
  * Copyright Kobol Dev 2018
  */

namespace alien_prober {

class Shader {
  public:
  Shader();
  ~Shader();

  bool loadShaders(const char*, const char*);
  void disableProgram();
  void enableProgram();
  GLuint getProgram();

  private:
  std::string readFile(const char*);
  GLuint _program;
};

} // namespace alien_prober
