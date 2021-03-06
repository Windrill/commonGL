#include "common/Init.h"
#include "module.h"

#include "logging/module.h"


unsigned int VertexBufferElement::GetSizeOfType(unsigned int type) {
  switch (type) {
    case GL_FLOAT:         return 4;
    case GL_UNSIGNED_INT:  return 4;
    case GL_UNSIGNED_BYTE: return 1;
  }
  ASSERT(false);
  return 0;
}