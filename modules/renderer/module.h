// i suppose getting a shared interface to run common graphics calls s.a. 'bind' is acceptable
// unless the call needs to be customized for each entity
// only need to let each separate 'asset' object specify their indices or part of obj to bind etc
#pragma once

//#define GLFW_INCLUDE_NONE

class Shader;
class VertexArray;
class IndexBuffer;

class Renderer {
public:
  void Clear() const;
  // need vertex array(w/ vertex buffer bound on it), index buffer(+index count//draw the whole thing huh), shader
  void Draw(const VertexArray &va, const IndexBuffer& ib, const Shader& shader) const;


// shader can be organizeed in its own manner and share a reference
// Draw an object with its own shading property, vertex array, and index bufer....
//  void Draw(Asset a) {}
};