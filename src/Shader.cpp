#include "include/Shader.hpp"

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

Shader::Shader()
{
}

Shader::~Shader()
{
}

std::string Shader::readFile(const char* filePath)
{
  std::string content;

  std::ifstream fileStream(filePath, std::ios::in);

  if (!fileStream.is_open()) {
    std::cerr << "Could not read file " << filePath << ". File does not exist." << std::endl;
    return "";
  }

  std::string line = "";
  while (!fileStream.eof()) {
    std::getline(fileStream, line);
    content.append(line + "\n");
  }

  fileStream.close();
  return content;
}

bool Shader::loadShaders(const char* vertexPath, const char* fragmentPath)
{
  GLuint vertShader = glCreateShader(GL_VERTEX_SHADER);
  GLuint fragShader = glCreateShader(GL_FRAGMENT_SHADER);

  // Read shaders
  std::string vertShaderStr = readFile(vertexPath);
  std::string fragShaderStr = readFile(fragmentPath);
  const char* vertShaderSrc = vertShaderStr.c_str();
  const char* fragShaderSrc = fragShaderStr.c_str();

  if(vertShaderStr.empty() || fragShaderStr.empty()) return false;

  GLint result = GL_FALSE;
  int logLength;

  // Compile vertex shader
  std::cout << "Compiling vertex shader." << std::endl;
  glShaderSource(vertShader, 1, &vertShaderSrc, NULL);
  glCompileShader(vertShader);

  // Check vertex shader
  glGetShaderiv(vertShader, GL_COMPILE_STATUS, &result);
  glGetShaderiv(vertShader, GL_INFO_LOG_LENGTH, &logLength);
  std::vector<GLchar> vertShaderError((logLength > 1) ? logLength : 1);
  glGetShaderInfoLog(vertShader, logLength, NULL, &vertShaderError[0]);
  std::cout << &vertShaderError[0] << std::endl;

  if(logLength > 1) return false;

  // Compile fragment shader
  std::cout << "Compiling fragment shader." << std::endl;
  glShaderSource(fragShader, 1, &fragShaderSrc, NULL);
  glCompileShader(fragShader);

  // Check fragment shader
  glGetShaderiv(fragShader, GL_COMPILE_STATUS, &result);
  glGetShaderiv(fragShader, GL_INFO_LOG_LENGTH, &logLength);
  std::vector<GLchar> fragShaderError((logLength > 1) ? logLength : 1);
  glGetShaderInfoLog(fragShader, logLength, NULL, &fragShaderError[0]);
  std::cout << &fragShaderError[0] << std::endl;

  if(logLength > 1) return false;

  std::cout << "Linking program" << std::endl;
  GLuint program = glCreateProgram();
  glAttachShader(program, vertShader);
  glAttachShader(program, fragShader);
  glLinkProgram(program);

  glGetProgramiv(program, GL_LINK_STATUS, &result);
  glGetProgramiv(program, GL_INFO_LOG_LENGTH, &logLength);
  std::vector<char> programError((logLength > 1) ? logLength : 1);
  glGetProgramInfoLog(program, logLength, NULL, &programError[0]);
  std::cout << &programError[0] << std::endl;

  if(logLength > 1) return false;

  glDeleteShader(vertShader);
  glDeleteShader(fragShader);

  _program = program;
  return true;
}

void Shader::disableProgram()
{
  glUseProgram(0);
}

void Shader::enableProgram()
{
  glUseProgram(_program);
}

GLuint Shader::getProgram()
{
  return _program;
}

} // namespace alien_prober
