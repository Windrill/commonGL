#pragma once
#include <string>
#include <unordered_map>
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
//#include "glm/glm.hpp"
struct ShaderProgramSource {
  std::string VertexSource;
  std::string FragmentSource;
};

class Shader {
private:
  std::string m_FilePath;
  unsigned int m_RendererID;
  mutable std::unordered_map<std::string, int> m_UniformLocationCache;
  // and caching

  unsigned int fs;
  unsigned int vs;

  bool bound;
public:
  // shader fragment and shader vertex are in 1 file
  Shader(const std::string& filepath);
  ~Shader();

  void CompilationCheck();
  void Bind() const; //'gluseprogram'
  void Unbind() const; // making non-const because member variable 'bound' changes
  // Set uniforms
  void SetUniform1i(const std::string& name, int v0); // for 'the slot you specify to sample your specified texture'
  void SetUniform1f(const std::string& name, float v0);
  void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3);
  void SetUniformMat4ff(const std::string& name, const glm::mat4 &matrix);
  void SetUniformMat4f(const std::string& name, const glm::mat4 &matrix);

  const unsigned int GetAttribLocation(const std::string& name);

private:
  ShaderProgramSource ParseShader(const std::string &filepath);

  unsigned int GetUniformLocation(const std::string& name);

  unsigned int CompileShader(unsigned int type, const std::string& source);
  unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);
};