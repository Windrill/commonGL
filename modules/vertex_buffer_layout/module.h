// because of how weird this is, you can only include this once ever in 1 translation unit
#pragma once
#include <vector>
#include <stdexcept>

struct VertexBufferElement {
  unsigned int type; //opengl type
  unsigned int count;
  unsigned char normalized;

  static unsigned int GetSizeOfType(unsigned int type);
  ~VertexBufferElement() = default;
};
class VertexBufferLayout {
private:
  std::vector<VertexBufferElement> m_Elements;
  unsigned int m_Stride;
public:
  VertexBufferLayout() : m_Stride(0) {}
  template<typename T>
  void inline Push(unsigned int count) {
    throw std::runtime_error("Err");
    // static_assert(false) //<--- c++17 extension
  }
  inline const std::vector<VertexBufferElement> GetElements() const& { return m_Elements; }
  inline unsigned int GetStride() const { return m_Stride; }
};
// making this inline, and received a suggestion from SO: https://stackoverflow.com/questions/53660616/explicit-template-specialization-multiple-definitions#53660677
// An explicit (full) specialization of a function template is subject to the one-definition rule,
// so StringUtils::toString<std::string> must not be defined in multiple translation units.
// You can solve this problem by declaring it inline.

template<>
void inline VertexBufferLayout::Push<float>(unsigned int count) {
  m_Elements.push_back({GL_FLOAT, count, GL_FALSE });
  m_Stride += count * VertexBufferElement::GetSizeOfType(GL_FLOAT);
}
template<>
void inline VertexBufferLayout::Push<unsigned int>(unsigned int count) {
  m_Elements.push_back({ GL_UNSIGNED_INT, count, GL_FALSE });
  m_Stride += count * VertexBufferElement::GetSizeOfType(GL_UNSIGNED_INT);
}
template<>
void inline VertexBufferLayout::Push<unsigned char>(unsigned int count) {
  m_Elements.push_back({ GL_UNSIGNED_BYTE, count, GL_TRUE });
  m_Stride += count * VertexBufferElement::GetSizeOfType(GL_UNSIGNED_BYTE);
}
