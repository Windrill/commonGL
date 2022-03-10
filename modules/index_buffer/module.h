#pragma once
// Index buffer: buffer containing indices to the vertex buffer (vertex buffer contains the location n other info)
// Like a reference buffer?????


// Which lines to draw in between vertices
class IndexBuffer {
private:
  // id related to opengl
  unsigned int m_Count; // num indices
public:
  // for this we're only supporting 65536 indices? so byte size for data type is set here to be unsigned int
  IndexBuffer(const unsigned int* data, unsigned int count, bool debug=false);
  ~IndexBuffer();

  void Bind() const;
  void Unbind() const;

  inline unsigned int getCount() const {return m_Count; }

  static void DryLink();
  unsigned int m_RendererID;
  bool debug;
};