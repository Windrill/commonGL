#include <stdexcept>
#include "common/Init.h"
#include <logging/module.h>
#include "module.h"

#define STB_IMAGE_IMPLEMENTATION

#include "vendor/stb_image/stb_image.h"
Texture::Texture(const std::string &path)
    : m_RendererID(0), m_FilePath(path), m_LocalBuffer(nullptr), m_Width(0), m_Height(0), m_BPP(0) {

  // flips texture vertically to make i upside down
  // gl expects pixels to start from bottom left
  stbi_set_flip_vertically_on_load(1);
  m_LocalBuffer = stbi_load(path.c_str(), &m_Width, &m_Height, &m_BPP, 4); // 4=rgba
  if (m_LocalBuffer == nullptr) {
    throw std::runtime_error("Texture image does not exist, check the string ");// + path.c_str());
  }
  GLCall(glGenTextures(1, &m_RendererID));
  GLCall(glBindTexture(GL_TEXTURE_2D, m_RendererID));

  // Must be specified for opengl...
  // ??? sepcial settings, not snapt o nearest pixel, resample method....
  // magnification filter: 'render texture on an area that's larger than actual texture size'
  GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
  GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
  // not extend area (don't tile), wrap = horizontal wrap; s=x, t=y
  GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
  GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

  // 0:  not multilevel texture
  // internal format: GL_TEXTURE_2D its own format
  // gl_rgba8: almost deprecated
  // second #: gl_rgba, format we are supplying
  GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_LocalBuffer));
  GLCall(glBindTexture(GL_TEXTURE_2D, 0));

  stbi_image_free(m_LocalBuffer);
}

Texture::~Texture() {
  GLCall(glDeleteTextures(1, &m_RendererID));
}

void Texture::Bind(unsigned int slot) const {
  //specify texture slot
  GLCall(glActiveTexture(GL_TEXTURE0 + slot))
  GLCall(glBindTexture(GL_TEXTURE_2D, m_RendererID));
}

void Texture::Unbind() const {
  GLCall(glBindTexture(GL_TEXTURE_2D, 0));
}
