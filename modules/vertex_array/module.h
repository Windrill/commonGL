#pragma once

// Vertex Array: Where this buffer is
// class VertexBuffer;
#include "vertex_buffer/module.h"
#include "vertex_buffer_layout/module.h"

class VertexArray {
public:
  explicit VertexArray(bool debug=false);
  // Finally you delete the correct id, which is the old id
  // Getting new Array (4), delete old number (2) and keep the new number thruogh move
  VertexArray & operator = (VertexArray && va)   noexcept {
    std::swap(m_RendererId, va.m_RendererId);
    std::swap(debug, va.debug);
//    m_RendererId = va.m_RendererId;
    std::cout << "[VA debug] Move assignment to here: " << m_RendererId << "\n";
    return *this;
  }

  VertexArray & operator = (const VertexArray & va) = delete;
////    std::swap(a,va.m_RendererId);
////    m_RendererId = va.m_RendererId;
//    return *this;
//  }

  VertexArray (VertexArray & va) = delete;

  VertexArray (VertexArray && va)
//  : m_RendererId(va.m_RendererId)
  {
    std::swap(m_RendererId, va.m_RendererId);
    std::swap(debug, va.debug);

    std::cout << "[VA debug] Move constructor: " << m_RendererId << "\n";
  }
  ~VertexArray();

  bool debug;
  static void DryLink();
  void AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout, int offsetLocation=0);
  void Bind() const;
  void UnBind() const;
  unsigned int m_RendererId;
};