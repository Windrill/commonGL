// array buffer: vertex buffer
#include "module.h"

#include "common/Init.h"
#include <logging/module.h>

// data: whole array; size: datatype size * num attributes * num elements
VertexBuffer::VertexBuffer(const void *data, unsigned int size) {
  GLCall(glGenBuffers(1,&m_RendererID));
  GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID));
  GLCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
}


int VertexBuffer::Update(const void *data, unsigned int offset, unsigned int size) {
  // if some boolean switch says it is unbound, return with -1
  glBufferSubData(	GL_ARRAY_BUFFER, offset, size, data);
  // opengl 4.5: buffer
  //Specifies the name of the buffer object for glNamedBufferSubData.
  return 0;
}

VertexBuffer::~VertexBuffer() {
  GLCall(glDeleteBuffers(1, &m_RendererID));
}

void VertexBuffer::Bind() const {
  GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID));
}

void VertexBuffer::Unbind() const {
  GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}
