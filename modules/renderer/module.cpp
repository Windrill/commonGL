#include "common/Init.h"
#include "module.h"

#include "modules/shader/module.h"
#include "modules/vertex_array/module.h"
#include "modules/index_buffer/module.h"

#include <logging/module.h>
// create an interface that includes vertexarray, indexbuffer, shader, and vertexarrayobject...just to be able to link to its commands


void Renderer::Draw(const VertexArray &va, const IndexBuffer &ib, const Shader &shader) const {
  shader.Bind();
  // Lol, don't unbind huh
  va.Bind();
  ib.Bind(); // must bind index buffer!
  GLCall(glDrawElements(GL_TRIANGLES, ib.getCount(), GL_UNSIGNED_INT, nullptr));

  va.UnBind();
  ib.Unbind();
  shader.Unbind();
}

void Renderer::Clear() const {

  glClear(GL_COLOR_BUFFER_BIT);
}
