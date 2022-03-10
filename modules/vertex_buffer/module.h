#ifndef GLFW_VERTEXBUFFER_H
#define GLFW_VERTEXBUFFER_H

// Contains x,y coordinates of GPUs
// Vertex Buffer object: exchange data with GPU
class VertexBuffer {
private:
  unsigned int m_RendererID; // id related to opengl
public:
  VertexBuffer(const void* data, unsigned int size);
  ~VertexBuffer();

  void Bind() const;
  void Unbind() const;

  int Update(const void* data, unsigned int offset, unsigned int size);
};
#endif //GLFW_VERTEXBUFFER_H
