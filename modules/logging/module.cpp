// assuming this is based on opengl only, no driver definitions here
#include "module.h"
#include <GLFW/glfw3.h>
#include <iostream>

// Note that definition of both private functions and member varialbes aren't subject to access control
void GLClearError() {
  while (GLenum err = glGetError());
}
void GLCheckError(const char* file, int line) {
  while (GLenum err = glGetError()) {
    std::cout << "[OpenGL Error] "<<err<<
                " " << file << ": "<<line
                 << " "
                <<std::endl;
  }
}
bool GLLogCall(const char* function, const char* file, int line) {
  while (GLenum err = glGetError()) {
    std::cout << "[OpenGL Error] ("<< err<< "): " <<function <<
              " " << file << ": "<<line <<std::endl;
    return false;
  }
  return true;
}


//
//void GLCheckError() {
//  while (GLenum err = glGetError()) {
//    std::cout << "[OpenGL Error] "<<err<<std::endl;
//  }
//}
//bool GLLogCall(const char* function, const char* file, int line) {
//  while (GLenum err = glGetError()) {
//    std::cout << "[OpenGL Error] ("<< err<< "): "  << " " << function <<
//              " " << file << ": "<<line <<std::endl;
//    return false;
//  }
//  return true;
//}
//#define ASSERT(x) if (!(x)) std::raise(SIGINT);
//
//#define GLCall(x) GLCheckError();\
//    x;\
//    ASSERT(GLLogCall(#x, __FILE__, __LINE__))
//
//
//void PrintOpenGLErrors(char const * const Function, char const * const File, int const Line)
//{
//  bool Succeeded = true;
//
//  GLenum Error = glGetError();
//  if (Error != GL_NO_ERROR)
//  {
//    char const * ErrorString = (char const *) gluErrorString(Error);
//    if (ErrorString)
//      std::cerr << ("OpenGL Error in %s at line %d calling function %s: '%s'", File, Line, Function, ErrorString) << std::endl;
//    else
//      std::cerr << ("OpenGL Error in %s at line %d calling function %s: '%d 0x%X'", File, Line, Function, Error, Error) << std::endl;
//  }
//}
//
//#ifdef _DEBUG
//#define CheckedGLCall(x) do { PrintOpenGLErrors(">>BEFORE<< "#x, __FILE__, __LINE__); (x); PrintOpenGLErrors(#x, __FILE__, __LINE__); } while (0)
//#define CheckedGLResult(x) (x); PrintOpenGLErrors(#x, __FILE__, __LINE__);
//#define CheckExistingErrors(x) PrintOpenGLErrors(">>BEFORE<< "#x, __FILE__, __LINE__);
//#else
//#define CheckedGLCall(x) (x)
//#define CheckExistingErrors(x)
//#endif

