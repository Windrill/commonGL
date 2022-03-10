#pragma once

// glad:to retrieve location of drivers that implement opengl
// glew: loads these and is loader for other components too.....

#include <vendor/glad/glad/gl.h>
#include <GLFW/glfw3.h>

// ri le guil liao!
// wut is these? let main tell u
// u cannot forward declare a typedef!!
//GLint;
void PrintShaderInfoLog(GLint const Shader);
