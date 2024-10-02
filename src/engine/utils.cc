#include "utils.h"

// System headers
#include <iostream>
#include <string>

namespace glEngine::utils {
bool IsUriEmbedded(const std::string& uri) {
  if (uri.find("data:application/octet-stream;base64,") == 0U) {
    return true;
  }
  return false;
}

int ComponentTypeToByteSize(int component_type) {
  int byte_size;

  // BYTE or UNSIGNED_BYTE
  if (component_type == 5120 || component_type == 5121) {
    byte_size = 1;
  }

  // SHORT or UNSIGNED_SHORT
  else if (component_type == 5122 || component_type == 5123) {
    byte_size = 2;
  }

  // UNSIGNED_INT or FLOAT
  else if (component_type == 5125 || component_type == 5126) {
    byte_size = 4;
  }

  // Undefined component type
  else {
    std::cerr << "Accessor property \"componentType\" (" << component_type << ") is undefined" << std::endl;
    byte_size = 0;
  }

  return byte_size;
}

int TypeToNumComponents(const std::string& type) {
  int num_components;

  // SCALAR
  if (type == "SCALAR") {
    num_components = 1;
  }

  // VEC2
  else if (type == "VEC2") {
    num_components = 2;
  }

  // VEC3
  else if (type == "VEC3") {
    num_components = 3;
  }

  // VEC4 or MAT2
  else if (type == "VEC4" || type == "MAT2") {
    num_components = 4;
  }

  // MAT3
  else if (type == "MAT3") {
    num_components = 9;
  }

  // MAT4
  else if (type == "MAT4") {
    num_components = 16;
  }

  // Undefined type
  else {
    std::cerr << "Accessor property \"type\" (" << type << ") is undefined" << std::endl;
    num_components = 0;
  }

  return num_components;
}
}
