#include <locale>
#include "module.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
//#include <GLFW/glfw3.h>
#include <glad/gl.h>
#include <logging/module.h>
//#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp> //translate, rotate, scale, perspective
#include <glm/gtc/type_ptr.hpp> //value_ptr

Shader::Shader(const std::string &filepath)
    : m_FilePath(filepath), bound(false) {

  ShaderProgramSource source = ParseShader(filepath);
  m_RendererID = CreateShader(source.VertexSource, source.FragmentSource);
}

Shader::~Shader() {
  GLCall(glDeleteProgram(m_RendererID));
}

void Shader::Bind() const {
//  if (bound) {
//    std::cout <<"Warning! Shader already bound! You're double binding?\n";
//    return;
//  }
  GLCall(glUseProgram(m_RendererID));
//  bound = true;
}

void Shader::Unbind() const {
//  bound =x false;
  GLCall(glUseProgram(0));
}

// Set uniforms
void Shader::SetUniform1f(const std::string &name, float v0) {
//    int ii = GetUniformLocation(name);
  GLCall(glUniform1f(GetUniformLocation(name), v0));
}

void Shader::SetUniform4f(const std::string &name, float v0, float v1, float v2, float v3) {
//    int bc = GetUniformLocation(name);
  GLCall(glUniform4f(GetUniformLocation(name), v0, v1, v2, v3));
}

unsigned int Shader::GetUniformLocation(const std::string &name) {
  if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end()) {
    // log(location of name.c_str() is location and is cached??)
    return m_UniformLocationCache[name];
  }
  GLCall(unsigned int location = glGetUniformLocation(m_RendererID, name.c_str()));
  // -1 as shader location = have uniform in location but not used b/c of comment,
  // or just newly declared...not used yet, will get 'stripped'
  // and uniform won't be in the shader
  if (location == -1)
    std::cout << "Warning: uniform '" << name << "' doesn't exist!\n";
  // LOG
  CLOG("Found uniform " + name + ":" + std::to_string(location));
//  std::cout << name << ": " << location << std::endl;
  // note that cache needs to update every compilation, when all the uniforms are updated
  m_UniformLocationCache[name] = location;
  return location;
}

const unsigned int Shader::GetAttribLocation(const std::string &name) {
  if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end()) {
    return m_UniformLocationCache[name];
  }
  GLCall(unsigned int location = glGetAttribLocation(m_RendererID, name.c_str()));
  if (location == -1) {
    std::cout << "Warning: attrib '" << name << "' doesn't exist!\n";
    // LOG
    CLOG("Found uniform " + name + ":" + std::to_string(location));
    std::flush(std::cout);
  }
//  std::cout << name << ": " << location << std::endl;
  // note that cache needs to update every compilation, when all the uniforms are updated
  m_UniformLocationCache[name] = location;
  return location;
}

ShaderProgramSource Shader::ParseShader(const std::string &filepath) {
  std::ifstream stream(filepath);
  enum class ShaderType {
    NONE = -1, VERTEX = 0, FRAGMENT = 1
  };
  std::string line;
  std::stringstream ss[2];
  ShaderType type = ShaderType::NONE;
  while (getline(stream, line)) {
    if (line.find("#shader") != std::string::npos) {
      if (line.find("vertex") != std::string::npos)
        type = ShaderType::VERTEX;
      else if (line.find("fragment") != std::string::npos) {
        type = ShaderType::FRAGMENT;
      }
    } else {
      // If shader file's first line is a comment, this will segfault
      ss[(int) type] << line << std::endl;
    }
  }
  return {ss[0].str(), ss[1].str()};
}

// strings meant to be 'actual source code", can be from file, internet, binary...in order to compile....
// ends up to be a string
unsigned int Shader::CreateShader(const std::string &vertexShader, const std::string &fragmentShader) {
  if (vertexShader == "" || fragmentShader == "") {
    throw std::runtime_error("Shader is empty!\n");
  }
  GLCall(unsigned int program = glCreateProgram());
  vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
  fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);
//    GLint compile = 0;
//    GLCall(glGetShaderiv(vs, GL_COMPILE_STATUS, &(compile)));

  GLCall(glAttachShader(program, vs));
  GLCall(glAttachShader(program, fs));
  GLCall(glLinkProgram(program));
  GLCall(glValidateProgram(program));

  glDeleteShader(vs);
  glDeleteShader(fs);
  return program;
}

unsigned int Shader::CompileShader(unsigned int type, const std::string &source) {
  unsigned int id = glCreateShader(type);
  const char *src = source.c_str();
  GLCall(glShaderSource(id, 1, &src, nullptr));
  GLCall(glCompileShader(id));

  int result;
  glGetShaderiv(id, GL_COMPILE_STATUS, &result);
  if (result == GL_FALSE) {
    int length;
    glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);

    char *message = (char *) (alloca(length * sizeof(char)));
    glGetShaderInfoLog(id, length, &length, message);
    std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << "shader!" << std::endl;
    std::cout << message << std::endl;
    glDeleteShader(id);
    return 0;
  }
  return id;
}

void Shader::SetUniform1i(const std::string &name, int v0) {
//    int ii = GetUniformLocation(name);
// setting texture... for u_Texture, can't use u_Color, must use texture(u_Texture, v_TexCoord);
  GLCall(glUniform1i(GetUniformLocation(name), v0));
}

void Shader::SetUniformMat4ff(const std::string &name, const glm::mat4 &matrix) {
  GLCall(glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &matrix[0][0]));
}

void setUniformMVP
    (
        GLuint Location,
        glm::vec3 const &Translate,
        glm::vec3 const &Rotate
    ) {
  glm::mat4 Projection =
      glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 100.f);
  glm::mat4 ViewTranslate = glm::translate(
      glm::mat4(1.0f),
      Translate);
  glm::mat4 ViewRotateX = glm::rotate(
      ViewTranslate,
      Rotate.y, glm::vec3(-1.0f, 0.0f, 0.0f));
  glm::mat4 View = glm::rotate(
      ViewRotateX,
      Rotate.x, glm::vec3(0.0f, 1.0f, 0.0f));
  glm::mat4 Model = glm::scale(
      glm::mat4(1.0f),
      glm::vec3(0.5f));
  glm::mat4 MVP = Projection * View * Model;
  GLCall(glUniformMatrix4fv(Location, 1, GL_FALSE, glm::value_ptr(MVP)));
}

void Shader::SetUniformMat4f(const std::string &name, const glm::mat4 &matrix) {
  // 1 matrix, column-major by default,
//    GLCall(glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, glm::value_ptr(matrix)));//&matrix[0][0]));
//    int ii = GetUniformLocation(name);
//    int a = GetUniformLocation("u_Color");
//    int b = GetUniformLocation("u_Texture");
//    int c = GetUniformLocation("vw_vec");
//  glm::mat4 proj = glm::ortho(-1.0f, 1.0f, -1.f, 1.f, -1.0f, 1.0f);
//    auto * projMat = glOrtho( 0, 400, 0, 400, -1, 1 );
//    glm::mat4 projMat = glm::ortho( 0.f, 400.f, 0.f, 400.f, -1.f, 1.f );

//  glm::mat4x2 bb = {1, 1, 1, 1, 1, 1, 1, 1};
//  glm::mat4 bc = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
//  GLCall(SetUniform4f("vw_vec", 1.0f, 1.0f, 1.0f, 1.0f));
//  glm::vec3 trans = {1, 1, 0};
//  glm::vec3 rot = {0, 0, 0};
//  int mvploc = GetUniformLocation("u_MVP");
//
//  setUniformMVP(mvploc, trans, rot);
//
//  float light[4] = {1, 2, 3, 4};
//  int lightloc = GetUniformLocation("lightloc");
//// Fill in `light` with data.
//  GLCall(glUniform4fv(lightloc, 1, &bb[0][0]));
//
//
//  float ll[8] = {1, 2, 3, 4, 1, 2, 3, 4};
//  int vloc = GetUniformLocation("vvv");
//  GLCall(glUniformMatrix4x2fv(vloc, 1, GL_FALSE,
//                              ll
//  ));
//
//  GLCall(glUniformMatrix4fv(mvploc, 1, GL_FALSE, &bc[0][0]));
//  GLCall(glUniformMatrix4fv(GetUniformLocation("u_MVP"), 1, GL_FALSE, &matrix[0][0]));

  GLCall(glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &matrix[0][0]));
//    GLCall(glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, glm::value_ptr(matrix)));
}

void Shader::CompilationCheck() {
  GLint compileStatus[10];
  GLint compile;
  // iv: integer vector
  GLCall(glGetShaderiv(vs, GL_VALIDATE_STATUS, &compileStatus[1]));
  GLCall(glGetShaderiv(vs, GL_COMPILE_STATUS, &(compile)));
  if (compileStatus[0] != GL_TRUE || compileStatus[1] != GL_TRUE) {
    GLint infoLogLength;
//        glGetShaderiv(m_RendererID, GL_INFO_LOG_LENGTH, &infoLogLength);
//        auto * buffer = new GLchar[infoLogLength];
//        GLsizei sz;
//        glGetShaderInfoLog(m_RendererID, infoLogLength, &sz, buffer);
//        if (infoLogLength > 0) {
////        std::wcout.imbue(std::locale("UTF-8"));
//            std::cout << buffer << std::endl;
//        }
////        std::wcout << buffer << std::endl;
//        delete [] buffer;
  }
  std::cout << compileStatus[0] << " " << compileStatus[1] << std::endl;
}