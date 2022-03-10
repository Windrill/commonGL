// driver based, because these implementations are linked by the opengl loading library itself...you can use multiple loading libraries btw, try to use macros for this?anw there is space in this directory
// u see this!



// glad before module.h or after????

#include "module.h"

#include <iostream>

void LoadDriver() {
  // if glad is enabled
  // version discrepancy??
  gladLoadGL(glfwGetProcAddress);
//  gladLoadGL();

  // Default buffering settings
  glfwSwapInterval( 1 );
  //I doubt you can call even something as simple as glGetString without an OpenGL context.
  std::cout << glGetString(GL_VERSION) << std::endl;


}
//void loadDriver();
// initialization!
void Init() {
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

//  LoadDriver();


}

//void loadDriver() {
//  // if glad is enabled
//  gladLoadGL();
//
//}

#if GLEW_DEFINED
void loadGlew() {
    GLenum err = glewInit();
  if (GLEW_OK != err)
  {
    std::cerr << "Error: " << glewGetErrorString(err) << std::endl;
    glfwTerminate();
    return -1;
  }
}
#endif



/*
 *
 * Logging Functionalities
 *
 */

// since this init is special...only in main???!!!
void PrintShaderInfoLog(GLint const Shader)
{
  int InfoLogLength = 0;
  int CharsWritten = 0;

  glGetShaderiv(Shader, GL_INFO_LOG_LENGTH, & InfoLogLength);

  if (InfoLogLength > 0)
  {
    GLchar * InfoLog = new GLchar[InfoLogLength];
    glGetShaderInfoLog(Shader, InfoLogLength, & CharsWritten, InfoLog);
    std::cout << "Shader Info Log:" << std::endl << InfoLog << std::endl;
    delete [] InfoLog;
  }
}
