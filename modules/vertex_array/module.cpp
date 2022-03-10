#include "common/Init.h"
#include "module.h"

#include <logging/module.h>

VertexArray::VertexArray(bool debug) : m_RendererId(0), debug(debug) {
  // If segfault, LoadDriver is not being called!
  GLCall(glGenVertexArrays(1, &m_RendererId));
  if (debug) {
    std::cout << "[VA Debug] Create vertexarray! " << m_RendererId << " \n";
  }
//  GLCall(glBindVertexArray(m_RendererId));
};
VertexArray::~VertexArray() {
//  if (debug) {
    std::cout << "Delete vertexarray! " << m_RendererId << " \n";
//  }
  GLCall(glDeleteVertexArrays(1, &m_RendererId));
}

// what if i wanted 2 buffers to be drawn one after another in the same shader in different locations
void VertexArray::AddBuffer(const VertexBuffer& vb, const VertexBufferLayout &layout, int offsetLocation) {
  Bind();
  vb.Bind();
  const auto& elements = layout.GetElements();
  unsigned int offset = 0;
  for (unsigned int i=0;i<elements.size(); i++) {
    const auto& element = elements[i];
    GLCall(glEnableVertexAttribArray(i));
    // this vertex attrib pointer says index 0 of vertex attrib array will be bound to the currently bound gl array buffer
    // so this links buffer to vao
    GLCall(glVertexAttribPointer(offsetLocation + i, element.count, element.type, element.normalized, layout.GetStride(), (const void *) (intptr_t) offset));
    offset += element.count * VertexBufferElement::GetSizeOfType(element.type);

  }

  vb.Unbind();
  UnBind();
}

void VertexArray::Bind() const {
  // GL_INVALID_OPERATION is generated if array is not zero or the name of a vertex array object
  // previously returned from a call to glGenVertexArrays.
  GLCall(glBindVertexArray(m_RendererId));
}
void VertexArray::UnBind() const {
  GLCall(glBindVertexArray(0));
}

void VertexArray::DryLink() {}