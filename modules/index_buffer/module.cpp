#include "common/Init.h"
#include "module.h"

#include <logging/module.h>

IndexBuffer::IndexBuffer(const unsigned int* data, unsigned int count, bool debug)
    : m_Count(count), debug(debug) {
//    ASSSERT(sizeof(unsigned int) == sizeof(GLuint));
  GLCall(glGenBuffers(1, &m_RendererID));
  if (debug) {
    printf("[IB Debug] Creating index buffer %d\n", m_RendererID);
  }
  GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID));
  // assuming unsigned int = gluint
  // y this 4 2 again
  GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, (count) * sizeof(unsigned int), data, GL_STATIC_DRAW));
//    GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, (6 * 2) * sizeof(unsigned int), data, GL_STATIC_DRAW));
//    glBufferData(GL_ARRAY_BUFFER, (6)*sizeof(float), data, GL_STATIC_DRAW);

}

IndexBuffer::~IndexBuffer() {
//  if (debug) {
    printf("[IB Debug] Deleting index buffer %d \n", m_RendererID);
//  }
  GLCall(glDeleteBuffers(1, &m_RendererID));
}

void IndexBuffer::Bind() const {
  GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID));
}

void IndexBuffer::Unbind() const {
  GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}


void IndexBuffer::DryLink() {

}