#include "texture.h"

// System headers
#include <iostream>

// Vendor headers
#include "glad/gl.h"
#include "stb_image.h"

namespace glEngine {
Texture::Texture() {
  glGenTextures(1, &id_);
}

Texture::~Texture() {
  glDeleteTextures(1, &id_);
}

void Texture::LoadImage(const std::string& file_name) const {
  int width;
  int height;
  int num_components;
  unsigned char* data = stbi_load(file_name.c_str(), &width, &height, &num_components, 0);

  if (!data) {
    std::cerr << "Failed to open image file at " << file_name << std::endl;
  } else {
    unsigned int format;
    switch (num_components) {
      case 1: format = GL_RED; break;
      case 2: format = GL_RG; break;
      case 3: format = GL_RGB; break;
      case 4: format = GL_RGBA; break;
      default: std::cerr << "Invalid image format at " << file_name << std::endl; break;
    }

    glBindTexture(GL_TEXTURE_2D, id_);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
  }

  stbi_image_free(data);
}

unsigned int Texture::GetId() const {
  return id_;
}
}
