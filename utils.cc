#include "utils.h"

int32_t GetByteStride(const Accessor& accessor, const BufferView& buffer_view) {
  int32_t n;
  int component_size_in_bytes = GetComponentSizeInBytes(accessor.component_type_);
  if (component_size_in_bytes <= 0) {
    n = -1;
  }
  if (buffer_view.byte_stride_ == 0) {
    int num_components = GetNumComponentsInType(accessor);
    if (num_components <= 0) {
      n = -1;
    }
    n = component_size_in_bytes * num_components;
  } else {
    if (buffer_view.byte_stride_ % component_size_in_bytes != 0) {
      n = -1;
    } else {
      n = buffer_view.byte_stride_;
    }
  }
  return n;
}

int32_t GetComponentSizeInBytes(const int32_t& component_type) {
  int32_t n;
  if (component_type == 5120) {
    n = 1;
  } else if (component_type == 5121) {
    n = 1;
  } else if (component_type == 5122) {
    n = 2;
  } else if (component_type == 5123) {
    n = 2;
  } else if (component_type == 5125) {
    n = 4;
  } else if (component_type == 5126) {
    n = 4;
  } else {
    n = -1;
  }
  return n;
}

int32_t GetNumComponentsInType(const Accessor& accessor) {
  int32_t n;
  if (accessor.type_ == "SCALAR") {
    n = 1;
  } else if (accessor.type_ == "VEC2") {
    n = 2;
  } else if (accessor.type_ == "VEC3") {
    n = 3;
  } else if (accessor.type_ == "VEC4" || accessor.type_ == "MAT2") {
    n = 4;
  } else if (accessor.type_ == "MAT3") {
    n = 9;
  } else if (accessor.type_ == "MAT4") {
    n = 16;
  } else {
    n = -1;
  }
  return n;
}
